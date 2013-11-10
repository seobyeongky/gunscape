#include "server.h"
#include "config.h"
#include "chatmsgmanager.h"
#include "gamemanager.h"
#include "random.h"
#include "smap.h"
#include "protocol.h"
#include "proto\command.pb.h"
#include "stringconvert.h"

#include <thread>
#include <string>
using namespace std;

#include <opznet/server.h>
using namespace opznet;

// light server

namespace Server
{
	struct cl_context_t
	{
		wstring		name;
		int			delay;
		bool		send;
	
		cl_context_t()
			: name(), delay(0), send(false)
		{
		}
		cl_context_t(const client_t & _basic_info)
			: name(_basic_info.name), delay(0), send(false)
		{
		}
	};
	
	typedef smap<ID, cl_context_t> client_map_t;

	bool					endflag = false;
	vector<SPECIAL_STAGE>	stages;
	client_map_t			client_map;
	
	vector<Command>			commands;
	int						nr_send = 0;

	vector<list<ID>>		stage_map;
	int						req_id_count = 0;
	smap<int, ID>			req_map;

	void PushCommands(Packet & packet)
	{
		size_t nr_commands;
		packet >> nr_commands;
		string inbuf;
		for (size_t i = 0U; i < nr_commands; ++i)
		{
			Command c;
			packet >> inbuf;
			c.ParseFromString(inbuf);
			commands.push_back(c);
			inbuf.clear();
		}
	}

	void HandleRecvPacket(client_map_t::Iter it, cl2sv_t header, Packet & packet)
	{
		ID cl_id = (*it).key();
		cl_context_t & cl_context = (*it).element();
		switch (header)
		{
		case CL2SV_REQUEST_LEVEL:
			{
				int lv;
				packet >> lv;
				auto & cl_list = stage_map[lv];
				if (cl_list.empty())
				{
					Packet sendpacket;
					sendpacket << TO_UINT16(SV2CL_CONTEXT) << 0;
					SafeSend(cl_id, sendpacket);
					for (auto list : stage_map)
					{
						list.remove(cl_id);
					}
					stage_map[lv].push_back(cl_id);
				}
				else
				{
					// 이미 가진 클라이언트에게 스테이지 정보 요청
					ID sender = cl_list.front();
					ID receiver = cl_id;
					req_map[req_id_count] = receiver;
					Packet sendpacket;
					sendpacket << TO_UINT16(SV2CL_REQUEST_STAGE) << req_id_count;
					SafeSend(sender, sendpacket);
					req_id_count++;
				}
			}
			break;

		case CL2SV_STAGE_INFO:
			{
				// 전달
				int req_id;
				packet >> req_id;
				ID receiver = req_map[req_id];
				size_t len = packet.GetByteSize()-sizeof(unsigned short)-sizeof(int);
				void * buf = new char[len];
				packet.Extract(buf, len);
				Packet sendpacket;
				sendpacket << TO_UINT16(SV2CL_CONTEXT) << 1;
				sendpacket.Append(buf, len);
				SafeSend(receiver, sendpacket);
				delete buf;
			}
			break;

		case CL2SV_COMMANDS:

			if (cl_context.send)
			{
				ChatMsg_Manager::PushMessage(L"클라이언트(" + to_wstring((*it).key()) + L") 중복 전송");
				return;
			}
			nr_send++;
			cl_context.send = true;

			PushCommands(packet);

			if (static_cast<unsigned int>(nr_send) >= client_map.size())
			{
				// 모든 클라이언트가 command들을 보냈다면...
				// 그걸 합해서 되돌려줍니다.
				nr_send = 0;
				for (auto it : client_map)
				{
					it.element().send = false;
				}

				Packet sendpacket;
				sendpacket << TO_UINT16(SV2CL_COMMANDS)
					<< commands.size();
				string outbuf;
				for (auto c : commands)
				{
					c.AppendToString(&outbuf);
					sendpacket << outbuf;
					outbuf.clear();
				}

				for (auto cl : client_map)
				{
					SafeSend(cl.key(), sendpacket);
				}

				commands.clear();
			}
			break;
		}
	}

	void Loop(function<void()> callback)
	{
		wstring wusername;
		multi2uni(config::username, &wusername);
		BeginServer(wusername + L"님의 관전 서버");
		ChatMsg_Manager::PushMessage(L"서버 서비스 시작");

		callback();

		server_msg_t msg;

		while(!endflag)
		{
			while(GetServerMsg(&msg))
			{
				switch (msg.type)
				{
					case SVMSG_NEW_CLIENT:
						client_map[msg.client_info.id] = cl_context_t(msg.client_info);
						{
							Packet send_packet;
							send_packet << TO_UINT16(SV2CL_WELCOME);
							send_packet << stages.size();
							for (auto it : stages)
								send_packet << static_cast<int>(it);
							SafeSend(msg.client_info.id, send_packet);
						}
						break;
					case SVMSG_CLIENT_GONE:
						{
							client_map_t::Iter it;
							if (client_map.find(msg.client_info.id, &it))
							{
								ChatMsg_Manager::PushMessage(L"서버 : 알 수 없는 클라이언트 : " + to_wstring(msg.client_info.id));
								continue;
							}
							if ((*it).element().send) nr_send--;
							client_map.erase(it);
						}
						break;
					case SVMSG_PACKET_RECV:
						{
							unsigned short header;
							if (!(msg.packet >> header)) break;
							client_map_t::Iter it;
							if (!client_map.find(msg.client_info.id, &it))
							{
								ChatMsg_Manager::PushMessage(L"서버 : 알 수 없는 클라이언트 : " + to_wstring(msg.client_info.id));
								continue;
							}
							
							HandleRecvPacket(it, static_cast<cl2sv_t>(header), msg.packet);
						}
						break;
					case SVMSG_CLIENT_DELAY_TIME_UPDATED:
						{
							client_map_t::Iter iter;
							if (client_map.find(msg.client_info.id, &iter))
							{
								(*iter).element().delay = msg.delay_time;
							}
						}
						break;
					case SVMSG_BIND_FAILED:
						ChatMsg_Manager::PushMessage(L"서버 : 바인드 실패");
						break;
				}
			}
			Sleep(20);
		}

		EndServer();
	}

	void Start(SPECIAL_STAGE * stages16, function<void()> callback)
	{
		endflag = false;
		stages.assign(&stages16[0], &stages16[16]);
		stage_map.resize(stages.size());
		thread t(Loop, callback);
		t.detach();
	}

	void End()
	{
		endflag = true;
	}
}