//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_smoke.cpp
//
// 내용: 연막탄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "Shot_smoke.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "effect_piece.h"
#include "random.h"


Shot_smoke::Shot_smoke(Texture* texture_, Unit* unit_, float range_, int team_, coord_def pos_, int time_):
Shot_base(texture_, unit_, team_, pos_, coord_def()), 
count(0), range(range_), time(time_), valid(true)
{
}
Shot_smoke::~Shot_smoke()
{

}


bool Shot_smoke::Action(Game_Manager* gm_)
{
	if(valid)
	{
		if(gm_)
		{
			for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
			{
				if((*it)->isLive() && !(*it)->isNonTarget() )
				{
					if((*it)->collution(GetPos(), range))
					{
						if(!(*it)->GetFogResist())
						{
							(*it)->SetBlind(2);
							(*it)->SetFogslow(2);
							(*it)->SetShotStop(2);
							//if(count%50)
							//	(*it)->TargetBlinding();
						}
					}
				}
			}
		}

		Move();

		count++;

		if(count% 10 == 0 && time - count > 30)
			Effect_smoke(gm_, GetPos(), 1.0f*(range/20));


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

bool Shot_smoke::Draw(coord_def offset_, float size_)
{
	return false;
}
