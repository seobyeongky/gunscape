#pragma once

#include "smap.h"
#include "protocol.h"

#include <opznet\client.h>
#include <string>
#include <vector>
#include <functional>

namespace NetInterface
{
	void Begin();
	void End();

	bool Connect(const std::wstring & addr, const std::wstring & user_name);
	void GetFoundSv(std::vector<opznet::server_info_t> * ptr);

	void Update();

	void RegisterConnectFailedCallback(std::function<void()> callback);
	void RegisterConnectedCallback(std::function<void(const opznet::server_info_t & sv_info, opznet::ID my_id)> callback);
	void RegisterClientIntroCallback(std::function<void(const opznet::client_t & cl_info)> callback);
	void RegisterClientGoneCallback(std::function<void(const opznet::client_t & cl_info)> callback);
	void RegisterPacketCallback(sv2cl_t type, std::function<void(opznet::Packet & packet)> callback);
	void ClearCallbacks();
	void GetClients(smap<opznet::ID, opznet::client_t> * ptr);
}
