//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_spy.cpp
//
// 내용: 스파이!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_spy.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "random.h"

Mon_spy::Mon_spy(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
count(0)
{
}
Mon_spy::~Mon_spy()
{

}

bool Mon_spy::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{	
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!GetDelay())
	{
		count = 255;
		Monster::Shot(gm_, c, focus_);
		return true;
	}
	return false;
}
bool Mon_spy::Special_Action(Game_Manager* gm_)
{
	SetInvisible(255-count);
	if(count>0)
		count-=5;
	return true;
}