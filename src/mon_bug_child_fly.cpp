//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_child_fly.cpp
//
// 내용: 비행충
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <d3dx9.h>
#include <math.h>
#include "mon_bug_child_fly.h"
#include "ai_fly_bug.h"

#include "image.h"
#include "random.h"
#include "gamemanager.h"
#include "map.h"


Mon_bug_child_fly::Mon_bug_child_fly(monster_infor& infor_, Unit* head_, Unit* target_, float x_, float y_, int team_, int return_time_, int time_):
Mon_bug_fly2(infor_, x_, y_, team_, time_),
return_time(return_time_), target(target_), head(head_)
{
}


void Mon_bug_child_fly::SetAi(monster_state state_, Unit* head_, int level_)
{
	if(!ai)
	{
		ai = new Ai_Fly_bug(state_, this, head_, level_);
		if(target)
			ai->SetTarget(target);
	}

}



bool Mon_bug_child_fly::Action_in(Game_Manager* gm_)
{
	if(!isLive())
	{
		return true;
	}
	if(GetWarning()>0)
		UpDownWarning(-5);
	if(return_time || !head)
	{
		if(ai)
		{
			if(ai->GetState() == MS_NORMAL)
			{
				ai->Noise(coord_def((float)rand_int(0,gm_->map->GetWidth()),(float)rand_int(0,gm_->map->GetHeight())));
			}
			ai->Action();
		}
		
		
		count--;
		return_time--;
		fly_speed+=accel;
		if(count<=0)
		{
			count = rand_int(50, 200);
			accel = (rand_float(0.5f,2.5f) - fly_speed)/count;
		}
	}
	else
	{
		float angle_ = GetAngleToTarget(GetPos(),head->GetPos());
		float speed_ = 1.0f;
		Move(GetPos().x+cos(angle_)*speed_,GetPos().y+sin(angle_)*speed_);
		SetAngle(angle_);
		fly_angle = angle_;
		if(collution(head->GetPos(), 5.0f))
		{
			return true;
		}
	}

	CommonAction(gm_);
	return false;
}

void Mon_bug_child_fly::SetFlyAngle(float angle_)
{
	SetAngle(angle_);
	fly_angle = angle_;
};

bool Mon_bug_child_fly::TargetLost()
{
	if(head && !head->isLive())
	{
		head = NULL;
		SetHp(0);
	}
	if(target && !target->isLive())
	{
		target = NULL;
	}
	return false;
}