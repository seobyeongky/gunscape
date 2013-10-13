//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_fire.cpp
//
// 내용: 화염방어공격 증가
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_fire.h"
#include "player.h"
#include "main_weapon.h"

Abil_fire::Abil_fire(int level_):
Ability("지옥불", level_, 3, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_fire::~Abil_fire()
{

}


Ability* Abil_fire::Clone(int level_)
{
	return new Abil_fire(level_);
}

const char* Abil_fire::GetInfor()
{
	switch(level)
	{
	case 1:
		return "화염방어력 25%증가";
	case 2:
		return "화염방어력 50%증가. 방사기공격력 10%증가";
	case 3:
		return "화염방어력 50%증가. 방사기공격력 30%증가.";
	}
	return "레벨 에러";
}


bool Abil_fire::ActivePlayer(Player* player_)
{
	player_->ApplyDefense(DT_FIRE, level==1?0.75f:0.5f);
	return true;
}
bool Abil_fire::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(level>1 && weapon_->GetType() == WT_FLAME_THROWER)
	{	
		weapon_->ApplyDamegeApply(level==1?1.10f:1.30f);
		return true;
	}
	return false;
}

bool Abil_fire::UnActivePlayer(Player* player_)
{
	player_->ApplyDefense(DT_FIRE, level==1?1/0.75f:2.0f);
	return false;
}
bool Abil_fire::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(level>1 && weapon_->GetType() == WT_FLAME_THROWER)
	{
		weapon_->ApplyDamegeApply(level==1?1/1.10f:1/1.30f);
		return true;
	}
	return false;
}