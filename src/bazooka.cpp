//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: bazooka.cpp
//
// 내용: 바주카류 무기들
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "bazooka.h"
#include "random.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "shot_missile.h"
#include "unit.h"

Bazooka::Bazooka(const main_weapon_infor& infor_, coord_def pos_, int time_):
Main_Weapon(infor_, pos_, time_), 
burst_speed(infor_.burst_speed), shot_speed(infor_.shot_speed), damage(infor_.damage),
range(infor_.size_var), guided_range(infor_.bonus_int), guided_power(infor_.bonus_damage),
bunch(infor_.bunch)
{


}
Bazooka::~Bazooka()
{
}
float Bazooka::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	if(UseBullet(1))
	{
		for(int i = 0;i<bunch;i++)
		{
			float focus2_ = rand_float(-focus_, focus_);
			float speed2_ = shot_speed*GetShotSpeedApply();
			float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
			gm_->shot_list.push_back(new Shot_missile(&tex_missile, User_, damage_, GetPower(), GetMaxPower(), range, team_, start_, angle_+focus2_, speed2_, guided_range, guided_power, GetDistance()));
		}
		gm_->Noise(team_,start_,GetNoise() * User_->GetSilencer());
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
	return -1;
}
const char* Bazooka::GetDamage()
{
	sprintf_s(temp_str,32,"%d",(int)damage);
	return temp_str;
}
const char* Bazooka::GetAtkSpeed()
{
	sprintf_s(temp_str,32,"%.2g",60.0f/burst_speed);
	return temp_str;
}