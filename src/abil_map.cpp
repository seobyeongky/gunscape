//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_map.cpp
//
// 내용: 시야보기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_map.h"
#include "player.h"

Abil_map::Abil_map(int level_):
Ability("지도", level_, 1, 5, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_map::~Abil_map()
{

}


Ability* Abil_map::Clone(int level_)
{
	return new Abil_map(level_);
}


const char* Abil_map::GetInfor()
{
	switch(level)
	{
	case 1:
		return "언제나 맵 전체와 포탈의 위치를 확인 할 수 있다.";
	}
	return "레벨 에러";
}

bool Abil_map::ActivePlayer(Player* player_)
{
	player_->SetMapHack(true);
	return true;
}

bool Abil_map::UnActivePlayer(Player* player_)
{
	player_->SetMapHack(false);
	return false;
}