//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: double_pistol.cpp
//
// 내용: 라이플류 무기들
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "double_pistol.h"
#include "random.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "shot_gun.h"
#include "sound.h"
#include "unit.h"


Double_pistol::Double_pistol(const main_weapon_infor& infor_, coord_def pos_, int time_):
Main_Weapon(infor_, pos_, time_), 
start_speed(infor_.burst_speed_init), speed_up((int)infor_.size_var), burst_speed(infor_.burst_speed), current_speed(infor_.burst_speed_init),
delay(0), shot_speed(infor_.shot_speed), damage(infor_.damage), sniper(infor_.bonus_damage?infor_.bonus_damage:1.0f),
distant(infor_.bonus_int)
{

}
Double_pistol::~Double_pistol()
{
}
float Double_pistol::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	int bullet_ = UseBullet(2);
	if(bullet_)
	{
		for(float i = -1;i<bullet_;i+=2)
		{
			coord_def start_pos_ = start_+coord_def(cos(angle_+i/2*D3DX_PI)*distant,sin(angle_+i/2*D3DX_PI)*distant);
			float angle2_ = GetAngleToTarget(start_pos_, pos_);
			float focus2_ = rand_float(-focus_, focus_);
			float speed2_ = shot_speed*GetShotSpeedApply()*rand_float(0.9f, 1.1f);
			float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
			gm_->shot_list.push_back(new Shot_gun(&tex_gun, User_, damage_, sniper, GetPower(), GetMaxPower(), team_, start_pos_, angle2_+focus2_, speed2_, GetDistance(),0,0.0f, 2));
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
void Double_pistol::Passive(Game_Manager* gm_, Player* unit_, bool current_)
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
const char* Double_pistol::GetDamage()
{
	sprintf_s(temp_str,32,"%d~%d",(int)damage,(int)damage*2);
	return temp_str;
}
const char* Double_pistol::GetAtkSpeed()
{
	sprintf_s(temp_str,32,"%.2g",60.0f/burst_speed);
	return temp_str;
}