//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: fire2.cpp
//
// 내용: 발사형 화염방사기
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "fire2.h"
#include "random.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "shot_refle_fire.h"
#include "unit.h"
#include "sound.h"

Fire2::Fire2(const main_weapon_infor& infor_, coord_def pos_, int time_):
Main_Weapon(infor_, pos_, time_), 
burst_speed(infor_.burst_speed), shot_speed(infor_.shot_speed), damage(infor_.damage),
fire_time((int)infor_.size_var), fire_damage(infor_.bonus_damage), bounce(infor_.bunch)
{


}
Fire2::~Fire2()
{
}
float Fire2::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	if(UseBullet(1))
	{
		float focus2_ = rand_float(-focus_, focus_);
		float speed2_ = shot_speed*GetShotSpeedApply();
		float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
		gm_->shot_list.push_back(new Shot_refle_fire(&tex_fire, User_, damage_, fire_time, fire_damage, (int)GetDistance(), team_, start_, angle_+focus2_, speed2_, bounce));
		gm_->Noise(team_,start_,GetNoise() * User_->GetSilencer());
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
	return -1;
}
void Fire2::PlayReloadSE()
{
	PlaySE(se_flame_reload);

}
const char* Fire2::GetDamage()
{
	sprintf_s(temp_str,32,"%d",(int)damage);
	return temp_str;
}
const char* Fire2::GetAtkSpeed()
{
	sprintf_s(temp_str,32,"%.2g",60.0f/burst_speed);
	return temp_str;
}