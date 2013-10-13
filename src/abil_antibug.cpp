//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_antibug.cpp
//
// 내용: 벌레 인식범위 감소
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_antibug.h"
#include "player.h"

Abil_antibug::Abil_antibug(int level_):
Ability("벌레방지약", level_, 2, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_antibug::~Abil_antibug()
{

}


Ability* Abil_antibug::Clone(int level_)
{
	return new Abil_antibug(level_);
}


const char* Abil_antibug::GetInfor()
{
	switch(level)
	{
	case 1:
		return "벌레들의 인식 범위 감소";
	case 2:
		return "벌레들의 인식 범위 대폭 감소";
	}
	return "레벨 에러";
}


float Abil_antibug::GetValue()
{
	switch(level)
	{
	case 1:
		return 0.7f;
	case 2:
		return 0.4f;
	}
	return false;
}


bool Abil_antibug::ActivePlayer(Player* player_)
{
	player_->ApplySneak(VT_BUG,GetValue());
	return true;
}

bool Abil_antibug::UnActivePlayer(Player* player_)
{
	player_->ApplySneak(VT_BUG,1/GetValue());
	return false;
}