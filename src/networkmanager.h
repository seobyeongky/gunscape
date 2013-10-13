//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: networkmanager.h
//
// 내용: 네트워크 매니저
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef  __NETWORK_MANAGER_H__
#define  __NETWORK_MANAGER_H__

#define  _WINSOCKAPI_

#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <process.h>
#include <list>
#include <mswsock.h>
#include "coord_def.h"

using namespace std;


#pragma comment( lib, "Ws2_32" )
#pragma comment( lib, "Mswsock" )

struct ACCEPTOVERLAPPED
{
	WSAOVERLAPPED ov;
	SOCKET commsock;
};

struct MYOVERLAPPED
{
	WSAOVERLAPPED ov;
	WSABUF wasBuf;
	SOCKET commsock;
};

class KeyinforBuf
{
	unsigned char index, team;
	DWORD key[8];
	float mouse_x, mouse_y;
	unsigned char mouse;//오른쪽에서 1비트(왼버튼),2비트(오른버튼)
public:
	KeyinforBuf():index(0),team(0),mouse_x(0),mouse_y(0),mouse(0)
	{
		for(int i=0;i<8;i++)
			key[i] = 0;
	}
	unsigned char GetIndex(){return index;}
	unsigned char GetTeam(){return team;}
	bool GetKey(int key_)
	{
		return (key[key_/8] & (1 << (key_%8)))!=0;
	}
	void SetKey(int key_)
	{
		key[key_/8] |= (1 << (key_%8));
	}
	coord_def GetMousePos()
	{
		return coord_def(mouse_x,mouse_y);
	}

	int SetNextIndex(unsigned char prev)
	{
		if(++prev>GetMaxIndex())
		{
			prev = 0;
		}
		return (index = prev);
	}
	unsigned char GetMaxIndex(){return 200;};
	int thenBig(char a) //a가 index보다 큰가? 맞을경우 1, 아닐경우 0, 같을 경우 -1
	{
		int dif = a-index;
		if(dif*dif>GetMaxIndex()*GetMaxIndex()/4)
		{
			return (a>index?-1:(a==index?1:0));
		}
		return (a>index?1:(a==index?-1:0));
	}

	void SetIndex(unsigned char index_){index = index_;}
	void SetMouseX(float mouse_x_){mouse_x=mouse_x_;}
	void SetMouseY(float mouse_y_){mouse_y=mouse_y_;}
};



class Member_KeyInput
{
	list<KeyinforBuf*>* list_member;
	int ping;
	int max_member;
public:
	Member_KeyInput();
	~Member_KeyInput();

	void InputKey(KeyinforBuf& temp);


};





class NetworkManager
{
	static NetworkManager* pInstance;


	HANDLE m_hCP;
	SOCKET m_lstnsock;
	char m_AcceptBuf[(sizeof(sockaddr_in)+16)*2];
	HWND m_hDlg;
	ACCEPTOVERLAPPED m_AOV;
	list<MYOVERLAPPED*> m_ltMOV;
	CRITICAL_SECTION m_cs;

	long m_lThreadCnt;

	string test;

	
	NetworkManager();
	NetworkManager(const NetworkManager* rhs);
	~NetworkManager();
public:
	static NetworkManager* CreateInstance();
	static void DestroyInstance(NetworkManager* pInstance_);
	
	bool init();


	BOOL CreateListenSocket();

	static unsigned __stdcall CommThread(void* pArguments);
	unsigned __stdcall InnerCommThread(void);

	
	void OnAccept(SOCKET commsock, char* AcceptBuf);
	void OnRead(MYOVERLAPPED* pMOV, char* buf, int nRead);
	void OnClose(MYOVERLAPPED* pMOV);
	void AddString(HWND hDlg, UINT nID, char* msg);


	const char* GetString(){
		EnterCriticalSection(&m_cs);
		const char* c = test.c_str();
		LeaveCriticalSection(&m_cs);
		return c;
	}
};



class NetworkClient
{
	SOCKET m_sock;

	static NetworkClient* pInstance;

	
	NetworkClient();
	NetworkClient(const NetworkClient* rhs);
	~NetworkClient();
public:
	static NetworkClient* CreateInstance();
	static void DestroyInstance(NetworkClient* pInstance_);

	bool init();

	bool sendtest(char* s);

};







#endif // __NETWORK_MANAGER_H__
