//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_health.cpp
//
// 내용: 체력 증가
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_health.h"
#include "player.h"

Abil_health::Abil_health(int level_):
Ability("맷집", level_, 5, 50, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_health::~Abil_health()
{

}


Ability* Abil_health::Clone(int level_)
{
	return new Abil_health(level_);
}


int Abil_health::GetHp()
{
	switch(level)
	{
	case 1:
		return 10;
	case 2:
		return 25;
	case 3:
		return 45;
	case 4:
		return 70;
	case 5:
		return 100;
	}
	return false;
}



const char* Abil_health::GetInfor()
{
	static char temp[32];
	sprintf_s(temp,32,"최대 체력 %d증가",GetHp());
	return temp;
}


bool Abil_health::ActivePlayer(Player* player_)
{
	player_->UpDownMaxHp(GetHp());
	player_->Heal(GetHp());
	return true;
}

bool Abil_health::UnActivePlayer(Player* player_)
{
	player_->UpDownMaxHp(-GetHp());
	player_->UpDownHp(-GetHp());
	return false;
}