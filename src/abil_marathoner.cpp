//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_marathoner.cpp
//
// 내용: 체력 증가
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_marathoner.h"
#include "player.h"

Abil_marathoner::Abil_marathoner(int level_):
Ability("마라토너", level_, 5, 50, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_marathoner::~Abil_marathoner()
{

}


Ability* Abil_marathoner::Clone(int level_)
{
	return new Abil_marathoner(level_);
}


float Abil_marathoner::GetSp()
{
	switch(level)
	{
	case 1:
		return 30.0f;
	case 2:
		return 60.0f;
	case 3:
		return 100.0f;
	case 4:
		return 150.0f;
	case 5:
		return 200.0f;
	}
	return false;
}



const char* Abil_marathoner::GetInfor()
{
	static char temp[32];
	sprintf_s(temp,32,"최대 스태미나 %g%%증가",GetSp());
	return temp;
}


bool Abil_marathoner::ActivePlayer(Player* player_)
{
	player_->UpDownMaxStamina(GetSp());
	player_->UpDownStamina(GetSp());
	return true;
}

bool Abil_marathoner::UnActivePlayer(Player* player_)
{
	player_->UpDownMaxStamina(-GetSp());
	player_->UpDownStamina(-GetSp());
	return false;
}