//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_grenade.cpp
//
// 내용: 연막탄
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "shot_smoke_bomb.h"
#include "shot_smoke.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "random.h"
#include "texture_list.h"
#include "effect_piece.h"


Shot_smoke_bomb::Shot_smoke_bomb(Texture* texture_, Unit* unit_, int time_, int smoke_time_, float range_, int team_, coord_def pos_, coord_def target_):
Shot_grenade(texture_, unit_, time_, 0, 0,0, range_, true, team_, pos_, target_),
smoke_time(smoke_time_)
{

}
	
Shot_smoke_bomb::~Shot_smoke_bomb()
{

}

bool Shot_smoke_bomb::Bomb(Game_Manager* gm_, float power_, float max_power_, float damage_, float range_, bool selfbomb_, bool noise_)
{
	gm_->shot_list.push_back(new Shot_smoke(&tex_smoke, unit, range_, GetTeam(), GetPos(), smoke_time));
	return true;
}

