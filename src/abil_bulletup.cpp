//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_bulletup.cpp
//
// 내용: 능력-탄창 증가
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_bulletup.h"
#include "main_weapon.h"

Abil_bulletup::Abil_bulletup(int level_):
Ability("탄창증가", level_, 5, 30, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_bulletup::~Abil_bulletup()
{

}


Ability* Abil_bulletup::Clone(int level_)
{
	return new Abil_bulletup(level_);
}



const char* Abil_bulletup::GetInfor()
{
	switch(level)
	{
	case 1:
		return "최대탄수 20%증가";
	case 2:
		return "최대탄수 40%증가";
	case 3:
		return "최대탄수 60%증가";
	case 4:
		return "최대탄수 80%증가";
	case 5:
		return "최대탄수 100%증가";
	}
	return "레벨 에러";
}



bool Abil_bulletup::ActiveMainWeapon(Main_Weapon* weapon_)
{
	weapon_->ApplyMaxBullet(1.0f+0.2f*level);
	return true;
}
bool Abil_bulletup::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	weapon_->ApplyMaxBullet(1/(1.0f+0.2f*level));
	return true;
}