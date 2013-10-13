//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_bomb.cpp
//
// 내용: 폭탄충
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_bug_bomb.h"

#include "effect_piece.h"
#include "gamemanager.h"
#include "map.h"


Mon_bug_bomb::Mon_bug_bomb(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_)
{

}
Mon_bug_bomb::~Mon_bug_bomb()
{

}
bool Mon_bug_bomb::Melee(Game_Manager* gm_)
{
	if(!GetDamage() || !isLive() || isNonTarget() )
		return false;
	bool ok_ = false;
	for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
	{
		if((*it)->isLive() && !(*it)->isNonTarget()  && GetTeam() != (*it)->GetTeam())
		{
			if(GetSize()+(*it)->GetSize()+5.0f > distan_coord(GetPos(), (*it)->GetPos()))
			{
				//if(각도가 맞으면)
				Bomb(gm_);
				SetDelay(30.0f);
				SetHp(0);
				ok_ = true;
			}
		}
	}
	return ok_;
}

void Mon_bug_bomb::Death(Game_Manager* gm_)
{
	Bomb(gm_);
}
void Mon_bug_bomb::Bomb(Game_Manager* gm_)
{
	if(gm_)
	{
		for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
		{
			if((*it)->isLive() && !(*it)->isNonTarget() )
			{
				if((*it)->collution(GetPos(), 10.0f))
				{
					if(!gm_->map->CollutionPosToPos(GetPos(), (*it)->GetPos()))
					{
						(*it)->SetKnockback(3.0f, 6.0f, GetAngleToTarget(GetPos(), (*it)->GetPos()));
						(*it)->SetDamage(gm_, GetPos(), DT_EXPLOSION, GetDamage(), GetTeam());
					}
				}
			}
		}
	}
	Effect_bomb(gm_, GetPos(), 15, 2.0f, 1.0f);
	return;
}
