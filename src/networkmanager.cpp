//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: networkmanager.cpp
//
// ����: ��Ʈ��ũ �Ŵ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "networkmanager.h"



NetworkManager* NetworkManager::pInstance = NULL;






NetworkManager::NetworkManager():
m_hCP(NULL), m_lstnsock(INVALID_SOCKET), m_hDlg(NULL), m_lThreadCnt(0), test("�׽�Ʈ")
{
}

bool NetworkManager::init()
{
	ZeroMemory(&m_AOV,sizeof(ACCEPTOVERLAPPED));

	WSADATA wsaData;
	BYTE nMajor = 2, nMinor = 2;
	WORD wVersionRequested = MAKEWORD(nMinor, nMajor);
	int nRet = WSAStartup(wVersionRequested, &wsaData);
	if(nRet == SOCKET_ERROR || LOBYTE(wsaData.wVersion) != nMajor || HIBYTE(wsaData.wVersion) != nMinor)
	{
		return false;
		//�հ�����
	}

	InitializeCriticalSection(&m_cs);

	m_hCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	if(m_hCP == NULL)
	{
		return false;
		//IOCP��ü�� �����ϴµ� �����߽��ϴ�.
	}

	if(!CreateListenSocket())
	{
		return false;

		//���ϻ�������
	}

	SYSTEM_INFO si;
	GetSystemInfo(&si);
	for(int i = 0 ; i < (int)si.dwNumberOfProcessors*2 ; i++)
	{
		HANDLE hThread = (HANDLE)_beginthreadex(NULL,0,CommThread, NULL, 0, NULL);
		CloseHandle(hThread);
	}
	return true;
}


NetworkManager::~NetworkManager()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	for(int i = 0; i < (int) si.dwNumberOfProcessors*2; i++)
		PostQueuedCompletionStatus(m_hCP, 1, 0, NULL);

	while(0 < m_lThreadCnt)
		Sleep(16);//�̰� �ȵɵ�;

	closesocket(m_lstnsock);

	list<MYOVERLAPPED*>::iterator it = m_ltMOV.begin();
	while(it != m_ltMOV.end())
	{
		MYOVERLAPPED* pMOV = *it;
		closesocket(pMOV->commsock);
		delete pMOV->wasBuf.buf;
		delete pMOV;

		it++;
	}
	m_ltMOV.clear();

	DeleteCriticalSection(&m_cs);

	WSACleanup();
}


NetworkManager* NetworkManager::CreateInstance()
{
	if(pInstance == NULL)
		pInstance = new NetworkManager();
	return pInstance;
}



void NetworkManager::DestroyInstance(NetworkManager* pInstance_)
{
	if(pInstance_ == pInstance)
		delete pInstance;
}




BOOL NetworkManager::CreateListenSocket()
{
	try
	{
		m_lstnsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(m_lstnsock == INVALID_SOCKET)
			throw "�����ϰ�ü��������";

		struct sockaddr_in addr;
		memset( &addr, 0, sizeof( addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(9190);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		if(bind(m_lstnsock, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
			throw "bind ����";

		if(listen(m_lstnsock,SOMAXCONN) == SOCKET_ERROR)
			throw "listen ����";

		CreateIoCompletionPort((HANDLE)m_lstnsock, m_hCP, (DWORD)m_lstnsock, 0);

		SOCKET commsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(commsock == INVALID_SOCKET)
			throw "���� ��ü ���� ����";

		m_AOV.commsock = commsock;
		DWORD dwBytes;
		if(!AcceptEx(m_lstnsock, commsock, m_AcceptBuf, 0, sizeof(sockaddr_in)+16, sizeof(sockaddr_in)+16, &dwBytes, (WSAOVERLAPPED*)&m_AOV))
		{
			
			int i = GetLastError();
			i+=1;
		}
	}
	catch(char* errmsg)
	{
		int a=0;
		return false;
	}
	return true;
}
//-------------------------------------------------

unsigned __stdcall NetworkManager::CommThread(void* pArguments)
{
	InterlockedIncrement(&pInstance->m_lThreadCnt);
	__try
	{
		__try
		{
			return pInstance->InnerCommThread();
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{

		}
	}
	__finally
	{
		InterlockedDecrement(&pInstance->m_lThreadCnt);
	}
	return 0;
	
}


unsigned __stdcall NetworkManager::InnerCommThread(void)
{
	try
	{
		while(1)
		{
			DWORD cbTransferred;
			SOCKET sock;
			WSAOVERLAPPED* pOV = NULL;

			int nRet = GetQueuedCompletionStatus(m_hCP, &cbTransferred, (LPDWORD)&sock, (LPOVERLAPPED*)&pOV, INFINITE);
			if(sock == m_lstnsock)
			{
				ACCEPTOVERLAPPED* pAOV = (ACCEPTOVERLAPPED*)pOV;
				OnAccept(pAOV->commsock, m_AcceptBuf);
				SOCKET commsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
				if(commsock != INVALID_SOCKET)
				{
					m_AOV.commsock = commsock;
					DWORD dwBytes;
					AcceptEx(m_lstnsock, commsock, m_AcceptBuf, 0 , sizeof(sockaddr_in)+16, sizeof(sockaddr_in)+16, &dwBytes, (WSAOVERLAPPED*)&m_AOV);

				}
				continue;
			}
			if(sock == 0)
				break;
			
			if(cbTransferred == 0)
			{
				OnClose((MYOVERLAPPED*)pOV);
				continue;
			}
			MYOVERLAPPED* pMOV = (MYOVERLAPPED*)pOV;
			OnRead(pMOV, pMOV->wasBuf.buf, cbTransferred);
		}
	}
	catch(char* errmsg)
	{
		int a;
		return 1;
	}
	return 0;
}

void NetworkManager::OnAccept(SOCKET commsock, char* AcceptBuf)
{
	MYOVERLAPPED* pMOV= new MYOVERLAPPED;
	ZeroMemory(&pMOV->ov, sizeof(WSAOVERLAPPED));
	pMOV->wasBuf.buf = new char[1024];
	pMOV->wasBuf.len = 1024;
	pMOV->commsock = commsock;

	CreateIoCompletionPort((HANDLE)commsock, m_hCP, (DWORD)commsock, 0);

	DWORD dwBytes, dwFlags = 0;
	WSARecv(commsock, &pMOV->wasBuf, 1, &dwBytes, &dwFlags, (WSAOVERLAPPED*)pMOV, NULL);

	EnterCriticalSection(&m_cs);
	m_ltMOV.push_back(pMOV);
	LeaveCriticalSection(&m_cs);

	struct sockaddr_in* cliaddr;
	int nlen = sizeof(cliaddr);
	GetAcceptExSockaddrs(AcceptBuf, 0, sizeof(sockaddr_in)+16, 0, (sockaddr**)(&cliaddr), &nlen, NULL, NULL);

	//����
}

void NetworkManager::OnRead(MYOVERLAPPED* pMOV, char* buf, int nRead)
{
	EnterCriticalSection(&m_cs);

	test+=buf;
	//list<MYOVERLAPPED*>::iterator it = m_ltMOV.begin();
	//while(it != m_ltMOV.end())
	//{
	//	MYOVERLAPPED* pMOV = *it;
	//	send(pMOV->commsock, buf, nRead, 0);
	//	it++;
	//}


	LeaveCriticalSection(&m_cs);
	DWORD dwFlags = 0, dwBytes;
	WSARecv(pMOV->commsock, &pMOV->wasBuf, 1, &dwBytes, &dwFlags, (WSAOVERLAPPED*)pMOV, NULL);
}

void NetworkManager::OnClose(MYOVERLAPPED* pMOV)
{
	EnterCriticalSection(&m_cs);
	m_ltMOV.remove(pMOV);
	LeaveCriticalSection(&m_cs);

	closesocket(pMOV->commsock);
	delete pMOV->wasBuf.buf;
	delete pMOV;

}