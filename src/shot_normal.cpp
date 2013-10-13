//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_normal.cpp
//
// 내용: 일반탄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_normal.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "effect_piece.h"
#include "Map.h"

Shot_normal::Shot_normal(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, int team_, coord_def pos_, float angle_, float speed_, float distance_):
Shot_base(texture_, unit_, team_, pos_, coord_def(cos(angle_)*speed_, sin(angle_)*speed_)), 
damage(damage_), power(power_), max_power(max_power_),
distance(distance_), valid(true), angle(angle_), const_speed(speed_), count(0)
{
}
Shot_normal::~Shot_normal()
{

}
bool Shot_normal::Action(Game_Manager* gm_)
{
	if(valid)
	{
		if(gm_)
		{
			for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
			{
				if((*it)->isLive() && !(*it)->isNonTarget()  && (*it)->GetTeam() != GetTeam())
				{
					if((*it)->collution(GetPos(), 5.0f))
					{
						(*it)->SetKnockback(power, max_power, angle);
						int final_damge_ = (*it)->SetDamage(gm_, GetFirstPos(), DT_BULLET, damage, GetTeam());
						if(unit)
							unit->GiveDamage(gm_, (*it), DT_BULLET, final_damge_);
						valid = false;
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


bool Shot_normal::Draw(coord_def offset_, float size_)
{
	if(GetTexture())
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size_ , angle);
	else
		return false;
}
