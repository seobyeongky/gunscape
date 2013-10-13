//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_virus_shot.cpp
//
// 내용: 그물 총알
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_virus.h"
#include "shot_virus_shot.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "texture_list.h"
#include "Map.h"

Shot_virus_shot::Shot_virus_shot(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, float range_, float virus_damage_, int virus_frame_, int virus_time_, int team_, coord_def pos_, float angle_, float speed_, float distance_):
Shot_base(texture_, unit_, team_, pos_, coord_def(cos(angle_)*speed_, sin(angle_)*speed_)), 
damage(damage_), power(power_), max_power(max_power_), range(range_),
distance(distance_), valid(true), angle(angle_), const_speed(speed_), count(0),
virus_damage(virus_damage_), virus_frame(virus_frame_), virus_time(virus_time_)
{
}
Shot_virus_shot::~Shot_virus_shot()
{

}
bool Shot_virus_shot::Action(Game_Manager* gm_)
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
						if(valid)
						{
							(*it)->SetKnockback(power, max_power, angle);
							int final_damge_ = (*it)->SetDamage(gm_, GetFirstPos(), DT_BULLET, damage, GetTeam());
							if(unit)
								unit->GiveDamage(gm_, (*it), DT_BULLET, final_damge_);
							Bomb_Virus(gm_);
						}
						valid = false;
					}
				}
			}
		}


		if(collution(3))
		{
			if(valid)
				Bomb_Virus(gm_);
			valid = false;
		}
		else
			Move();


		distance -= const_speed;
		if(distance<0)
		{
			if(valid)
				Bomb_Virus(gm_);
			valid = false;
		}
	}


	if(!valid)
	{
		return true;
	}
	return false;
}


bool Shot_virus_shot::Draw(coord_def offset_, float size_)
{
	if(GetTexture())
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size_, angle);
	else
		return false;
}

void Shot_virus_shot::Bomb_Virus(Game_Manager* gm_)
{
	gm_->shot_list.push_back(new Shot_virus(&tex_virus, unit, virus_frame, virus_damage, range, GetTeam(), GetPos(), virus_time));
}