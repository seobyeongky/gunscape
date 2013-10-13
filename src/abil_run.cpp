//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_run.cpp
//
// 내용: 사용형 - 달리기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_run.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_piece.h"

Abil_run::Abil_run(int level_):
Ability("질주", level_,3, 100, 1, AT_USE),
run(false), count(0)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_run::~Abil_run()
{

}


Ability* Abil_run::Clone(int level_)
{
	return new Abil_run(level_);
}


const char* Abil_run::GetInfor()
{
	switch(level)
	{
	case 1:
		return "사용시 일시적 달리기 속도 20% 증가";
	case 2:
		return "사용시 일시적 달리기 속도 35% 증가";
	case 3:
		return "사용시 일시적 달리기 속도 50% 증가";
	}
	return "레벨 에러";
}
float Abil_run::GetSpeed()
{
	switch(level)
	{
	case 1:
		return 1.2f;
	case 2:
		return 1.35f;
	case 3:
		return 1.5f;
	}
	return false;
}
bool Abil_run::Action(Game_Manager* gm_, Player* player_)
{
	if(run)
	{
		player_->SetStaminaDelay(100);
		if(count%10 == 0)
		{
			Effect_run_afterimage(gm_, player_->GetTexture(), player_->GetPos(), player_->GetAngle(), 1.0f);
		}
		count++;
		if(!player_->UseStamina(0.4f))
		{
			UnUse(gm_, player_);
			return false;
		}
	}
	return true;
}
bool Abil_run::Use(Game_Manager* gm_, Player* player_)
{
	if(!run)
	{
		player_->ApplySpeed(GetSpeed());
		run = true;
		return true;
	}
	return false;
}
bool Abil_run::UnUse(Game_Manager* gm_, Player* player_)
{
	if(run)
	{
		player_->ApplySpeed(1/GetSpeed());
		run = false;
		return true;
	}
	return false;
}