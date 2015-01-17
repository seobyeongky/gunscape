//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: box.cpp
//
// 내용: 보급상자클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "box.h"
#include "random.h"

#include "main_weapon_list.h"
#include "melee_weapon_list.h"
#include "sub_weapon_list.h"
#include "instant_list.h"
#include "gamemanager.h"
#include "sound.h"

Box::Box(Texture* texture_, coord_def pos_, int level_):
Unit("상자",texture_, pos_.x, pos_.y, -1, 20),
level(level_)
{
	SetSize(5.0f);
}


Box::~Box()
{

}

bool Box::Action_in(Game_Manager* gm_)
{
	if(!isLive())
	{
		DropItem(gm_);
		return true;
	}

	CommonAction(gm_);
	return false;
}



bool Box::DropItem(Game_Manager* gm_)
{
	Item* drop_item_ = NULL;

	if(gm_->Heal_percent(true)){
		drop_item_ = New_Instant(IK_HEAL, GetPos(), 1000);
	}
	else{
		switch(rand_int(0,5,"Box::DropItem main weapon selector"))
		{
		case 0:
			drop_item_ = New_Main_Weapon((Main_Weapon_Kind)randA(MWK_MAX,"Box::DropItem main weapon selector"), GetPos(), -1);
			break;
		case 1:
		case 2:
		case 3:
			drop_item_ = New_Sub_Weapon((Sub_Weapon_Kind)randA(SWK_MAX,"Box::DropItem sub weapon selector"), NULL, GetPos(), -1);
			break;
		case 4:
			drop_item_ = New_Melee_Weapon((Melee_Kind)randA(MK_MAX,"Box::DropItem melee weapon selector"), GetPos(), -1);
			break;
		case 5:
			drop_item_ = New_Instant(IK_BULLET, GetPos(), 1000);
			break;
		}
	}

	if(drop_item_)
	{
		gm_->item_list.push_back(drop_item_);
		return true;
	}
	else
		return false;

}



void Box::Death(Game_Manager* gm_)
{
	if (gm_->isPlayerCanHear(GetPos()))
	{
		PlaySE3(se_item1, se_item2, se_item3);
	}
}