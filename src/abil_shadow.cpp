//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_shadow.cpp
//
// 내용: 인식범위 대폭감소(레어)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_shadow.h"
#include "player.h"

Abil_shadow::Abil_shadow(int level_):
Ability("그림자걷기", level_, 2, 5, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_shadow::~Abil_shadow()
{

}


Ability* Abil_shadow::Clone(int level_)
{
	return new Abil_shadow(level_);
}


const char* Abil_shadow::GetInfor()
{
	switch(level)
	{
	case 1:
		return "적들의 인식 범위 감소";
	case 2:
		return "적들의 인식 범위 감소";
	}
	return "레벨 에러";
}


float Abil_shadow::GetValue()
{
	switch(level)
	{
	case 1:
		return 0.8f;
	case 2:
		return 0.6f;
	}
	return false;
}


bool Abil_shadow::ActivePlayer(Player* player_)
{
	player_->ApplySneak(VT_ALL,GetValue());
	return true;
}

bool Abil_shadow::UnActivePlayer(Player* player_)
{
	player_->ApplySneak(VT_ALL,1/GetValue());
	return false;
}