//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_trap.cpp
//
// 내용: 함정
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_trap.h"
#include "gamemanager.h"
#include "unit.h"
#include "random.h"
#include "effect_piece.h"
#include "image.h"

Shot_trap::Shot_trap(Texture* texture_, Unit* unit_, float slow_rate_, int slow_time_, int stop_time_, int time_, int team_, coord_def pos_):
Shot_base(texture_, unit_, team_, pos_, coord_def()), 
slow_rate(slow_rate_), slow_time(slow_time_), stop_time(stop_time_), time(time_), valid(true), angle(rand_float(0,D3DX_PI*2))
{
}
Shot_trap::~Shot_trap()
{

}
bool Shot_trap::Action(Game_Manager* gm_)
{
	if(valid)
	{
		if(gm_)
		{
			for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
			{
				if((*it)->isLive() && !(*it)->isNonTarget()  && (*it)->GetTeam() != GetTeam() && (*it)->GetKind() != VT_ROBOT)
				{
					if((*it)->collution(GetPos(), 10.0f))
					{
						int damage = (*it)->GetHp()/2;

						int final_damge_ = (*it)->SetDamage(gm_, GetFirstPos(), DT_TRAP ,(float)damage, GetTeam());
						if(unit)
							unit->GiveDamage(gm_, (*it), DT_TRAP, final_damge_);

						(*it)->SetShotStop(stop_time);
						(*it)->SlowApply(slow_rate,slow_time,SK_TRAP);
						(*it)->StateApply("덫",slow_time);
						Effect_trap(gm_, (*it)->GetPos(), 1.0f);
						valid = false;
					}
				}
			}
		}


		if(time--<=0)
		{
			valid = false;
		}
	}


	if(!valid)
	{
		return true;
	}
	return false;
}


bool Shot_trap::Draw(coord_def offset_, float size_)
{
	if(GetTexture())
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size_, angle);
	else
		return false;
}