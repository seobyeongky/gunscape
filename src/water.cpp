//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: water.cpp
//
// 내용: 물뿌리개 무기들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "water.h"
#include "random.h"
#include "sound.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "shot_water.h"
#include "sound.h"
#include "unit.h"

Water::Water(const main_weapon_infor& infor_, coord_def pos_, int time_):
Main_Weapon(infor_, pos_, time_), 
burst_speed(infor_.burst_speed), shot_speed(infor_.shot_speed),
damage(infor_.damage), power(infor_.power), max_power(infor_.max_power), size_inc(infor_.size_var)
{


}
Water::~Water()
{

}


float Water::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	if(UseBullet(1))
	{
		float focus2_ = rand_float(-focus_, focus_);
		float speed2_ = shot_speed*GetShotSpeedApply()*rand_float(0.8f, 1.2f);
		float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
		gm_->shot_list.push_back(new Shot_water(&tex_gun, User_, damage_, power, max_power, (int)GetDistance(), team_, start_, angle_+focus2_, speed2_, size_inc));
		gm_->Noise(team_,start_,GetNoise() * User_->GetSilencer());
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
	return -1;
}

void Water::PlayReloadSE()
{
}
const char* Water::GetDamage()
{
	sprintf_s(temp_str,32,"%d",(int)damage);
	return temp_str;
}
const char* Water::GetAtkSpeed()
{
	sprintf_s(temp_str,32,"%.2g",60.0f/burst_speed);
	return temp_str;
}