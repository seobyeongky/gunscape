//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_knowledge.cpp
//
// 내용: 선택능력 1씩 증가
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_knowledge.h"
#include "player.h"

Abil_knowledge::Abil_knowledge(int level_):
Ability("배경지식", level_, 3, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_knowledge::~Abil_knowledge()
{

}


Ability* Abil_knowledge::Clone(int level_)
{
	return new Abil_knowledge(level_);
}


const char* Abil_knowledge::GetInfor()
{
	switch(level)
	{
	case 1:
		return "레벨업시 선택하는 능력 갯수 최대치 1개 증가";
	case 2:
		return "레벨업시 선택하는 능력 갯수 최대치 2개 증가";
	case 3:
		return "레벨업시 선택하는 능력 갯수 최대치 3개 증가";
	}
	return "레벨 에러";
}

bool Abil_knowledge::ActivePlayer(Player* player_)
{
	player_->SetSelectAbilityNum(3+level);
	return true;
}

bool Abil_knowledge::UnActivePlayer(Player* player_)
{
	player_->SetSelectAbilityNum(3);
	return false;
}