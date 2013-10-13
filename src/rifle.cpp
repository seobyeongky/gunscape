//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: rifle.cpp
//
// 내용: 라이플류 무기들
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "rifle.h"
#include "random.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "shot_gun.h"
#include "sound.h"
#include "unit.h"


Rifle::Rifle(const main_weapon_infor& infor_, coord_def pos_, int time_):
Main_Weapon(infor_, pos_, time_), 
start_speed(infor_.burst_speed_init), speed_up((int)infor_.size_var), burst_speed(infor_.burst_speed), current_speed(infor_.burst_speed_init),
delay(0), shot_speed(infor_.shot_speed), damage(infor_.damage), sniper(infor_.bonus_damage?infor_.bonus_damage:1.0f), sniper_static(infor_.bonus_damage?infor_.bonus_damage:1.0f),
bunch(infor_.bunch), slow_ratio(infor_.size_var?infor_.size_var:1.0f), slow_turn(infor_.bonus_int)
{

}
Rifle::~Rifle()
{
}
float Rifle::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	if(UseBullet(1))
	{
		for(int i = 0;i<bunch;i++)
		{
			float focus2_ = rand_float(-focus_, focus_);
			float speed2_ = shot_speed*GetShotSpeedApply()*rand_float(0.8f, 1.2f);
			float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
			gm_->shot_list.push_back(new Shot_gun(&tex_gun, User_, damage_, sniper, GetPower(), GetMaxPower(), team_, start_, angle_+focus2_, speed2_, GetDistance(),slow_turn,slow_ratio,2));
		}
		if(GetType() == WT_SILENCE || User_->GetSilencer() != 1.0f)
			PlaySE(se_silencer);
		else
			PlaySE(se_pistol);
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


void Rifle::PlayReloadSE()
{
	if(bunch>1)
	{
		PlaySE(se_shotgun_reload);
	}
	else
		PlaySE(se_pistol_reload);
}

void Rifle::Passive(Game_Manager* gm_, Player* unit_, bool current_)
{
	if(delay)
	{
		delay--;
	}
	else
	{
		if(current_speed<start_speed)
		{
			current_speed++;
		}
	}
}

int Rifle::GetBackStabDamage(Unit* User_)
{
	float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f)*sniper;
	return (int)damage_;
}


const char* Rifle::GetDamage()
{
	if(bunch == 1)
	{
		sprintf_s(temp_str,32,"%.2g",damage);
	}
	else
	{
		sprintf_s(temp_str,32,"%d~%d",(int)damage,(int)damage*bunch);
	}

	return temp_str;
}
const char* Rifle::GetAtkSpeed()
{
	sprintf_s(temp_str,32,"%.2g",60.0f/burst_speed);
	return temp_str;
}
const char* Rifle::GetSniperStr()
{
	if(sniper_static != 1.0f)
	{
		sprintf_s(temp_str,32,"암살 %.2g배 보너스",sniper_static);
		return temp_str;
	}
	else
	{
		return NULL;
	}
}