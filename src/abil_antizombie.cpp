//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_antizombie.cpp
//
// ����: ����������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_antizombie.h"
#include "player.h"
#include "gamemanager.h"
#include "effect_piece.h"

Abil_antizombie::Abil_antizombie(int level_):
Ability("����������", level_, 3, 100, 1, AT_PASSIVE),
	count(0)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_antizombie::~Abil_antizombie()
{

}


Ability* Abil_antizombie::Clone(int level_)
{
	return new Abil_antizombie(level_);
}


const char* Abil_antizombie::GetInfor()
{
	switch(level)
	{
	case 1:
		return "�ֺ� ������ ���� ������ �̵��ӵ� 10% ����";
	case 2:
		return "�ֺ� ������ ���� ������ �̵��ӵ� 20% ����";
	case 3:
		return "�ֺ� ������ ���� ������ �̵��ӵ� 30% ����";
	}
	return "���� ����";
}

float Abil_antizombie::GetSpeed()
{
	switch(level)
	{
	case 1:
		return 0.9f;
	case 2:
		return 0.8f;
	case 3:
		return 0.7f;
	}
	return false;
}

float Abil_antizombie::GetRange()
{
	switch(level)
	{
	case 1:
		return 70.0f;
	case 2:
		return 80.0f;
	case 3:
		return 90.0f;
	}
	return false;
}

bool Abil_antizombie::Action(Game_Manager* gm_, Player* player_)
{
	if(count%10==0)
	{
		for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
		{
			if((*it)->isLive() && !(*it)->isNonTarget() && (*it)->GetKind() == VT_ZOMBIE)
			{
				if((*it)->GetTeam() != player_->GetTeam())
				{
					if((*it)->collution(player_->GetPos(),GetRange()))
					{						
						(*it)->SlowApply(GetSpeed(),20, SK_ANTI_ZOMBIE);
					}
				}
			}
		}

	}
	count++;
	return true;
}

bool Abil_antizombie::ActiveGame(Game_Manager* gm_, Player* player_)
{
	Effect_range(gm_, player_->GetPos(),GetRange(),D3DCOLOR_ARGB(128,255,0,0));
	return true;
}