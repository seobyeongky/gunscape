//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_deathbomb.cpp
//
// 내용: 연쇄폭발
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_deathbomb.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_bomb.h"
#include "monster.h"

Abil_deathbomb::Abil_deathbomb(int level_):
Ability("연쇄폭발", level_, 4, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_deathbomb::~Abil_deathbomb()
{

}


Ability* Abil_deathbomb::Clone(int level_)
{
	return new Abil_deathbomb(level_);
}


const char* Abil_deathbomb::GetInfor()
{
	switch(level)
	{
	case 1:
		return "적을 죽일때마다 폭발을 일으켜 주변의 적에게 데미지를 준다";
	case 2:
		return "적을 죽일때마다 폭발을 일으켜 주변의 적에게 데미지를 준다";
	case 3:
		return "적을 죽일때마다 폭발을 일으켜 주변의 적에게 데미지를 준다";
	case 4:
		return "적을 죽일때마다 폭발을 일으켜 주변의 적에게 데미지를 준다";
	}
	return "레벨 에러";
}

float Abil_deathbomb::GetDamage()
{
	switch(level)
	{
	case 1:
		return 15.0f;
	case 2:
		return 25.0f;
	case 3:
		return 40.0f;
	case 4:
		return 80.0f;
	}
	return false;
}
float Abil_deathbomb::GetRange()
{
	switch(level)
	{
	case 1:
		return 15.0f;
	case 2:
		return 20.0f;
	case 3:
		return 25.0f;
	case 4:
		return 40.0f;
	}
	return false;
}
bool Abil_deathbomb::KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_)
{
	gm_->shot_list.push_back(new Shot_bomb(player_, monster_->GetPos(), GetDamage(), 1.0f, 2.0f, GetRange(), player_->GetTeam()));			

	return true;
}