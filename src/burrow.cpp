//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: burrow.cpp
//
// 내용: 버로우한 적들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "burrow.h"
#include "random.h"

#include "gamemanager.h"
#include "map.h"
#include "monster_list.h"

#include "effect_piece.h"


Burrow::Burrow(coord_def pos_, int time_, float range_, Brrow_Type type_):
Unit("버로우", NULL, pos_.x, pos_.y, -1, 0),
time(time_), range(range_), react(false), mon_list(), pos_list()
{
	SetSize(20.0f);
	CreateMonster(type_);
}


Burrow::~Burrow()
{

}

bool Burrow::Action_in(Game_Manager* gm_)
{
	if(gm_ && !react)
	{
		for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
		{
			if((*it)->isLive() && !(*it)->isNonTarget()  && (*it)->GetTeam() != GetTeam())
			{
				if((*it)->collution(GetPos(), GetSize()))
				{
					SetMonPos(gm_);
					react = true;
				}
			}
		}
	}

	if(react)
	{
		time--;
		if(time%5==4)
		{
			for(vector<coord_def>::iterator it = pos_list.begin() ; it != pos_list.end() ; it++)
				Effect_dust(gm_, (*it), 2,  1.0f, 0.3f);
		}
		if(!time)
		{
			for(unsigned int i = 0; i<mon_list.size();i++)
			{
				Effect_dust(gm_, pos_list[i], 10,  2.0f, 0.5f);
				gm_->unit_list.push_back(New_Monster(mon_list[i], pos_list[i], -1, 0, 60));
			}

			return true;
		}
	}
	return false;
}


void Burrow::CreateMonster(Brrow_Type type_)
{
	switch(type_)
	{
	case BT_SMALL_ZOMBIE:
		for(int i = rand_int(2,3) ; i>0 ; i--)
			mon_list.push_back(MON_WEAK_ZOMBIE);
		return;
	case BT_ZOMBIE_VIRUS:
		for(int i = rand_int(2,3) ; i>0 ; i--)
			mon_list.push_back(rand_int(0,1)?MON_ZOMBIE_VIRUS:MON_WEAK_ZOMBIE);
		return;
	case BT_ZOMBIE_VIRUS_SMALL:
		for(int i = rand_int(2,3) ; i>0 ; i--)
			mon_list.push_back(rand_int(0,1)?MON_ZOMBIE_SMALL:MON_ZOMBIE_VIRUS);
		return;
	default:
		return;
	}
}
void Burrow::SetMonPos(Game_Manager* gm_)
{		
	for(unsigned int i = 0; i<mon_list.size();)
	{
		int x_ = rand_int((int)(GetX()-range), (int)(GetX()+range));
		int y_ = rand_int((int)(GetY()-range), (int)(GetY()+range));
		if(x_<0 || x_>=gm_->map->GetWidth() || y_<0 || y_>=gm_->map->GetHeight()) 
			continue;
		if(!gm_->map->CollutionPos(x_,y_) && !gm_->map->CollutionPosToPos(coord_def((float)x_, (float)y_), GetPos()))
		{
			pos_list.push_back(coord_def((float)x_, (float)y_));
			i++;
		}
	}
}