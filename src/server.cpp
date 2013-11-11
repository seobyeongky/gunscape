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
		bool		req_next_lv;
	
		cl_context_t()
			: name(), delay(0), send(false), req_next_lv(false)
		{
		}
		cl_context_t(const client_t & _basic_info)
			: name(_basic_info.name), delay(0), send(false), req_next_lv(false)
		{
		}
	};
	
	typedef smap<ID, cl_context_t> client_map_t;

	bool					endflag = false;
	vector<SPECIAL_STAGE>	stages;
	client_map_t			client_map;
	
	vector<Command>			commands;
	int						nr_send = 0;
	int						nr_voidness = 0;

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

	//
	// 모든 클라이언트가 command들을 보냈다면...
	//
	bool IsGotAllCommands()
	{
		return nr_send > 0 && static_cast<unsigned int>(nr_send) >= client_map.size();
	}
	
	//
	// 그걸 합해서 되돌려줍니다.
	//
	void DelegateCommands()
	{		
		nr_send = 0;
		for (auto & it : client_map)
		{
			it.element().send = false;
		}

		Packet sendpacket;
		sendpacket << TO_UINT16(SV2CL_COMMANDS)
			<< commands.size();
		string outbuf;
		for (auto & c : commands)
		{
			c.AppendToString(&outbuf);
			sendpacket << outbuf;
			outbuf.clear();
		}

		for (auto & cl : client_map)
		{
			SafeSend(cl.key(), sendpacket);
		}

		commands.clear();
	}

	//
	// 확인
	//
	bool NextLvOk()
	{
		for (auto & cl : client_map)
		{
			if (!cl.element().req_next_lv)
			{
				return false;
			}
		}
		return true;
	}

	//
	// hoho
	//
	void SendNextLvAllow()
	{
		Packet sendpacket;
		sendpacket << TO_UINT16(SV2CL_NEXT_LEVEL_ALLOW);
		for (auto & cl : client_map)
		{
			SafeSend(cl.key(), sendpacket);
			cl.element().req_next_lv = false;
		}
		nr_voidness = 0;
	}


	void HandleRecvPacket(client_map_t::Iter it, cl2sv_t header, Packet & packet)
	{
		ID cl_id = (*it).key();
		cl_context_t & cl_context = (*it).element();
		switch (header)
		{
		case CL2SV_MY_CHARACTER:
			{
				int sel;
				packet >> sel;

				Packet sendpacket;
				sendpacket << TO_UINT16(SV2CL_INTRODUCE_CHARACTER) << cl_id << sel;

				for (auto & cl : client_map)
				{
					SafeSend(cl.key(), sendpacket);
				}
			}
			break;

		case CL2SV_REQUEST_NEXT_LEVEL:
			{
				cl_context.req_next_lv = true;

				bool ok = true;
				for (auto & cl : client_map)
				{
					if (!cl.element().req_next_lv)
					{
						ok = false;
						break;
					}
				}

				nr_voidness++;
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
			
			break;
		}
	}

	void Loop(function<void()> callback)
	{
		BeginServer(config::username + L"님의 서버");
		ChatMsg_Manager::PushMessage(L"서버 서비스 시작");

		callback();

		unsigned int seed = static_cast<unsigned int>(time(nullptr));
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
//							send_packet << stages.size();
	//						for (auto it : stages)
		//						send_packet << static_cast<int>(it);
							send_packet << seed;
							SafeSend(msg.client_info.id, send_packet);
						}
						break;
					case SVMSG_CLIENT_GONE:
						{
							client_map_t::Iter it;
							if (!client_map.find(msg.client_info.id, &it))
							{
								ChatMsg_Manager::PushMessage(L"서버 : 알 수 없는 클라이언트 : " + to_wstring(msg.client_info.id));
								continue;
							}
							if ((*it).element().send) nr_send--;
							if ((*it).element().req_next_lv) nr_voidness--;
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
				if (IsGotAllCommands()) DelegateCommands();
				if (NextLvOk()) SendNextLvAllow();
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