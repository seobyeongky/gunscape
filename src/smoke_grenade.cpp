//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: smoke_grenade.cpp
//
// 내용: 서브아이템. 수류탄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "smoke_grenade.h"
#include "texture_list.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_smoke_bomb.h"

Sub_Smoke_Grenade::Sub_Smoke_Grenade(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "연막탄", "연막을 만드는 수류탄\n이동속도와 시야를 줄임", pos_, time_, user_, &tex_inter_bomb, 4, 5.0f)
{

}
Sub_Smoke_Grenade::~Sub_Smoke_Grenade()
{

}

float Sub_Smoke_Grenade::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float distan_ = distan_coord(start_, pos_);
	coord_def target_ = pos_;
	if(distan_ > 100)
	{
		coord_def temp_ = target_ - start_;
		temp_ = temp_/distan_*100.0f;
		target_ = temp_ + start_;
	}
	float angle_ = GetAngleToTarget(start_, pos_);
	gm_->shot_list.push_back(new Shot_smoke_bomb(&tex_grenade, User_, 30, 300, 40.f, team_, start_, target_));
	if(!UpDownNum(-1))
	{
		GetPlayer()->DeleteSubWeapon(this, -1);
		delete this; //끝나면 이걸 지움. 제대로 동작되나?
	}
	return 0;
}