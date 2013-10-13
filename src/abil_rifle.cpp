//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_rifle.cpp
//
// 내용: 능력-라이플마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_rifle.h"
#include "main_weapon.h"

Abil_rifle::Abil_rifle(int level_):
Ability("라이플 테크닉", level_, 5, 50, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_rifle::~Abil_rifle()
{

}


Ability* Abil_rifle::Clone(int level_)
{
	return new Abil_rifle(level_);
}


const char* Abil_rifle::GetInfor()
{
	switch(level)
	{
	case 1:
		return "라이플의 최대 탄수 8%증가, 반동 감소";
	case 2:
		return "라이플의 최대 탄수 16%증가, 반동 감소";
	case 3:
		return "라이플의 최대 탄수 24%증가, 반동 감소";
	case 4:
		return "라이플의 최대 탄수 32%증가, 반동 감소";
	case 5:
		return "라이플의 최대 탄수 40%증가, 반동 감소";	
	}
	return "레벨 에러";
}


bool Abil_rifle::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_RIFLE)
	{	
		weapon_->ApplyMaxBullet(1.0f+0.08f*level);
		weapon_->ApplyFocusReact(1.0f-0.1f*level);
		return true;
	}
	return false;
}
bool Abil_rifle::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_RIFLE)
	{
		weapon_->ApplyMaxBullet(1/(1.0f+0.08f*level));
		weapon_->ApplyFocusReact(1/(1.0f-0.1f*level));
		return true;
	}
	return false;
}