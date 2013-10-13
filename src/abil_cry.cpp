//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_cry.cpp
//
// 내용: 사용형 - 외침
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_cry.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_piece.h"

Abil_cry::Abil_cry(int level_):
Ability("괴성", level_,3, 100, 1, AT_USE),
delay(0)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_cry::~Abil_cry()
{

}


Ability* Abil_cry::Clone(int level_)
{
	return new Abil_cry(level_);
}


const char* Abil_cry::GetInfor()
{
	switch(level)
	{
	case 1:
		return "주변의 적에게 넉백과 스턴. 큰 소음이 난다.";
	case 2:
		return "주변의 적에게 넉백과 스턴. 큰 소음이 난다.";
	case 3:
		return "주변의 적에게 넉백과 스턴. 큰 소음이 난다.";
	}
	return "레벨 에러";
}
float Abil_cry::GetSp()
{
	switch(level)
	{
	case 1:
		return 30.0f;
	case 2:
		return 30.0f;
	case 3:
		return 30.0f;
	}
	return false;
}
int Abil_cry::GetStun()
{
	switch(level)
	{
	case 1:
		return 40;
	case 2:
		return 75;
	case 3:
		return 100;
	}
	return false;
}
bool Abil_cry::Action(Game_Manager* gm_, Player* player_)
{
	if(delay)
		delay--;
	return true;
}


bool Abil_cry::Use(Game_Manager* gm_, Player* player_)
{
	if(!delay)
	{
		if(player_->UseStamina(GetSp()))
		{
			player_->SetStaminaDelay(100);
			//player_->SlowApply(1.5f, 100);

			for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
			{
				if((*it)->isLive() && !(*it)->isNonTarget())
				{
					if((*it)->GetTeam() != player_->GetTeam())
					{
						if((*it)->collution(player_->GetPos(),70.0f))
						{
							if(!gm_->map->CollutionPosToPos(player_->GetPos(), (*it)->GetPos()))
							{
								(*it)->SetKnockback(5.0f, 5.0f, GetAngleToTarget(player_->GetPos(), (*it)->GetPos()));
								(*it)->SetStop(GetStun());
							}
						}
					}
				}
			}
			Effect_cry(gm_, player_->GetPos(),70.0f);
			gm_->Noise(player_->GetTeam(),player_->GetPos(),150.0f);
			delay = 30;
			player_->SetDelay(30);
			return true;
		}
	}
	return false;
}