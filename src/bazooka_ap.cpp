//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: bazooka_ap.cpp
//
// 내용: 관통바주카
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "bazooka_ap.h"
#include "random.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "shot_ap_missle.h"
#include "unit.h"

Bazooka_ap::Bazooka_ap(const main_weapon_infor& infor_, coord_def pos_, int time_):
Main_Weapon(infor_, pos_, time_), 
burst_speed(infor_.burst_speed), shot_speed(infor_.shot_speed), damage(infor_.damage)
{


}
Bazooka_ap::~Bazooka_ap()
{
}
float Bazooka_ap::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	if(UseBullet(1))
	{
		float focus2_ = rand_float(-focus_, focus_);
		float speed2_ = shot_speed*GetShotSpeedApply();
		float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
		gm_->shot_list.push_back(new Shot_ap_missile(&tex_missile, User_, damage_, GetPower(), GetMaxPower(), team_, start_, angle_+focus2_, speed2_, GetDistance()));
		gm_->Noise(team_,start_,GetNoise() * User_->GetSilencer());
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
	return -1;
}
const char* Bazooka_ap::GetDamage()
{
	sprintf_s(temp_str,32,"%d",(int)damage);
	return temp_str;
}
const char* Bazooka_ap::GetAtkSpeed()
{
	sprintf_s(temp_str,32,"%.2g",60.0f/burst_speed);
	return temp_str;
}