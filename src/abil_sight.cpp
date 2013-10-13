//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_sight.cpp
//
// 내용: 시야증가
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_sight.h"
#include "player.h"

Abil_sight::Abil_sight(int level_):
Ability("망원경", level_, 3, 20, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_sight::~Abil_sight()
{

}


Ability* Abil_sight::Clone(int level_)
{
	return new Abil_sight(level_);
}


const char* Abil_sight::GetInfor()
{
	switch(level)
	{
	case 1:
		return "시야 증가";
	case 2:
		return "시야 증가";
	case 3:
		return "시야 증가";
	}
	return "레벨 에러";
}


bool Abil_sight::ActivePlayer(Player* player_)
{
	player_->UpDownSight(13.0f*level);
	return true;
}

bool Abil_sight::UnActivePlayer(Player* player_)
{
	player_->UpDownSight(-13.0f*level);
	return false;
}