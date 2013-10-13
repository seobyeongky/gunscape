//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: throw_knife.cpp
//
// 내용: 서브아이템. 투척나이프
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "throw_knife.h"
#include "texture_list.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_normal.h"
#include "sound.h"

Sub_Throw_knife::Sub_Throw_knife(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "투척나이프", "던지는 단검", pos_, time_, user_, &tex_inter_knife, 20, 5.0f)
{

}
Sub_Throw_knife::~Sub_Throw_knife()
{

}

float Sub_Throw_knife::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
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
	PlaySE(se_knife, false);
	gm_->shot_list.push_back(new Shot_normal(&tex_throw_knife, User_, 10, 0.5f, 4.0f, team_, start_, angle_, 5.0f, 100));
	if(!UpDownNum(-1))
	{
		GetPlayer()->DeleteSubWeapon(this, -1);
		delete this; //끝나면 이걸 지움. 제대로 동작되나?
	}
	return 10;
}