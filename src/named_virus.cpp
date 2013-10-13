//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_virus.cpp
//
// 내용: 죽으면 바이러스를 분포한다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "named_virus.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "random.h"
#include "shot_virus.h"

Named_virus::Named_virus(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
count(rand_int(0,30))
{

}
Named_virus::~Named_virus()
{

}

bool Named_virus::Special_Action(Game_Manager* gm_)
{
	count++;
	if(count % 50 == 0)
	{
		gm_->shot_list.push_back(new Shot_virus(&tex_virus, NULL, 5, 1, 10, GetTeam(), GetPos(), 150));
	}
	return true;
}
