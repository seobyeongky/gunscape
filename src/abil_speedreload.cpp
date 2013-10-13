//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_speedreload.cpp
//
// 내용: 능력-빠른 장전
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_speedreload.h"
#include "main_weapon.h"

Abil_speedreload::Abil_speedreload(int level_):
Ability("스피드리로드", level_, 3, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_speedreload::~Abil_speedreload()
{

}


Ability* Abil_speedreload::Clone(int level_)
{
	return new Abil_speedreload(level_);
}


float Abil_speedreload::GetSpeed()
{
	switch(level)
	{
	case 1:
		return 0.8f;
	case 2:
		return 0.6f;
	case 3:
		return 0.25f;
	}
	return false;
}


const char* Abil_speedreload::GetInfor()
{
	switch(level)
	{
	case 1:
		return "장전 속도 20%감소";
	case 2:
		return "장전 속도 40%감소";
	case 3:
		return "장전 속도 75%감소";
	}
	return "레벨 에러";
}


bool Abil_speedreload::ActiveMainWeapon(Main_Weapon* weapon_)
{
	weapon_->ApplyReloadSpeed(GetSpeed());
	return true;
}
bool Abil_speedreload::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	weapon_->ApplyReloadSpeed(1/GetSpeed());
	return true;
}