//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: burrow2.cpp
//
// 내용: 맵이 너무 넓어서 ai매니저를 부하줄이기위해 멀면 정지
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "burrow2.h"
#include "random.h"
#include "player.h"

#include "gamemanager.h"
#include "map.h"
#include "monster_list.h"
#include "monster.h"

#include "effect_piece.h"


Burrow2::Burrow2(coord_def pos_, int time_, Monster_Index mon_):
Unit("숨엇어요", NULL, pos_.x, pos_.y, -1, 0),
sleep(false), mon(mon_)
{
	SetSize(250.0f);
}


Burrow2::~Burrow2()
{

}

bool Burrow2::Action_in(Game_Manager* gm_)
{
	if(gm_)
	{
		if(gm_->player->collution(GetPos(), GetSize()))
		{
			Unit* temp = New_Monster(mon, GetPos(), -1, 0, 0);
			gm_->unit_list.push_back(temp);
			if(sleep)
				temp->Sleep();
			return true;
		}
	}

	return false;
}

void Burrow2::Sleep()
{
	sleep = true;
}