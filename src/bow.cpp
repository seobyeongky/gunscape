//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: bow.cpp
//
// 내용: 활이야
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "bow.h"
#include "random.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "shot_gun.h"
#include "sound.h"
#include "unit.h"
#include "player.h"



Bow::Bow(const main_weapon_infor& infor_, coord_def pos_, int time_):
Main_Weapon(infor_, pos_, time_), 
burst_speed(infor_.burst_speed), shot_speed(infor_.shot_speed), 
count(0), cur_click(false), pre_click(false),bow_state(),
damage(infor_.damage), sniper(infor_.bonus_damage?infor_.bonus_damage:1.0f), sniper_static(infor_.bonus_damage?infor_.bonus_damage:1.0f),
bunch(infor_.bunch), slow_ratio(infor_.size_var?infor_.size_var:1.0f), slow_turn(infor_.bonus_int)
{

}
Bow::~Bow()
{
}
float Bow::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	bow_state.focus = focus_;
	bow_state.pos = pos_;
	bow_state.start = start_;
	bow_state.team = team_;
	bow_state.User = User_;
	if(pre_click)
	{
		cur_click = true;
		count++;	
		return 0;
	}
	else
	{
		if(UseBullet(1))
		{
			cur_click = true;
			count=1;
			if(User_->GetFocus() < 0.2f)
			User_->UpDownFocus(0.3f);
			return 0;
		}
		return -1;
	}
}


void Bow::Passive(Game_Manager* gm_, Player* unit_, bool current_)
{
	if(pre_click && !cur_click)
	{
		float angle_ = GetAngleToTarget(bow_state.start, bow_state.pos);
		for(int i = 0;i<bunch;i++)
		{
			float speed__ = 1.0f+min(max(0,count-5),10)/10.0f;
			float focus2_ = rand_float(-bow_state.focus, bow_state.focus);
			float speed2_ = shot_speed*GetShotSpeedApply()*rand_float(0.8f, 1.2f)*speed__;
			float damage_ =  damage*GetDamegeApply()*(bow_state.User?bow_state.User->GetAtkApply():1.0f);
			gm_->shot_list.push_back(new Shot_gun(&tex_gun, bow_state.User, damage_, sniper, GetPower(), GetMaxPower(), bow_state.team, bow_state.start, angle_+focus2_, speed2_, GetDistance(),slow_turn,slow_ratio,5));
		}
		PlaySE(se_bow);
		gm_->Noise(bow_state.team,bow_state.start,GetNoise() * unit_->GetSilencer());
		bow_state.User->SetDelay(burst_speed*(1.0f/(GetBurstSpeedApply()*(bow_state.User?bow_state.User->GetAtkSpdApply():1.0f))));
		count = 1;
	}

	pre_click = cur_click;
	cur_click = false;
}
void Bow::PlayReloadSE()
{

}


int Bow::GetBackStabDamage(Unit* User_)
{
	float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f)*sniper;
	return (int)damage_;
}
const char* Bow::GetDamage()
{
	sprintf_s(temp_str,32,"%d",(int)damage);
	return temp_str;
}
const char* Bow::GetAtkSpeed()
{
	sprintf_s(temp_str,32,"%.2g",60.0f/burst_speed);
	return temp_str;
}
const char* Bow::GetSniperStr()
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