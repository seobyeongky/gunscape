//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_ice.cpp
//
// 내용: 냉기방사
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_ice.h"
#include "random.h"
#include "gamemanager.h"
#include "Unit.h"
#include "image.h"


Shot_ice::Shot_ice(Texture* texture_, Unit* unit_, float damage_, float fire_power_, int time_, int team_, coord_def pos_, float angle_, float speed_, int slow_turn_, float slow_ratio_, float size_inc_):
Shot_base(texture_, unit_, team_, pos_, coord_def(cos(angle_)*speed_, sin(angle_)*speed_)), 
damage(damage_), fire_power(fire_power_), decel(GetSpeed()/(float)time_), time(time_), valid(true), angle(angle_),
size(1.0f), slow_turn(slow_turn_), slow_ratio(slow_ratio_),
size_inc(size_inc_), color(D3DCOLOR_ARGB(150,0,rand_int(0,255),255))
{
}

Shot_ice::~Shot_ice()
{

}

bool Shot_ice::Action(Game_Manager* gm_)
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
					for(vector<Unit*>::iterator it2 = hit_unit.begin(); it2 != hit_unit.end() ; it2++)
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


		if(collution(3))
		{
			valid = false;
		}
		else
			Move();
		UpDownSpeed(-decel);
		size += size_inc;
		color -= 0x02000000;
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
void Shot_ice::Damage(Game_Manager* gm_, Unit* unit_)
{
	if(!unit_)
		return;
	int final_damge_ = unit_->SetDamage(gm_, GetFirstPos(), DT_FIRE ,damage, GetTeam());
	unit_->SlowApply(slow_ratio,slow_turn, SK_ICE);
	if(unit)
		unit->GiveDamage(gm_, unit_, DT_FIRE, final_damge_);
	hit_unit.push_back(unit_);
	//후에 화염데미지도 넣는다.
}

bool Shot_ice::Draw(coord_def offset_, float size_)
{
	if(GetTexture())
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size_*size*3, size_*size*3 , angle , color);
	else
		return false;
}