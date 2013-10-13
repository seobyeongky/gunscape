//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: grenade_gun.cpp
//
// 내용: 바주카류 무기들
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "grenade_gun.h"
#include "shot_grenade.h"
#include "random.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "shot_missile.h"
#include "unit.h"

Grenade_gun::Grenade_gun(const main_weapon_infor& infor_, coord_def pos_, int time_):
Main_Weapon(infor_, pos_, time_), 
burst_speed(infor_.burst_speed), shot_time(infor_.shot_speed), damage(infor_.damage),
range(infor_.size_var), bunch(infor_.bunch), pentan(infor_.bonus_int>0?true:false)
{


}
Grenade_gun::~Grenade_gun()
{
}
float Grenade_gun::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	if(UseBullet(1))
	{
		for(int i = 0;i<bunch;i++)
		{

			float distan_ = distan_coord(start_, pos_);
			float angle_ = GetAngleToTarget(start_, pos_);
			coord_def target_ = pos_;
			
			float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);


			if(distan_ > GetDistance())
			{
				coord_def temp_ = target_ - start_;
				temp_ = temp_/distan_*GetDistance();
				target_ = temp_ + start_;
			}
			{
				float focus2_ = rand_float(0,sin(focus_)*distan_);
				float rand_angle_ = rand_float(0,rand_float(0,D3DX_PI*2));
				coord_def temp_pos_ = coord_def(cos(rand_angle_)*focus2_,sin(rand_angle_)*focus2_);
				target_+=temp_pos_;
			}
			gm_->shot_list.push_back(new Shot_grenade(&tex_grenade, User_, shot_time, damage_, GetPower(), GetMaxPower(), range, pentan, team_, start_, target_));

		}
		gm_->Noise(team_,start_,GetNoise() * User_->GetSilencer());
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
	return -1;
}
const char* Grenade_gun::GetDamage()
{
	sprintf_s(temp_str,32,"%d",(int)damage);
	return temp_str;
}
const char* Grenade_gun::GetAtkSpeed()
{
	sprintf_s(temp_str,32,"%.2g",60.0f/burst_speed);
	return temp_str;
}