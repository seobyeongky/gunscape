//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_zombie_noise.cpp
//
// 내용: 죽으면 소음을 낸다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_zombie_noise.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "effect_piece.h"

Mon_zombie_noise::Mon_zombie_noise(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_), 
noise(true), count(0)
{

}
Mon_zombie_noise::~Mon_zombie_noise()
{
}

void Mon_zombie_noise::Death(Game_Manager* gm_)
{
	Effect_noise(gm_, GetPos(), 1.0f);
	gm_->Noise(GetTeam(),GetPos(),200.0f);
}