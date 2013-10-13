//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_water.cpp
//
// 내용: 물뿌리기
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include <math.h>
#include "shot_water.h"
#include "random.h"
#include "gamemanager.h"
#include "Unit.h"
#include "image.h"


Shot_water::Shot_water(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, int time_, int team_, coord_def pos_, float angle_, float speed_, float size_inc_):
Shot_fire(texture_, unit_, damage_, 0, time_, team_, pos_, angle_, speed_, size_inc_),
power(power_), max_power(max_power_)
{
	color = D3DCOLOR_ARGB(150,rand_int(0,150),rand_int(150,255),255);
}

Shot_water::~Shot_water()
{

}



void Shot_water::Damage(Game_Manager* gm_, Unit* unit_)
{
	unit_->SetKnockback(power, max_power, angle);
	int final_damge_ = unit_->SetDamage(gm_, GetFirstPos(), DT_WATER ,damage, GetTeam());
	if(unit)
		unit->GiveDamage(gm_, unit_, DT_WATER, final_damge_);
	hit_unit.push_back(unit_);
}
