//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ice.cpp
//
// 내용: 화염방사기류 무기들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "ice.h"
#include "random.h"
#include "sound.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "shot_ice.h"
#include "sound.h"
#include "unit.h"

Ice::Ice(const main_weapon_infor& infor_, coord_def pos_, int time_):
Main_Weapon(infor_, pos_, time_), 
burst_speed(infor_.burst_speed), shot_speed(infor_.shot_speed),
damage(infor_.damage), fire_damage(infor_.bonus_damage), size_inc(infor_.size_var),
slow_turn(infor_.burst_speed_init), slow_ratio(infor_.bonus_damage)
{

}
Ice::~Ice()
{

}

float Ice::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	if(UseBullet(1))
	{
		float focus2_ = rand_float(-focus_, focus_);
		float speed2_ = shot_speed*GetShotSpeedApply()*rand_float(0.8f, 1.2f);
		float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
		gm_->shot_list.push_back(new Shot_ice(&tex_gun, User_, damage_, fire_damage, (int)GetDistance(), team_, start_, angle_+focus2_, speed2_, slow_turn, slow_ratio, size_inc));
		PlaySE(se_flame_thrower, false);
		gm_->Noise(team_,start_,GetNoise() * User_->GetSilencer());
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
	return -1;
}

void Ice::PlayReloadSE()
{
	PlaySE(se_flame_reload);

}
const char* Ice::GetDamage()
{
	sprintf_s(temp_str,32,"%.2g",damage);
	return temp_str;
}
const char* Ice::GetAtkSpeed()
{
	sprintf_s(temp_str,32,"%.2g",60.0f/burst_speed);
	return temp_str;
}