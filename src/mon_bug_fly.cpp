//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_fly.cpp
//
// 내용: 메뚜기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <d3dx9.h>
#include <math.h>
#include "mon_bug_fly.h"

#include "image.h"
#include "gamemanager.h"
#include "map.h"


Mon_bug_fly::Mon_bug_fly(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
fly_delay(0)
{

}
Mon_bug_fly::~Mon_bug_fly()
{

}


bool Mon_bug_fly::Special_Action(Game_Manager* gm_)
{
	if(fly_delay)
		fly_delay--;
	return true;
}

	



void Mon_bug_fly::Approach(Game_Manager* gm_, coord_def c, Unit* target_)
{
	if(!fly_delay && !GetDelay() && !nonmove_delay)
	{
		float dis_ = distan_coord(GetPos(), c);
		if(dis_<50)
			return;
		float angle_ = GetAngleToTarget(GetPos(), c);
		Fly(gm_, c, (int)(dis_ / GetSpeed_Pure()));
		fly_delay = 700;
		SetAngle(angle_);
	}
	return;
}