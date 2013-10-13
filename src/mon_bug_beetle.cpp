//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_beetle.cpp
//
// 내용: 풍뎅이. 돌진함
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_bug_beetle.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "shot_virus_shot.h"
#include "effect_piece.h"
#include "image.h"
#include "map.h"

Mon_bug_beetle::Mon_bug_beetle(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
rush_delay(0), rush(-1), rush_speed(2.5f), count(0), hit_unit()
{

}
Mon_bug_beetle::~Mon_bug_beetle()
{

}
bool Mon_bug_beetle::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetShotStop())
		return false;
	if(!GetDelay())
	{
		if(!rush_delay)
		{
			SetStop(2);
			rush = 20;

			rush_delay = 100;
		}
		else
		{
			Monster::Shot(gm_, c, focus_);
		}
		return true;
	}
	return false;
}
bool Mon_bug_beetle::TargetLost()
{
	bool ok_=false;
	if(ai->TargetLost())
		ok_ = true;
	for(list<Unit_Infor>::iterator it = hit_unit.begin();it != hit_unit.end();)
	{
		if(!(*it).pointer->isLive())
		{
			list<Unit_Infor>::iterator temp = it++;
			hit_unit.erase(temp);
			ok_ = true;
		}
		else
			it++;
	}
	return ok_;

}


bool Mon_bug_beetle::Special_Action(Game_Manager* gm_)
{
	if(GetNet() && rush_delay == 0)	
	{
		rush = -1;
		SetDelay(70.0f);
		hit_unit.clear();
	}



	if(rush > 0)
	{
		SetStop(2);

		rush--;
	}
	else if(rush == 0)
	{	
		if(count++%10 == 0)
		{
			Effect_run_afterimage(gm_, GetTexture(), GetPos(), GetAngle(), 1.0f);
		}

		SetStop(0);
		SetAngleStop(2);

		float x_ = cos(GetAngle())*rush_speed;
		float y_ = sin(GetAngle())*rush_speed;


		Move(GetX()+x_,GetY()+y_);

		int state_=0;
		if(!gm_->map->Collution((int)GetX(), (int)GetY(), (int)GetSize()))
		{	
			for(list<Unit*>::iterator it = gm_->unit_list.begin(); it != gm_->unit_list.end(); it++)
			{
				if((*it) != this && (*it)->isLive() && !(*it)->isNonTarget()  && (*it)->isCollution())
				{
					if((*it)->collution(GetPos(), GetSize()))
					{
						state_ = ((*it)->GetTeam() != GetTeam())?2:1; //팀이 같으면 1 틀리면 2
					}
				}
			}
		}
		else
			state_ = -1;

		SetStop(2);

		if(state_ == -1 || state_ == 1) //벽(-1)이나 아군(1)에게 부딫힐경우
		{
			rush = -1;
			SetDelay(70.0f);
			hit_unit.clear();
		}
		else
		{
			if(state_ == 2) //적에게 부딫힐경우
			{
				for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
				{
					if((*it)->isLive() && !(*it)->isNonTarget()  && GetTeam() != (*it)->GetTeam())
					{
						if((*it)->collution(GetPos(), GetSize()))
						{
							bool already = false;
							for(list<Unit_Infor>::iterator it2 = hit_unit.begin();it2 != hit_unit.end();it2++)
							{
								if((*it) == (*it2).pointer)
								{
									already = true;
									break;
								}
							}
							if(!already)
								hit_unit.push_back(Unit_Infor((*it),(*it)->GetPos()-GetPos()));
						}
					}
				}
			}

			for(list<Unit_Infor>::iterator it = hit_unit.begin();it != hit_unit.end();it++)
			{
				if((*it).pointer->GetNet()) //적이나 아군이나 그물에 쌓인경우 움직임을 멈춰야한다.
				{						
					rush = -1;
					SetDelay(70.0f);
					hit_unit.clear();
					break;
				}
				(*it).pointer->SetDamage(gm_,GetPos(),DT_MELEE, 1.0f,GetTeam());
				(*it).pointer->SetStop(0);
				(*it).pointer->Move((*it).pos_dif.x+GetPos().x,(*it).pos_dif.y+GetPos().y);
				(*it).pointer->SetStop(2);
			}

		}


	}
	else if(rush_delay>0)
	{
		rush_delay--;
	}
	return true;
}