//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_rock.cpp
//
// 내용: 바위
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_rock.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "texture_list.h"
#include "random.h"
#include "effect_piece.h"
#include "Map.h"

Shot_rock::Shot_rock(Texture* texture_, Unit* unit_, int time_, float damage_, int bunch_, float power_, float max_power_, float range_, bool pentan_, int team_, coord_def pos_, coord_def target_):
Shot_grenade(texture_,unit_,time_,damage_, power_, max_power_, range_, pentan_, team_, pos_, target_),
bunch(bunch_), const_time(time_)
{
}
Shot_rock::~Shot_rock()
{

}

bool Shot_rock::Bomb(Game_Manager* gm_, float power_, float max_power_, float damage_, float range_, bool selfbomb_, bool noise_)
{
	if(gm_)
	{
		for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
		{
			if((*it)->isLive() && !(*it)->isNonTarget() )
			{
				if((*it)->GetTeam() != GetTeam())
				{
					if((*it)->collution(GetPos(), range_))
					{
						if(!map->CollutionPosToPos(GetPos(), (*it)->GetPos()))
						{
							(*it)->SetKnockback(power_, max_power_, GetAngleToTarget(GetPos(), (*it)->GetPos()));
							int final_damge_ = (*it)->SetDamage(gm_, first_pos, DT_ROCK, damage_, GetTeam());
							if(unit)
								unit->GiveDamage(gm_, (*it), DT_ROCK, final_damge_);
						}
					}
				}
			}
		}
	}

	if(noise_)
		gm_->Noise(GetTeam(),GetPos(),100.0f);
	Effect_rockbomb(gm_, GetPos(), 5, 1.0f, 0.5f);
	
	for(int i = 0; i< bunch ; i++)
	{
		coord_def temp_ = GetPos();
		float angle__ = rand_float(0,D3DX_PI*2);
		float range__ = rand_float(0,35.0f);
		temp_ += coord_def(cos(angle__)*range__, sin(angle__)*range__);
		gm_->shot_list.push_back(new Shot_rock(&tex_small_rock, unit,50, damage/2, 0, power/2, max_power/2, range/2, pentan, team, GetPos(), temp_));
	}
	return true;
}