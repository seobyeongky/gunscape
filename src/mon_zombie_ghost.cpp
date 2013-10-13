//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_zombie_ghost.cpp
//
// 내용: 투명해졌다를 반복하는 좀비.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_zombie_ghost.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "random.h"

Mon_zombie_ghost::Mon_zombie_ghost(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
count(rand_int(0,399)), cycle(randA(1)*2-1)
{
	if(cycle == 1)
		SetInvisible(min(count,255));
	else
		SetInvisible(255 - min(count,255));
}
Mon_zombie_ghost::~Mon_zombie_ghost()
{

}

bool Mon_zombie_ghost::Special_Action(Game_Manager* gm_)
{
	count++;
	if(count <= 255)
	{
		SetInvisible(GetInvisible()+cycle);
	}
	if(count == 400)
	{
		count = 0;
		cycle *= -1;
	}

	return true;
}
