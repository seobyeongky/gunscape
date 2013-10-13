//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_fly2.cpp
//
// 내용: 비행충
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <d3dx9.h>
#include <math.h>
#include "mon_bug_fly2.h"
#include "ai_fly_bug.h"

#include "image.h"
#include "random.h"
#include "gamemanager.h"
#include "map.h"


Mon_bug_fly2::Mon_bug_fly2(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
fly_speed(GetSpeed_Pure()), fly_angle(0),
count(1), accel(0)
{

}
Mon_bug_fly2::~Mon_bug_fly2()
{

}
void Mon_bug_fly2::SetAi(monster_state state_, Unit* head_, int level_)
{
	if(!ai)
	{
		ai = new Ai_Fly_bug(state_, this, head_, level_);
	}

}

bool Mon_bug_fly2::charDraw(Game_Manager* gm_, coord_def offset, float size_)
{
	float size__ = GetFlySize();
	if(GetTexture())
		return GetTexture()->Draw((GetX()-offset.x)*size_, (GetY()-offset.y)*size_, size_*size__, size_*size__, fly_angle, D3DCOLOR_ARGB(GetAlpha(gm_),255,255,255));
	return false;
}

bool Mon_bug_fly2::Action_in(Game_Manager* gm_)
{
	if(!isLive())
	{
		DropItem(gm_);
		return true;
	}
	if(GetWarning()>0)
		UpDownWarning(-5);
	if(ai)
	{
		if(ai->GetState() == MS_NORMAL)
		{			
			ai->Noise(coord_def((float)rand_int(0,gm_->map->GetWidth()),(float)rand_int(0,gm_->map->GetHeight())));
		}
		ai->Action();

	
	}



	count--;
	fly_speed+=accel;
	if(count<=0)
	{
		count = rand_int(50, 200);
		accel = (rand_float(0.5f,2.5f) - fly_speed)/count;
	}

	CommonAction(gm_);
	return false;
}

int Mon_bug_fly2::UnitMove(Game_Manager* gm_, float speed_, float angle_)
{
	fly_angle+=(sin(angle_-fly_angle)>0)?0.03f:-0.03f;


	float x_ = cos(fly_angle)*fly_speed;
	float y_ = sin(fly_angle)*fly_speed;

	Move(GetX()+x_,GetY()+y_);

	return 0;
}
int Mon_bug_fly2::UnitSlipMove(Game_Manager* gm_, float speed_, float angle_)
{
	UnitMove(gm_,speed_,angle_);
	for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
	{
		if((*it)->isLive() && !(*it)->isNonTarget()  && GetTeam() != (*it)->GetTeam())
		{
			if(GetSize()+(*it)->GetSize() > distan_coord(GetPos(), (*it)->GetPos()))
			{
				return 1;
			}
		}
	}
	return 0;
}
bool Mon_bug_fly2::isCollution()
{
	return false;
}

