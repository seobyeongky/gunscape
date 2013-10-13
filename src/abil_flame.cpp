//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_flame.cpp
//
// 내용: 능력-화염방사기마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_flame.h"
#include "main_weapon.h"

Abil_flame::Abil_flame(int level_):
Ability("파이로 테크닉", level_, 5, 50, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_flame::~Abil_flame()
{

}


Ability* Abil_flame::Clone(int level_)
{
	return new Abil_flame(level_);
}


const char* Abil_flame::GetInfor()
{
	switch(level)
	{
	case 1:
		return "화염방사기의 최대 탄수 8%증가, 사거리 증가";
	case 2:
		return "화염방사기의 최대 탄수 16%증가, 사거리 증가";
	case 3:
		return "화염방사기의 최대 탄수 24%증가, 사거리 증가";
	case 4:
		return "화염방사기의 최대 탄수 32%증가, 사거리 증가";
	case 5:
		return "화염방사기의 최대 탄수 40%증가, 사거리 증가";		
	}
	return "레벨 에러";
}


bool Abil_flame::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_FLAME_THROWER)
	{	
		weapon_->ApplyMaxBullet(1.0f+0.08f*level);
		weapon_->UpDownDistance(4.0f*level);
		return true;
	}
	return false;
}
bool Abil_flame::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_FLAME_THROWER)
	{
		weapon_->ApplyMaxBullet(1/(1.0f+0.08f*level));
		weapon_->UpDownDistance(-4.0f*level);
		return true;
	}
	return false;
}