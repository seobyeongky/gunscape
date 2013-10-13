//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_spider.cpp
//
// 내용: 거미다
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_bug_spider.h"

#include "effect_piece.h"
#include "gamemanager.h"
#include "map.h"
#include "monster_list.h"


Mon_bug_spider::Mon_bug_spider(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_)
{

}
Mon_bug_spider::~Mon_bug_spider()
{

}

void Mon_bug_spider::Death(Game_Manager* gm_)
{
	gm_->unit_list.push_back(New_Monster(MON_SPIDER_BABY, GetPos(), -1, 0, 30));
	gm_->unit_list.push_back(New_Monster(MON_SPIDER_BABY, GetPos(), -1, 0, 30));
}