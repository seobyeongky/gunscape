//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_melee.cpp
//
// 내용: 밀리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_melee.h"
#include "unit.h"
#include "gamemanager.h"
#include "image.h"
#include "effect_message.h"
#include "sound.h"
#include "random.h"


Shot_melee::Shot_melee(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, int time_, int team_, coord_def pos_, float angle_, float size_, float width_, float back_stab_):
Shot_base(texture_, unit_, team_, pos_, coord_def()), 
damage(damage_), power(power_), max_power(max_power_), time(time_), const_time(time_), valid(true),
angle(angle_), size(size_), width(width_),
alpha(255), ok_backstab(false), back_stab(back_stab_)
{

}


Shot_melee::~Shot_melee()
{

}

bool Shot_melee::Action(Game_Manager* gm_)
{
	if(valid)
	{
		if(gm_ && time > const_time-3)
		{
			for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
			{
				bool hit_ = true;
				if((*it)->isLive() && !(*it)->isNonTarget()  && (*it)->GetTeam() != GetTeam())
				{
					for(list<Unit*>::iterator it2 = hit_unit.begin(); it2 != hit_unit.end() ; it2++)
					{
						if((*it) == (*it2))
						{
							hit_ = false;
						}
					}
					if(hit_ && (*it)->collution(GetPos(), size))
					{
						if(map->CollutionPosToPos(GetPos(), (*it)->GetPos()))
							continue;

						float angle_ = GetAngleToTarget(GetPos(), (*it)->GetPos())-angle;
						if(width>=3.0f || cos(angle_) >= cos(width) || (*it)->collution(GetPos(), 0.0f))
						{
							Hit(gm_, (*it));
						}
					}
				}
			}
		}

		if(gm_ && time == const_time-3 && !ok_backstab)
			PlaySE(se_knife, false);


		alpha -= (int)(150/const_time);
		if(alpha<0)
			alpha = 0;
		time--;
		if(time<0)
			valid = false;
	}
	
	if(!valid)
	{
		return true;
	}
	return false;
}
void Shot_melee::Hit(Game_Manager* gm_, Unit* unit_)
{
	Damage_Type dt_ = DT_MELEE;
	float damage_ = damage;
	float power_ = power;
	float max_power_ = max_power;
	bool backstab_ok_ = false;
	if(unit && unit->GetCritical() && unit->GetCritical()>rand_int(0,99))
	{
		backstab_ok_ = true;
	}
	if(back_stab > 1.0f && (backstab_ok_ ||  unit_->isBackStabbing()))
	{

		damage_ *= back_stab;
		Effect_simple_speak(gm_,"백스탭!",unit_->GetPos());
		PlaySE(se_backstab, false);
		ok_backstab = true;
		dt_ = DT_BACK_STAB;	
		power_ *= 3;
		max_power_ *= 3;
	}
	unit_->SetKnockback(power_, max_power_, angle);
	int final_damge_ = unit_->SetDamage(gm_, GetFirstPos(), dt_ ,damage_, GetTeam());
	if(unit)
		unit->GiveDamage(gm_, unit_, dt_, final_damge_);
	hit_unit.push_back(unit_);
}


bool Shot_melee::Draw(coord_def offset_, float size_)
{
	if(GetTexture())
	{
		float size__ = size/16.0f+0.1f;
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size_*size__, size_*size__, angle, D3DCOLOR_ARGB(alpha,255,255,255));
	}
	else
		return false;
}
bool Shot_melee::TargetLost_in()
{
	for(list<Unit*>::iterator it = hit_unit.begin(); it != hit_unit.end() ;)
	{
		if((*it) && !(*it)->isLive())
		{
			list<Unit*>::iterator temp = it;
			it++;
			hit_unit.erase(temp);
		}
		else
			it++;
	}
	return true;
}
