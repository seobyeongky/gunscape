//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sniper.cpp
//
// 내용: 저격총
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "sniper.h"
#include "random.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "shot_sniper.h"
#include "sound.h"
#include "unit.h"

#include <opznet/shared_structs.h>

extern smap<opznet::ID, cl_t> clients;
extern opznet::ID my_id;

Sniper::Sniper(const main_weapon_infor& infor_, coord_def pos_, int time_):
Main_Weapon(infor_, pos_, time_), 
burst_speed(infor_.burst_speed), shot_speed(infor_.shot_speed), damage(infor_.damage), sniper(infor_.bonus_damage?infor_.bonus_damage:1.0f), sniper_static(infor_.bonus_damage?infor_.bonus_damage:1.0f),
bunch(infor_.bunch)
{


}
Sniper::~Sniper()
{
}
float Sniper::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	if(UseBullet(1))
	{
		for(int i = 0;i<bunch;i++)
		{
			float focus2_ = rand_float(-focus_, focus_);
			if(User_->GetSniper())
				focus2_ = 0;
			float speed2_ = shot_speed*GetShotSpeedApply()*rand_float(0.8f, 1.2f);
			float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
			gm_->shot_list.push_back(new Shot_sniper(&tex_gun, User_, damage_, sniper, GetPower(), GetMaxPower(), team_, start_, angle_+focus2_, GetDistance(), 50));
		}
		if (gm_->isPlayerCanHear(GetPos()))
		{
			if(GetType() == WT_SILENCE || User_->GetSilencer() != 1.0f)
				PlaySE(se_silencesnipergun);
			else
				PlaySE(se_snipergun);
		}
		gm_->Noise(team_,start_,GetNoise() * User_->GetSilencer());
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
	return -1;
}
float Sniper::special(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	Player * my_player = clients[my_id].player;

	if(User_->GetSniper())
	{
		User_->SetSniper(false);
		if (reinterpret_cast<Player *>(User_ ) == my_player)
		{
			gm_->SetSniperMode(false, pos_, 1.0f);
		}
		ApplyDamegeApply(0.5f);
	}
	else
	{
		User_->SetSniper(true);
		if (reinterpret_cast<Player *>(User_ ) == my_player)
		{
			gm_->SetSniperMode(true, pos_, 2.0f);
		}
		ApplyDamegeApply(2.0f);
		if (gm_->isPlayerCanHear(GetPos()))
		{
			PlaySE(se_snipermode, false);
		}
	}
	return 40;

}


int Sniper::GetBackStabDamage(Unit* User_)
{
	float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f)*sniper;
	return (int)damage_;
}
void Sniper::PlayReloadSE(Game_Manager * gm_)
{
	if (gm_->isPlayerCanHear(GetPos())) PlaySE(se_snipergun_reload);
}

const char* Sniper::GetDamage()
{
	sprintf_s(temp_str,32,"%d",(int)damage);
	return temp_str;
}
const char* Sniper::GetAtkSpeed()
{
	sprintf_s(temp_str,32,"%.2g",60.0f/burst_speed);
	return temp_str;
}
const char* Sniper::GetSniperStr()
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