//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_fast_portal.cpp
//
// 내용: 빠른 포탈
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_fast_portal.h"
#include "player.h"
#include "gamemanager.h"
#include "item.h"

Abil_fast_portal::Abil_fast_portal(int level_):
Ability("하이패스", level_, 2, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_fast_portal::~Abil_fast_portal()
{

}


Ability* Abil_fast_portal::Clone(int level_)
{
	return new Abil_fast_portal(level_);
}


const char* Abil_fast_portal::GetInfor()
{
	switch(level)
	{
	case 1:
		return "포탈진입시간 50%감소. 탈출이 쉬워진다.";
	case 2:
		return "포탈진입시간 90%감소. 탈출이 더욱 쉬워진다.";
	}
	return "레벨 에러";
}


bool Abil_fast_portal::ActiveGame(Game_Manager* gm_, Player* player_)
{
	if(gm_->GetCurrentStage() == SS_LAST)
	{
		int	left_switch = 4-level;
		for(list<Item*>::iterator it = gm_->item_list.begin();it != gm_->item_list.end();it++)
		{
			if(!strcmp((*it)->GetName(),"스위치"))
			{
				left_switch--;
				if(left_switch == 0 || !(*it)->is_On())
				{
					(*it)->Erase();
					break;
				}
			}
		}
	}
	return true;
}

bool Abil_fast_portal::ActivePlayer(Player* player_)
{
	player_->SetSwitch(3-level);
	player_->SetPortalTime(level==1?2:10);
	return true;
}

bool Abil_fast_portal::UnActivePlayer(Player* player_)
{
	player_->SetPortalTime(1);
	return false;
}