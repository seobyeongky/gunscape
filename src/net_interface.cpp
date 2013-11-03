#include "net_interface.h"

using namespace std;
using namespace opznet;

namespace NetInterface
{
	typedef function<void(client_msg_t & msg)> callback_t;
	typedef smap<client_msg_type_t, callback_t> callback_map_t;
	typedef smap<sv2cl_t, function<void(Packet & packet)>> packet_callback_map_t;

	bool					began = false;
	vector<server_info_t>	found_sv_list;
	callback_map_t			callback_map;
	packet_callback_map_t	packet_callback_map;
	client_msg_t			cl_msg;
	smap<ID, client_t>		client_map;

	void Begin()
	{
		BeginClient();
		began = true;
	}

	void End()
	{
		began = false;
		EndClient();
	}

	bool Connect(const wstring & addr, const wstring & user_name)
	{
		return RequestConnectToServer(addr.c_str(), user_name.c_str());
	}

	void GetFoundSv(vector<server_info_t> * ptr)
	{
		if (began)
		{
			*ptr = found_sv_list;
		}
		else
			ptr->clear();
	}

	void Update()
	{
		while (GetClientMsg(&cl_msg))
		{
			switch (cl_msg.type)
			{
			case CLMSG_CONNECT_FAILED:
			case CLMSG_CONNECTED:
			case CLMSG_DISCONNECTED:
			case CLMSG_CLIENT_INTRODUCTION:
			case CLMSG_CLIENT_GONE:
				{
					switch (cl_msg.type)
					{
					case CLMSG_CLIENT_INTRODUCTION:
						client_map[cl_msg.client_info.id] = cl_msg.client_info;
						break;
					case CLMSG_CLIENT_GONE:
						client_map.erase(cl_msg.client_info.id);
						break;
					}

					callback_map_t::Iter iter;
					if (callback_map.find(cl_msg.type, &iter))
					{
						(*iter).element()(cl_msg);
					}
				}
				break;
			case CLMSG_LOCAL_SERVER_FOUND:
				break;
			case CLMSG_FINDING_LOCAL_SERVER_OVER:
				break;
			case CLMSG_UNEXPECTED_ERROR:
				break;
			case CLMSG_PACKET_RECV:
				{
					unsigned short header;
					if (!(cl_msg.packet >> header)) return;
					sv2cl_t type = static_cast<sv2cl_t>(header);

					packet_callback_map_t::Iter iter;
					if (packet_callback_map.find(type, &iter))
					{
						(*iter).element()(cl_msg.packet);
					}
				}
				break;
			}
		}
	}

	void RegisterConnectFailedCallback(function<void()> callback)
	{
		callback_map[CLMSG_CONNECT_FAILED] = [callback](client_msg_t & msg)
		{
			callback();
		};
	}

	void RegisterConnectedCallback(function<void(const server_info_t & sv_info, ID my_id)> callback)
	{
		callback_map[CLMSG_CONNECTED] = [callback](client_msg_t & msg)
		{
			callback(msg.server_info, msg.my_id);
		};
	}

	void RegisterClientIntroCallback(function<void(const client_t & cl_info)> callback)
	{
		callback_map[CLMSG_CLIENT_INTRODUCTION] = [callback](client_msg_t & msg)
		{
			callback(msg.client_info);
		};
	}

	void RegisterClientGoneCallback(function<void(const client_t & cl_info)> callback)
	{
		callback_map[CLMSG_CLIENT_GONE] = [callback](client_msg_t & msg)
		{
			callback(msg.client_info);
		};
	}
	
	void RegisterPacketCallback(sv2cl_t type, function<void(Packet & packet)> callback)
	{
		packet_callback_map[type] = [callback](Packet & packet)
		{
			callback(packet);
		};
	}

	void ClearCallbacks()
	{
		callback_map.clear();
		packet_callback_map.clear();
	}

	void GetClients(smap<ID, client_t> * ptr)
	{
		*ptr = client_map;
	}
};