//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_see_sight.cpp
//
// 내용: 시야보기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_see_sight.h"
#include "player.h"

Abil_see_sight::Abil_see_sight(int level_):
Ability("위험감지", level_, 1, 50, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_see_sight::~Abil_see_sight()
{

}


Ability* Abil_see_sight::Clone(int level_)
{
	return new Abil_see_sight(level_);
}


const char* Abil_see_sight::GetInfor()
{
	switch(level)
	{
	case 1:
		return "적의 시야를 알 수 있다.";
	}
	return "레벨 에러";
}

bool Abil_see_sight::ActivePlayer(Player* player_)
{
	player_->SetMonSightView(true);
	return true;
}

bool Abil_see_sight::UnActivePlayer(Player* player_)
{
	player_->SetMonSightView(false);
	return false;
}

