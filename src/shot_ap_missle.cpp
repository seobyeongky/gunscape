//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_ap_missle.cpp
//
// 내용: 포탄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_ap_missle.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "effect_piece.h"
#include "Map.h"

Shot_ap_missile::Shot_ap_missile(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, int team_, coord_def pos_, float angle_, float speed_, float distance_):
Shot_base(texture_, unit_, team_, pos_, coord_def(cos(angle_)*speed_, sin(angle_)*speed_)), 
damage(damage_), power(power_), max_power(max_power_),
distance(distance_), valid(true), angle(angle_), const_speed(speed_), count(0)
{
}
Shot_ap_missile::~Shot_ap_missile()
{

}
bool Shot_ap_missile::Action(Game_Manager* gm_)
{
	if(valid)
	{
		if(gm_)
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
					if(hit_ && (*it)->collution(GetPos(), 3.0f))
					{						
						Damage(gm_, (*it), power, max_power);
					}
				}
			}
		}


		if(collution(3))
		{
			valid = false;
		}
		else
			Move();


		distance -= const_speed;
		if(distance<0)
			valid = false;
		count++;
	}


	if(!valid)
	{
		return true;
	}
	return false;
}
bool Shot_ap_missile::Draw(coord_def offset_, float size_)
{
	if(GetTexture())
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size_ , angle);
	else
		return false;
}
bool Shot_ap_missile::TargetLost_in()
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




void Shot_ap_missile::Damage(Game_Manager* gm_, Unit* unit_, float power_, float max_power_)
{
	if(!unit_)
		return;
	int final_damge_ = unit_->SetDamage(gm_, GetFirstPos(), DT_AP ,damage, GetTeam());
	unit_->SetKnockback(power, max_power, angle);
	if(unit)
	{
		unit->GiveDamage(gm_, unit_, DT_AP, final_damge_);
	}
	hit_unit.push_back(unit_);
	//후에 화염데미지도 넣는다.
}
