//////////////////////////////////////////////////////////////////////////////////////////////////
//
// ÆÄÀÏÀÌ¸§: shot_bug.cpp
//
// ³»¿ë: À¸¾Ç ¹ú·¹! Â¡±×·¯!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_bug.h"
#include "gamemanager.h"
#include "player.h"
#include "unit.h"
#include "image.h"
#include "effect_piece.h"
#include "Map.h"


Shot_bug::Shot_bug(Texture* texture_, Unit* unit_, float damage_, coord_def start_, coord_def goal_, int time_, int team_, int delay_):
Unit("¶¥±¼¹ú·¹",texture_, start_.x, start_.y, team_, 100),
damage(damage_),valid(true), head(unit_),angle(GetAngleToTarget(start_,goal_)), ishead(delay_?false:true), fly_speed((goal_ - start_)*2.0f/(float)time_), fly_acc(-fly_speed/(float)time_), fly_time(time_), fly(time_), delay(delay_)
{
	SetSize(10.0f);
}
Shot_bug::~Shot_bug()
{

}
bool Shot_bug::Action(Game_Manager* gm_)
{
	if(valid)
	{
		if(delay>0)
		{
			delay--;
			if(delay==0)
				Effect_dust(gm_, GetPos(), 10,  2.0f, 0.8f);

		}
		else
		{
			if(gm_)
			{
				for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
				{
					if((*it)->isLive() && !(*it)->isNonTarget()  && (*it)->GetTeam() != GetTeam())
					{
						bool hit_ = true;
						for(list<Unit*>::iterator it2 = hit_unit.begin(); it2 != hit_unit.end() ; it2++)
						{
							if((*it) == (*it2))
							{
								hit_ = false;
							}
						}
						if(hit_ && (*it)->collution(GetPos(), 8.0f))
						{
							Damage(gm_, (*it));
						}
					}
				}
			}

			if(fly)
			{
				Move(GetPos().x + fly_speed.x, GetPos().y + fly_speed.y);
				fly_speed += fly_acc;
				fly--;
			}
			else
			{
				valid = false;
				Effect_dust(gm_, GetPos(), 10,  2.0f, 0.8f);
			}
		}
	}


	if(!valid)
	{
		return true;
	}
	return false;
}


void Shot_bug::Damage(Game_Manager* gm_, Unit* unit_)
{
	if(!head)
		return;
	if(!unit_)
		return;
	int final_damge_ = unit_->SetDamage(gm_, head->GetPos(), DT_MELEE ,damage, GetTeam());
	if(head)
	{
		head->GiveDamage(gm_, unit_, DT_MELEE, final_damge_);
		unit_->SetSlow(20);
		if(unit_->GetMirrorDamage())
		{
			head->SetDamage(gm_, unit_->GetPos(), DT_MIRROR, unit_->GetMirrorDamage(), unit_->GetTeam());
		}

	}
	hit_unit.push_back(unit_);
	//ÈÄ¿¡ È­¿°µ¥¹ÌÁöµµ ³Ö´Â´Ù.
}

bool Shot_bug::Draw(Game_Manager* gm_, coord_def offset_, float size_)
{
	if(delay>0)
		return false;
	float size__ = (!fly)?1.0f:(1.0f+sin(fly*D3DX_PI/fly_time));
	if(GetTexture())
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size_*size__ , angle);
	else
		return false;
}

bool Shot_bug::TargetLost()
{
	if(head && !head->isLive())
	{
		head = NULL;
		valid = false;
	}
	for(list<Unit*>::iterator it = hit_unit.begin(); it != hit_unit.end() ;)
	{
		if((*it) && !(*it)->isLive())
		{
			list<Unit*>::iterator temp = it;
			it++;
			hit_unit.erase(temp);
		}
		else
			it++;
	}
	return false;
}
int Shot_bug::SetDamage(Game_Manager* gm_, coord_def c, Damage_Type type_, float damage_, int team_, float sniper_, int critical_)
{	
	int final_damage_ = 0;
	if(head)
	{
		final_damage_ = head->SetDamage(gm_, c, type_, damage_/(ishead?2.0f:2.0f), team_, sniper_, ishead?critical_:0);
	}
	if(!isNonLife() && final_damage_ && !isNonTarget())
		Effect_blood(gm_, GetPos(), (int)(damage_/5+1), 1.0f);
	return final_damage_;
}
void Shot_bug::SetPoison(float damage_, int turn_, Unit* unit_)
{
	if(head)
	{
		head->SetPoison(damage_, turn_, unit_);
	}
};