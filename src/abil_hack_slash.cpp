//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_hack_slash.cpp
//
// 내용: 
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_hack_slash.h"
#include "player.h"
#include "gamemanager.h"

Abil_hack_slash::Abil_hack_slash(int level_):
Ability("핵앤슬래쉬", level_, 5, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_hack_slash::~Abil_hack_slash()
{

}


Ability* Abil_hack_slash::Clone(int level_)
{
	return new Abil_hack_slash(level_);
}


const char* Abil_hack_slash::GetInfor()
{
	switch(level)
	{
	case 1:
		return "적을 죽일때마다 3초간 공격력이 20%증가(중첩가능)";
	case 2:
		return "적을 죽일때마다 4초간 공격력이 20%증가(중첩가능)";
	case 3:
		return "적을 죽일마다 5초간 공격력이 30%증가(중첩가능)";
	case 4:
		return "적을 죽일마다 6초간 공격력이 30%증가(중첩가능)";
	case 5:
		return "적을 죽일마다 7초간 공격력이 40%증가(중첩가능)";
	}
	return "레벨 에러";
}

int Abil_hack_slash::Getsecond()
{
	switch(level)
	{
	case 1:
		return 180;
	case 2:
		return 240;
	case 3:
		return 300;
	case 4:
		return 360;
	case 5:
		return 420;
	}
	return false;
}
float Abil_hack_slash::Getattack()
{
	switch(level)
	{
	case 1:
		return 1.2f;
	case 2:
		return 1.2f;
	case 3:
		return 1.3f;
	case 4:
		return 1.3f;
	case 5:
		return 1.4f;
	}
	return false;
}
bool Abil_hack_slash::KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_)
{
	player_->AttackApply(Getattack(),Getsecond(),ABK_HACK_SLASH);
	player_->StateApply("핵앤슬래쉬",Getsecond());
	return true;
}

