//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_pistol.cpp
//
// 내용: 능력-권총마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_pistol.h"
#include "main_weapon.h"

Abil_pistol::Abil_pistol(int level_):
Ability("권총 테크닉", level_, 5, 50, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_pistol::~Abil_pistol()
{

}


Ability* Abil_pistol::Clone(int level_)
{
	return new Abil_pistol(level_);
}


const char* Abil_pistol::GetInfor()
{
	switch(level)
	{
	case 1:
		return "권총의 최대 탄수 1증가, 반동 감소, 사격속도 증가";
	case 2:
		return "권총의 최대 탄수 2증가, 반동 감소, 사격속도 증가";
	case 3:
		return "권총의 최대 탄수 3증가, 반동 감소, 사격속도 증가";
	case 4:
		return "권총의 최대 탄수 4증가, 반동 감소, 사격속도 증가";
	case 5:
		return "권총의 최대 탄수 5증가, 반동 감소, 사격속도 증가";	
	}
	return "레벨 에러";
}


bool Abil_pistol::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_PISTOL)
	{	
		weapon_->SetMaxBullet(weapon_->GetMaxBullet()+level);
		weapon_->ApplyFocusReact(1.0f-0.1f*level);
		weapon_->ApplyBurstSpeedApply(1.0f+0.1f*level);
		return true;
	}
	return false;
}
bool Abil_pistol::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_PISTOL)
	{
		weapon_->SetMaxBullet(weapon_->GetMaxBullet()-level);
		weapon_->ApplyFocusReact(1/(1.0f-0.1f*level));
		weapon_->ApplyBurstSpeedApply(1/(1.0f+0.1f*level));
		return true;
	}
	return false;
}