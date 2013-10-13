//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_missile.cpp
//
// 내용: 포탄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_missile.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "effect_piece.h"
#include "Map.h"

Shot_missile::Shot_missile(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, float range_, int team_, coord_def pos_, float angle_, float speed_, int guided_range_, float guided_power_, float distance_):
Shot_base(texture_, unit_, team_, pos_, coord_def(cos(angle_)*speed_, sin(angle_)*speed_)), 
damage(damage_), power(power_), max_power(max_power_), range(range_),
distance(distance_), valid(true), angle(angle_), const_speed(speed_)
, guided_range(guided_range_), guided_power(guided_power_), target(NULL), count(0)
{
}
Shot_missile::~Shot_missile()
{

}
bool Shot_missile::Action(Game_Manager* gm_)
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
							Bomb(gm_, power, max_power, damage, range);
						valid = false;
					}
				}
			}

			if(guided_range)
			{
				if(count%10 == 0)
				{
					target = NULL;
					float max_range_ = (float)guided_range;
					for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
					{
						if((*it)->isLive() && !(*it)->isNonTarget()  && (*it)->GetTeam() != GetTeam())
						{
							if((*it)->collution(GetPos(), (float)guided_range))
							{
								float temp_ = distan_coord(GetPos(), (*it)->GetPos());
								if(temp_<max_range_)
								{
									if(!map->CollutionPosToPos(GetPos(), (*it)->GetPos()))
									{
										target = (*it);
										max_range_ = temp_;
									}
								}
							}
						}
					}
				}
				if(target)
				{
					coord_def temp_speed = GetSpeed();
					float temp = sin(GetAngleToTarget(coord_def(),temp_speed)-GetAngleToTarget(GetPos(), target->GetPos()));
					if(temp>0)
					{
						float speed_ = distan_coord(coord_def(), temp_speed);
						float angle_ = GetAngleToTarget(coord_def(), temp_speed);
						angle_-=guided_power;
						angle = angle_;
						SetSpeed(coord_def(cos(angle_)*speed_, sin(angle_)*speed_));
					}
					else if(temp<0)
					{
						float speed_ = distan_coord(coord_def(), temp_speed);
						float angle_ = GetAngleToTarget(coord_def(), temp_speed);
						angle_+=guided_power;
						angle = angle_;
						SetSpeed(coord_def(cos(angle_)*speed_, sin(angle_)*speed_));
					}
				}
			}
		}



		if(collution(3))
		{
			if(valid)
				Bomb(gm_, power, max_power, damage, range);
			valid = false;
		}
		else
		{
			Move();

		}


		distance -= const_speed;
		if(distance<0)
			valid = false;
		count++;
		if(count %5==0)
		{
			Effect_fog(gm_, GetPos(), 1.0f);
		}
	}


	if(!valid)
	{
		return true;
	}
	return false;
}


bool Shot_missile::Draw(coord_def offset_, float size_)
{
	if(GetTexture())
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size_ , angle);
	else
		return false;
}
bool Shot_missile::TargetLost_in()
{
	if(target && !target->isLive())
	{
		target = NULL;
		return true;
	}
	return false;
}