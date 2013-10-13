//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_scream.cpp
//
// 내용: 죽으면 소음을 낸다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "named_scream.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "effect_piece.h"

Named_Scream::Named_Scream(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
scream(0)
{

}
Named_Scream::~Named_Scream()
{
}

void Named_Scream::Death(Game_Manager* gm_)
{
	Effect_noise(gm_, GetPos(), 1.0f);
	gm_->Noise(GetTeam(),GetPos(),200.0f);
}

bool Named_Scream::Special_Action(Game_Manager* gm_)
{
	if(scream>0)
		scream--;
	return true;
}
bool Named_Scream::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!GetDelay())
	{
		if(!scream)
		{
			float dis_ = distan_coord(GetPos(), c);
			if(dis_>60.0f)
				return false;
			for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
			{
				if((*it)->isLive() && !(*it)->isNonTarget())
				{
					if((*it)->GetTeam() != GetTeam())
					{
						if((*it)->collution(GetPos(),70.0f))
						{
							if(!gm_->map->CollutionPosToPos(GetPos(), (*it)->GetPos()))
							{
								(*it)->SetKnockback(7.0f, 7.0f, GetAngleToTarget(GetPos(), (*it)->GetPos()));
								(*it)->SetStop(60);
								(*it)->StateApply("기절",60);
							}
						}
					}
				}
			}
			Effect_cry(gm_, GetPos(),70.0f);
			gm_->Noise(GetTeam(),GetPos(),150.0f);
			scream = 150;
		}
		else
		{
			Monster::Shot(gm_, c, focus_);
		}
		return true;
	}
	return false;
}