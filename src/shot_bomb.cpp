//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_bomb.cpp
//
// 내용: 수류탄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_bomb.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "random.h"
#include "effect_piece.h"
#include "Map.h"

Shot_bomb::Shot_bomb(Unit* unit_, coord_def pos_, float damage_, float power_, float max_power_, float range_, int team_):
Shot_base(NULL, unit_, team_, pos_, coord_def()), 
damage(damage_), power(power_), max_power(max_power_), range(range_)
{
}
Shot_bomb::~Shot_bomb()
{

}
bool Shot_bomb::Action(Game_Manager* gm_)
{
	Bomb(gm_, power, max_power, damage, range,false,false);
	return true;
}
bool Shot_bomb::Draw(coord_def offset_, float size_)
{
	return false;
}
