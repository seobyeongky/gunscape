//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_knife.cpp
//
// 내용: 능력-나이프마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_knife.h"
#include "melee_weapon.h"
#include "main_weapon.h"

Abil_knife::Abil_knife(int level_):
Ability("암살기술", level_, 4, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_knife::~Abil_knife()
{

}


Ability* Abil_knife::Clone(int level_)
{
	return new Abil_knife(level_);
}


const char* Abil_knife::GetInfor()
{
	switch(level)
	{
	case 1:
		return "모든 백스탭, 헤드샷 데미지 1.25배";
	case 2:
		return "모든 백스탭, 헤드샷 데미지 1.5배";
	case 3:
		return "모든 백스탭, 헤드샷 데미지 2배";
	case 4:
		return "모든 백스탭, 헤드샷 데미지 2.5배";
	}
	return "레벨 에러";
}
float Abil_knife::GetDamage()
{
	switch(level)
	{
	case 1:
		return 1.25f;
	case 2:
		return 1.5f;
	case 3:
		return 2.0f;
	case 4:
		return 2.5f;
	}
	return false;
}


bool Abil_knife::ActiveMeleeWeapon(Melee_Weapon* weapon_)
{
	if(weapon_->GetBackStab()>1.0f)
		weapon_->ApplyBackStab(GetDamage());
	return false;
}
bool Abil_knife::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetSniper()>1.0f)
		weapon_->ApplySniper(GetDamage());
	return false;
}
bool Abil_knife::UnActiveMeleeWeapon(Melee_Weapon* weapon_)
{
	if(weapon_->GetBackStab()>1.0f)
		weapon_->ApplyBackStab(1/GetDamage());
	return false;
}
bool Abil_knife::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetSniper()>1.0f)
		weapon_->ApplySniper(1/GetDamage());
	return false;
}