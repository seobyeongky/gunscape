//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_shot_gun.cpp
//
// 내용: 능력-샷건마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_shot_gun.h"
#include "main_weapon.h"

Abil_shot_gun::Abil_shot_gun(int level_):
Ability("샷건 테크닉", level_, 5, 50, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_shot_gun::~Abil_shot_gun()
{

}


Ability* Abil_shot_gun::Clone(int level_)
{
	return new Abil_shot_gun(level_);
}


const char* Abil_shot_gun::GetInfor()
{
	switch(level)
	{
	case 1:
		return "샷건의 한번에 나가는 총알 갯수 1 증가, 넉백 증가";
	case 2:
		return "샷건의 한번에 나가는 총알 갯수 2 증가, 넉백 증가";
	case 3:
		return "샷건의 한번에 나가는 총알 갯수 3 증가, 넉백 증가";
	case 4:
		return "샷건의 한번에 나가는 총알 갯수 4 증가, 넉백 증가";
	case 5:
		return "샷건의 한번에 나가는 총알 갯수 5 증가, 넉백 증가";	
	}
	return "레벨 에러";
}


bool Abil_shot_gun::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_SHOTGUN)
	{	
		weapon_->UpDownBunch(level);
		weapon_->ApplyPower(1.0f-0.2f*level);
		weapon_->ApplyMaxPower(1.0f-0.2f*level);
		return true;
	}
	return false;
}
bool Abil_shot_gun::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_SHOTGUN)
	{
		weapon_->UpDownBunch(-level);
		weapon_->ApplyPower(1/(1.0f-0.2f*level));
		weapon_->ApplyMaxPower(1/(1.0f-0.2f*level));
		return true;
	}
	return false;
}