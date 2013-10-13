//////////////////////////////////////////////////////////////////////////////////////////////////
//
// ÆÄÀÏÀÌ¸§: named_fly_boss.cpp
//
// ³»¿ë: ¿©¿Õ¹ú·¹
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "mon_bug_child_fly.h"
#include "named_fly_boss.h"
#include "gamemanager.h"
#include "ai_fly_bug.h"
#include "random.h"


extern monster_infor monster__bug_child_fly;

Named_fly_boss::Named_fly_boss(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
count(0)
{

}
Named_fly_boss::~Named_fly_boss()
{

}
bool Named_fly_boss::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!GetDelay())
	{
		float length_ = distan_coord(GetPos(), c);

		if(length_ >120)
			return false;
		float angle_ = GetAngleToTarget(GetPos(), c);

		Unit* target_ = NULL;
		if(gm_)
		{
			for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
			{
				if((*it)->isLive() && !(*it)->isNonTarget()  && (*it)->GetTeam() != GetTeam())
				{
					if((*it)->collution(c, 30.0f))
					{
						target_ = (*it);
						break;
					}
				}
			}
		}
		Unit* temp = new Mon_bug_child_fly(monster__bug_child_fly,this, target_, GetX(), GetY(), GetTeam(),200);
		temp->SetAi(MS_NORMAL, NULL, 2);
		temp->SetFlyAngle(GetAngle()+rand_float(-1.0f,1.0f));
		gm_->unit_list.push_back(temp);			
		SetDelay(50.0f);
		return true;
	}
	return false;

}