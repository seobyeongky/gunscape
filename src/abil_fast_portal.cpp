//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_fast_portal.cpp
//
// ����: ���� ��Ż
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_fast_portal.h"
#include "player.h"
#include "gamemanager.h"
#include "item.h"

Abil_fast_portal::Abil_fast_portal(int level_):
Ability("�����н�", level_, 2, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
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
		return "��Ż���Խð� 50%����. Ż���� ��������.";
	case 2:
		return "��Ż���Խð� 90%����. Ż���� ���� ��������.";
	}
	return "���� ����";
}


bool Abil_fast_portal::ActiveGame(Game_Manager* gm_, Player* player_)
{
	if(gm_->GetCurrentStage() == SS_LAST)
	{
		int	left_switch = 4-level;
		for(list<Item*>::iterator it = gm_->item_list.begin();it != gm_->item_list.end();it++)
		{
			if(!strcmp((*it)->GetName(),"����ġ"))
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