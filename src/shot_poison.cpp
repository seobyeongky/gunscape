//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_poison.cpp
//
// 내용: 독침
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_poison.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "debug.h"

Shot_poison::Shot_poison(Texture* texture_, Unit* unit_, float damage_, float sniper_, float power_, float max_power_, int team_, coord_def pos_, float angle_, float speed_, float distance_, int slow_turn_, float slow_ratio_, int delay_):
Shot_base(texture_, unit_, team_, pos_, coord_def(cos(angle_)*speed_, sin(angle_)*speed_)), 
damage(damage_), sniper(sniper_), power(power_), max_power(max_power_), const_delay(delay_), distance(distance_), 
delay(delay_), delay_pos(pos_), valid(true), angle(angle_), slow_turn(slow_turn_), slow_ratio(slow_ratio_),const_speed(speed_)
{
}
Shot_poison::~Shot_poison()
{

}
bool Shot_poison::Action(Game_Manager* gm_)
{
	if(valid)
	{
		int coll_ = pre_collution(3);

		if(gm_)
		{
			for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
			{
				if((*it)->isLive() && !(*it)->isNonTarget()  && (*it)->GetTeam() != GetTeam())
				{
					if(unit_collution((*it)->GetPos(), (*it)->GetSize()+((*it)->isPlayer()?0.0f:3.0f) ))
					{
						(*it)->SetKnockback(power, max_power, angle);
						if(slow_turn)
							(*it)->SlowApply(slow_ratio,slow_turn, SK_GUN);
						int final_damge_ = (*it)->SetDamage(gm_, GetFirstPos(), DT_BULLET, damage, GetTeam(), sniper, unit?unit->GetCritical():0);

						if(!(*it)->GetDefResist(DT_POISON) && !(*it)->isNonLife())
							(*it)->SetPoison(8, 150, unit?unit:NULL);
						if(unit)
							unit->GiveDamage(gm_, (*it), DT_BULLET, final_damge_);
						valid = false;
						break;
					}
				}
			}
		}

		
		if(coll_)
		{
			SetPos(GetPos()+coord_def(cos(angle)*coll_, sin(angle)*coll_));
			valid = false;
			delay++;
		}
		else
			Move();
		distance -= const_speed;
		if(distance<0)
			valid = false;

	}
	
	if(valid && delay)
	{
		delay--;
	}
	else
	{
		delay_pos += GetSpeed();
		if(!valid)
		{
			if(const_delay < delay++)
				return true;
		}
	}
	return false;
}


bool Shot_poison::Draw(coord_def offset_, float size_)
{
	if(GetTexture())
		return GetTexture()->Draw(((GetPos().x+delay_pos.x)/2-offset_.x)*size_, ((GetPos().y+delay_pos.y)/2-offset_.y)*size_, size_*distan_coord(GetPos(),delay_pos), size_ , angle , D3DCOLOR_ARGB(200,200,0,200));
	else
		return false;
}