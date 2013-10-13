//////////////////////////////////////////////////////////////////////////////////////////////////
//
// ÆÄÀÏÀÌ¸§: named_berserker.cpp
//
// ³»¿ë: ±×¹°°ú ¼¦°ÇÀ» ¾²´Â ÇåÅÍ
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "named_berserker.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "shot_net.h"
#include "effect_message.h"
#include "effect_piece.h"

Named_Berserker::Named_Berserker(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
berserker(0), delay(0), count(0)
{

}
Named_Berserker::~Named_Berserker()
{

}
bool Named_Berserker::Special_Action(Game_Manager* gm_)
{
	if(berserker>0)
	{
		berserker--;
		if(count%10==0)
		{
			Effect_berserker(gm_,GetPos(),1.0f);
		}
		if(berserker==0)
		{			
			ApplyAtk(0.5f);
			ApplyDefense(DT_ALL,2.0f);
			SetDefResist(DT_MELEE,false);
			ApplySpeed(1/1.5f);
			SlowApply(0.2f,120, SK_BERSERKER);
		}
	}
	else
	{
		if(delay>0)
		{
			delay--;
		}
	}
	count++;
	return true;
}

bool Named_Berserker::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!GetDelay())
	{
		if(!delay)
		{
			berserker = 100;
			delay = 200;
			Effect_simple_speak(gm_,"±¤ÆøÈ­!",GetPos());
			ApplyAtk(2.0f);
			ApplyDefense(DT_ALL,0.5f);
			SetDefResist(DT_MELEE,true);
			ApplySpeed(1.5f);
		}
		else
		{
			Monster::Shot(gm_, c, focus_);
		}
		return true;
	}
	return false;
}