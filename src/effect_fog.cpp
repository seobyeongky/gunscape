//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_fog.cpp
//
// 내용: 좀비의 마을엔 안개가 낀다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "effect_fog.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "effect_piece.h"
#include "random.h"


Effect_fog::Effect_fog(Texture* texture_):
Shot_base(texture_, NULL, 0, coord_def(), coord_def(),STP_FOG)
{
}
Effect_fog::~Effect_fog()
{

}


bool Effect_fog::Action(Game_Manager* gm_)
{
	if(gm_)
	{
		for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
		{
			if((*it)->isLive() && !(*it)->isNonTarget() )
			{
				if(!(*it)->GetFogResist())
				{
					(*it)->SetBlind(2);
					(*it)->SetFogslow(2);
				}
			}
		}
	}
	return false;
}

bool Effect_fog::Draw(coord_def offset_, float size_)
{
	return false;
}
