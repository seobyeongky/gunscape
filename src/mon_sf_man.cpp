//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_sf_man.cpp
//
// 내용: 그물과 샷건을 쓰는 헌터
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_sf_man.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "shot_smoke_bomb.h"

Mon_sf_man::Mon_sf_man(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
smoke(true)
{

}
Mon_sf_man::~Mon_sf_man()
{

}

bool Mon_sf_man::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!GetDelay())
	{
		if(smoke)
		{
			gm_->shot_list.push_back(new Shot_smoke_bomb(&tex_grenade, this, 25, 200, 35.0f, GetTeam(), GetPos() ,c));			
			smoke = false;
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