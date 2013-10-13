//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_refle_fire.cpp
//
// 내용: 벽에 튕기는 화염방사
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_refle_fire.h"
#include "random.h"
#include "gamemanager.h"
#include "effect_piece.h"
#include "Unit.h"
#include "image.h"


Shot_refle_fire::Shot_refle_fire(Texture* texture_, Unit* unit_, float damage_, int fire_time_, float fire_damage_, int time_, int team_, coord_def pos_, float angle_, float speed_, int bounce_):
Shot_base(texture_, unit_, team_, pos_, coord_def(cos(angle_)*speed_, sin(angle_)*speed_)), 
damage(damage_), fire_time(fire_time_), fire_damage(fire_damage_), decel(GetSpeed()/(float)time_), time(time_), valid(true), speed_absol(speed_), angle(angle_),
bounce(bounce_), count(0)
{

}

Shot_refle_fire::~Shot_refle_fire()
{

}

bool Shot_refle_fire::Action(Game_Manager* gm_)
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
						Damage(gm_, (*it));
					}
				}
			}
		}

		
		float temp = 0;

		if(count>3)
		{
			bool hit_ = 0;
			coord_def temp_ = GetSpeed();
			if(gm_->map->CollutionX(GetX(),coord_def(GetX()+temp_.x,GetY()), 1.0f))
			{
				temp_.x*=-1;
				hit_=true;
			}
			if(gm_->map->CollutionY(GetY(),coord_def(GetX(),GetY()+temp_.y), 1.0f))
			{
				temp_.y*=-1;
				hit_=true;
			}
			if(hit_)
			{
				SetSpeed(temp_);
				hit_unit.clear();
				angle = GetAngleToTarget(coord_def(), coord_def(temp_.x,temp_.y));
				bounce--;
				count = 0;
				if(!bounce)
					valid = false;
			}
		}
		//if(count>6 && collutionAngle(3, temp))
		//{
		//	if(bounce)
		//	{
		//		temp = temp-
		//		angle = GetAngleToTarget(coord_def(), coord_def(cos(temp+3.141592654f)+cos(angle),sin(temp+3.141592654f)+sin(angle)));
		//		//angle += ((temp+3.141592654f)-angle)/2;

		//		SetSpeed(coord_def(cos(angle)*speed_absol, sin(angle)*speed_absol));
		//		bounce--;
		//		count = 0;
		//	}
		//	else
		//		valid = false;
		//}

		count++;
		if(count %3==0)
		{
			Effect_fire(gm_, GetPos()+coord_def(rand_float(-6,6),rand_float(-6,6)), 1.0f);
		}
		if(time==count)
			valid = false;

			
		Move();
	}


	if(!valid)
	{
		return true;
	}
	return false;
}
void Shot_refle_fire::Damage(Game_Manager* gm_, Unit* unit_)
{
	int final_damge_ = unit_->SetDamage(gm_, GetFirstPos(), DT_FIRE ,damage, GetTeam());
	if(unit)
		unit->GiveDamage(gm_, unit_, DT_FIRE, final_damge_);
	hit_unit.push_back(unit_);
	//후에 화염데미지도 넣는다.
}

bool Shot_refle_fire::Draw(coord_def offset_, float size_)
{
	if(GetTexture())
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size_ ,angle);
	else
		return false;
}
bool Shot_refle_fire::TargetLost_in()
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