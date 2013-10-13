//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_hammer.cpp
//
// 내용: 밀리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "Shot_hammer.h"
#include "unit.h"
#include "gamemanager.h"
#include "image.h"
#include "effect_message.h"
#include "random.h"
#include "sound.h"


Shot_hammer::Shot_hammer(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, int time_, int team_, coord_def pos_, float angle_, float size_, float width_, float back_stab_):
Shot_melee( texture_, unit_, damage_, power_, max_power_, time_, team_, pos_, angle_, size_, width_, back_stab_)
{

}


Shot_hammer::~Shot_hammer()
{

}
void Shot_hammer::Hit(Game_Manager* gm_, Unit* unit_)
{
	Damage_Type dt_ = DT_MELEE;
	float damage_ = damage;
	float power_ = power;
	float max_power_ = max_power;
	bool backstab_ok_ = false;
	if(unit && unit->GetCritical() && unit->GetCritical()>rand_int(0,99))
	{
		backstab_ok_ = true;
	}
	if(back_stab > 1.0f && (backstab_ok_ ||  unit_->isBackStabbing()))
	{

		damage_ *= back_stab;
		Effect_simple_speak(gm_,"백스탭!",unit_->GetPos());
		PlaySE(se_backstab, false);
		ok_backstab = true;
		dt_ = DT_BACK_STAB;	
		power_ *= 3;
		max_power_ *= 3;
	}
	int final_damge_ = unit_->SetDamage(gm_, GetFirstPos(), dt_ ,damage_, GetTeam());
	if(unit)
	{
		unit->GiveDamage(gm_, unit_, dt_, final_damge_);
		{
			float angle_ = GetAngleToTarget(GetPos(), unit_->GetPos());
			float knockback_ = power_*5.0f+unit_->GetSize();
			coord_def knock_pos = unit_->GetPos()+coord_def(cos(angle_)*knockback_,sin(angle_)*knockback_);
			int i = map->CollutionPosToPos( unit_->GetPos(), knock_pos,(int)knockback_);
			if(i)
			{
				knockback_ =(float)i,0;
			}
			knockback_= max(0, knockback_-unit_->GetSize());
			knock_pos = unit_->GetPos()+coord_def(cos(angle_)*knockback_,sin(angle_)*knockback_);
			unit_->Fly(gm_, knock_pos, 30);
		}
	}
	hit_unit.push_back(unit_);
}
