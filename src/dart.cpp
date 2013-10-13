//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: dart.cpp
//
// 내용: 독침
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "dart.h"
#include "random.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "shot_poison.h"
#include "sound.h"
#include "unit.h"



Dart::Dart(const main_weapon_infor& infor_, coord_def pos_, int time_):
Rifle(infor_, pos_, time_)
{
}

float Dart::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	if(UseBullet(1))
	{
		for(int i = 0;i<bunch;i++)
		{
			float focus2_ = rand_float(-focus_, focus_);
			float speed2_ = shot_speed*GetShotSpeedApply()*rand_float(0.8f, 1.2f);
			float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
			gm_->shot_list.push_back(new Shot_poison(&tex_gun, User_, damage_, sniper, GetPower(), GetMaxPower(), team_, start_, angle_+focus2_, speed2_, GetDistance(),slow_turn,slow_ratio,2));
		}
		PlaySE(se_bow);
		gm_->Noise(team_,start_,GetNoise() * User_->GetSilencer());
		delay = start_speed*2;
		if(current_speed>burst_speed)
		{
			current_speed=max(burst_speed,current_speed-speed_up);
		}
		return current_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
	return -1;
}
