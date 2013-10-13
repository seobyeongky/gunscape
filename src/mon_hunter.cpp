//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_hunter.cpp
//
// 내용: 그물과 샷건을 쓰는 헌터
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_hunter.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "shot_net.h"

Mon_hunter::Mon_hunter(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
net(true)
{

}
Mon_hunter::~Mon_hunter()
{

}

bool Mon_hunter::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!GetDelay())
	{
		if(net)
		{
			float angle_ = GetAngleToTarget(GetPos(), c);
			gm_->shot_list.push_back(new Shot_net(&tex_net, this, 100, GetTeam(), GetPos(), angle_, 3, 150));			
			net = false;
			SetDelay(70.0f);
		}
		else
		{
			Monster::Shot(gm_, c, focus_);
		}
		return true;
	}
	return false;
}