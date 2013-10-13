//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_stalker.cpp
//
// 내용: 추적자 몹(ai만 다른 몹이다.)
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "ai_stalker.h"
#include "texture_list.h"
#include "gamemanager.h"
#include "shot_net.h"
#include "mon_stalker.h"
#include "effect_piece.h"

Mon_stalker::Mon_stalker(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
run(false), stamina(200), run_delay(0)
{

}
Mon_stalker::~Mon_stalker()
{

}

void Mon_stalker::SetAi(monster_state state_, Unit* head_, int level_)
{
	if(!ai)
	{
		ai = new Ai_Stalker(state_, this, head_, level_);
	}
}
bool Mon_stalker::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!run && !run_delay)
	{
		run = true;
		ApplySpeed(1.3f);
		run_delay = 600;
		return true;
	}
	{
		Monster::Shot(gm_, c, focus_);
	}
	return false;
}

bool Mon_stalker::Special_Action(Game_Manager* gm_)
{
	if(run_delay)
		run_delay--;
	if(run)
	{
		if(stamina%10 == 0)
		{
			Effect_run_afterimage(gm_, GetTexture(), GetPos(), GetAngle(), 1.0f);
		}
		stamina--;
		if(stamina<0){
			run = false;
			ApplySpeed(1/1.3f);
			stamina = 200;
		}
	}
	else
	{
		stamina = 200;
	}
	return true;

}