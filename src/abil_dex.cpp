//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_dex.cpp
//
// 내용: 속도 증가
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_dex.h"
#include "player.h"

Abil_dex::Abil_dex(int level_):
Ability("날렵함", level_, 5, 30, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_dex::~Abil_dex()
{

}


Ability* Abil_dex::Clone(int level_)
{
	return new Abil_dex(level_);
}


const char* Abil_dex::GetInfor()
{
	switch(level)
	{
	case 1:
		return "이동속도 10% 증가";
	case 2:
		return "이동속도 20% 증가";
	case 3:
		return "이동속도 35% 증가";
	case 4:
		return "이동속도 50% 증가";
	case 5:
		return "이동속도 70% 증가";
	}
	return "레벨 에러";
}

float Abil_dex::GetSpeed()
{
	switch(level)
	{
	case 1:
		return 1.1f;
	case 2:
		return 1.2f;
	case 3:
		return 1.35f;
	case 4:
		return 1.5f;
	case 5:
		return 1.7f;
	}
	return false;
}


bool Abil_dex::ActivePlayer(Player* player_)
{
	player_->ApplySpeed(GetSpeed());
	return true;
}

bool Abil_dex::UnActivePlayer(Player* player_)
{
	player_->ApplySpeed(1/GetSpeed());
	return false;
}