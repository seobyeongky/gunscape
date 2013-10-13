//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_zombie_virus.cpp
//
// 내용: 죽으면 바이러스를 분포한다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_zombie_virus.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "random.h"
#include "shot_virus.h"

Mon_zombie_virus::Mon_zombie_virus(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
count(rand_int(0,30))
{

}
Mon_zombie_virus::~Mon_zombie_virus()
{

}

bool Mon_zombie_virus::Special_Action(Game_Manager* gm_)
{
	//count++;
	//if(count % 30 == 0)
	//{
	//	gm_->shot_list.push_back(new Shot_virus(&tex_virus, 5, 1, 10, GetTeam(), GetPos(), 150));
	//}
	return true;
}

void Mon_zombie_virus::Death(Game_Manager* gm_)
{
	gm_->shot_list.push_back(new Shot_virus(&tex_virus, NULL, 2, 1, 15, GetTeam(), GetPos(), 250));
}