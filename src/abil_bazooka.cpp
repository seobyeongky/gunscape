//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_bazooka.cpp
//
// 내용: 능력-바주카마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_bazooka.h"
#include "main_weapon.h"

Abil_bazooka::Abil_bazooka(int level_):
Ability("바주카 테크닉", level_, 5, 50, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_bazooka::~Abil_bazooka()
{

}


Ability* Abil_bazooka::Clone(int level_)
{
	return new Abil_bazooka(level_);
}


const char* Abil_bazooka::GetInfor()
{
	switch(level)
	{
	case 1:
		return "바주카의 사격속도, 총알속도증가. 장전시간 감소";
	case 2:
		return "바주카의 사격속도, 총알속도증가. 장전시간 감소";
	case 3:
		return "바주카의 사격속도, 총알속도증가. 장전시간 감소";
	case 4:
		return "바주카의 사격속도, 총알속도증가. 장전시간 감소";
	case 5:
		return "바주카의 사격속도, 총알속도증가. 장전시간 감소";
	}
	return "레벨 에러";
}


bool Abil_bazooka::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_BAZOOKA)
	{	
		weapon_->ApplyBurstSpeedApply(1.0f+0.1f*level);
		weapon_->ApplyShotSpeedApply(1.0f+0.1f*level);
		weapon_->ApplyReloadSpeed(1.0f-0.1f*level);
		return true;
	}
	return false;
}
bool Abil_bazooka::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_BAZOOKA)
	{
		weapon_->ApplyBurstSpeedApply(1/(1.0f+0.1f*level));
		weapon_->ApplyShotSpeedApply(1/(1.0f+0.1f*level));
		weapon_->ApplyReloadSpeed(1/(1.0f-0.1f*level));
		return true;
	}
	return false;
}