//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_whirlwind.cpp
//
// 내용: 능력-나이프마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_whirlwind.h"
#include "melee_weapon.h"
#include "main_weapon.h"

Abil_whirlwind::Abil_whirlwind(int level_):
Ability("휠윈드", level_, 2, 30, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_whirlwind::~Abil_whirlwind()
{

}


Ability* Abil_whirlwind::Clone(int level_)
{
	return new Abil_whirlwind(level_);
}


const char* Abil_whirlwind::GetInfor()
{
	switch(level)
	{
	case 1:
		return "근접 무기가 전방향을 공격하게 된다";
	case 2:
		return "근접 무기가 전방향을 공격하고 사거리가 1.5배가 된다";
	}
	return "레벨 에러";
}


bool Abil_whirlwind::ActiveMeleeWeapon(Melee_Weapon* weapon_)
{
	if(weapon_->GetWWPannalty())
	{
		weapon_->ApplyWidth(10.0f);
		weapon_->ApplyBurstSpeedApply(1/weapon_->GetWWPannalty());
	}
	if(level == 2)
		weapon_->ApplyDistance(1.5f);
	return false;
}

bool Abil_whirlwind::UnActiveMeleeWeapon(Melee_Weapon* weapon_)
{
	if(weapon_->GetWWPannalty())
	{
		weapon_->ApplyWidth(1/10.0f);
		weapon_->ApplyBurstSpeedApply(weapon_->GetWWPannalty());
	}
	if(level == 2)
		weapon_->ApplyDistance(1/1.5f);
	return false;
}