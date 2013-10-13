//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_zombie_boomer.cpp
//
// 내용: 구역질을 하는 좀비다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_zombie_boomer.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "shot_virus_shot.h"

Mon_zombie_boomer::Mon_zombie_boomer(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
virus(true), count(0)
{

}
Mon_zombie_boomer::~Mon_zombie_boomer()
{

}

bool Mon_zombie_boomer::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!GetDelay())
	{
		if(virus)
		{
			float angle_ = GetAngleToTarget(GetPos(), c);
			float length_ = distan_coord(GetPos(), c);
			gm_->shot_list.push_back(new Shot_virus_shot(&tex_virus_missile, this, 10, 1, 5, 20.0f, 1, 5, 200, GetTeam(), GetPos(), angle_, 4.0f, length_));			
			virus = false;
			count = 150;
			SetDelay(50.0f);
		}
		else
		{
			count--;
			if(count < 0)
				virus = true;
			Monster::Shot(gm_, c, focus_);
		}
		return true;
	}
	return false;
}