//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: obj_barricade.cpp
//
// 내용: 바리케이트 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "obj_barricade.h"
#include "random.h"

#include "main_weapon_list.h"
#include "melee_weapon_list.h"
#include "sub_weapon_list.h"
#include "instant_list.h"
#include "gamemanager.h"


Barricade::Barricade(Texture* texture_, coord_def pos_, int health_, int time_, int team_):
Unit("바리케이트",texture_, pos_.x, pos_.y, team_, health_),
time(time_)
{
	SetFixed(true);
	SetSize(8.0f);
}


Barricade::~Barricade()
{

}

bool Barricade::Action_in(Game_Manager* gm_)
{	
	if(!isLive())
	{
		return true;
	}
	if(time--<=0)
	{
		SetHp(0);
		return true;
	}

	CommonAction(gm_);
	return false;
}



bool Barricade::DropItem(Game_Manager* gm_)
{
	return false;
}