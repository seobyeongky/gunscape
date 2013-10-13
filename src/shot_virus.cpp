//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_virus.cpp
//
// 내용: 바이러스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "Shot_virus.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "effect_piece.h"
#include "random.h"


Shot_virus::Shot_virus(Texture* texture_, Unit* unit_, int frame_, float damage_, float range_, int team_, coord_def pos_, int time_):
Shot_base(texture_, unit_, team_, pos_, coord_def()), 
count(0), frame(frame_), damage(damage_), range(range_), time(time_), valid(true)
{
}
Shot_virus::~Shot_virus()
{

}


bool Shot_virus::Action(Game_Manager* gm_)
{
	if(valid)
	{
		if(gm_ && count % frame == 0)
		{
			for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
			{
				if((*it)->isLive() && !(*it)->isNonTarget() )
				{
					if((*it)->collution(GetPos(), range))
					{
						int final_damge_ = (*it)->SetDamage(gm_, GetFirstPos(), DT_VIRUS, damage, GetTeam());
						if(unit)
							unit->GiveDamage(gm_, (*it), DT_VIRUS, final_damge_);
					}
				}
			}
		}

		Move();

		count++;


		if(count% (10/(int)(range/10)) == 0 && time - count > 30)
			Effect_virus(gm_, GetPos()+coord_def(rand_float(-range,range),rand_float(-range,range)), 1.0f);


		if(count == time)
		{
			valid = false;
		}
	}


	if(!valid)
	{
		return true;
	}
	return false;
}

bool Shot_virus::Draw(coord_def offset_, float size_)
{
	return false;
}
