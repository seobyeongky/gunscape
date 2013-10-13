//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: network_memberkey.cpp
//
// 내용: 네트워크 키 저장 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "networkmanager.h"

Member_KeyInput::Member_KeyInput():ping(10),max_member(8)
{
	list_member = new list<KeyinforBuf*>[max_member];
}

Member_KeyInput::~Member_KeyInput()
{
	for(int i=0;i<max_member;i++)
	{
		for(list<KeyinforBuf*>::iterator it = list_member[i].begin(); it!=list_member[i].end(); it++)
		{
			delete (*it);	
		}
	}
	delete[] list_member;
}


void Member_KeyInput::InputKey(KeyinforBuf& temp)
{
	int team = temp.GetTeam();
	if(team)
	{
		list<KeyinforBuf*>::iterator it;
		for(it = list_member[team].begin(); it!=list_member[team].end(); it++)
		{
			int big = (*it)->thenBig(temp.GetIndex());
			if(big == -1)
			{
				throw; //여기로 들어가면 에러임. 확실히 잡기
			}
			else if(big == 0)
			{
				break;
			}
		}
		KeyinforBuf *new_key = new KeyinforBuf(temp);
		list_member[team].insert(it,new_key);
	}
}


