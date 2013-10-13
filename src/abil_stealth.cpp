//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_stealth.cpp
//
// 내용: 도둑걸음(늦게 발견)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_stealth.h"
#include "player.h"

Abil_stealth::Abil_stealth(int level_):
Ability("도둑걸음", level_, 3, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_stealth::~Abil_stealth()
{

}


Ability* Abil_stealth::Clone(int level_)
{
	return new Abil_stealth(level_);
}


const char* Abil_stealth::GetInfor()
{
	switch(level)
	{
	case 1:
		return "정면이 아니면 적에게 곧바로 들키지않음";
	case 2:
		return "정면이 아닐때 적에게 금방은 들키지않는 시간이 증가";
	case 3:
		return "정면이 아닐때 적에게 금방은 들키지않는 시간이 증가";
	}
	return "레벨 에러";
}


int Abil_stealth::GetTime()
{
	switch(level)
	{
	case 1:
		return 400;
	case 2:
		return 150;
	case 3:
		return 90;
	}
	return false;
}




bool Abil_stealth::ActivePlayer(Player* player_)
{
	player_->SetWarningTime(GetTime());
	return true;
}

bool Abil_stealth::UnActivePlayer(Player* player_)
{
	player_->SetWarningTime(1000);
	return false;
}