//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: hammer.cpp
//
// 내용: 근접무기 햄머!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "hammer.h"
#include "texture_list.h"
#include "gamemanager.h"
#include "player.h"
#include "shot_hammer.h"

Melee_Hammer::Melee_Hammer(const melee_weapon_infor& infor_, coord_def pos_, int time_):
Melee_Weapon(infor_, pos_, time_)
{

}
Melee_Hammer::~Melee_Hammer()
{

}
float Melee_Hammer::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
	gm_->shot_list.push_back(new Shot_hammer(width<3.0f?effect_texture:&tex_melee2, User_, damage_, GetPower(), GetMaxPower(), burst_speed, team_, start_, angle_, GetDistance(), width, back_stab));
	return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
}
