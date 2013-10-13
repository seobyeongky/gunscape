//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: networkclient.cpp
//
// 내용: 네트워크클라이언트
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "networkmanager.h"



NetworkClient* NetworkClient::pInstance = NULL;






NetworkClient::NetworkClient():m_sock(NULL)
{
}

NetworkClient::~NetworkClient()
{
	if(m_sock)
		closesocket(m_sock);	
}

NetworkClient* NetworkClient::CreateInstance()
{
	if(pInstance == NULL)
		pInstance = new NetworkClient();
	return pInstance;
}

void NetworkClient::DestroyInstance(NetworkClient* pInstance_)
{
	if(pInstance_ == pInstance)
		delete pInstance;
}



bool NetworkClient::init()
{
	
	WSADATA wsaData;
	BYTE nMajor = 2, nMinor = 2;
	WORD wVersionRequested = MAKEWORD(nMinor, nMajor);
	int nRet = WSAStartup(wVersionRequested, &wsaData);
	if(nRet == SOCKET_ERROR || LOBYTE(wsaData.wVersion) != nMajor || HIBYTE(wsaData.wVersion) != nMinor)
	{
		return false;
		//먼가에러
	}
	
	m_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	try
	{
		if(m_sock == INVALID_SOCKET)
			throw "대기소켓객체생성실패";
		
		struct sockaddr_in addr;

		memset( &addr, 0, sizeof( addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(9190);
		addr.sin_addr.s_addr = inet_addr("5.44.8.106");
		if(connect(m_sock, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
		{
			int i = GetLastError();
			throw "connect 에러";

		}


	}
	catch(char* errmsg)
	{
		int a=0;
		return false;
	}
	return true;

}
bool NetworkClient::sendtest(char* s)
{
	int n = send(m_sock,s,(int)strlen(s)+1,0);
	if(n == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}