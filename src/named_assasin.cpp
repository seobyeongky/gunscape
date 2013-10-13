//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_assasin.cpp
//
// 내용: 스파이!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "named_assasin.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "effect_message.h"
#include "sound.h"
#include "random.h"

Named_Assasin::Named_Assasin(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
count(0)
{
}
Named_Assasin::~Named_Assasin()
{

}
bool Named_Assasin::Special_Action(Game_Manager* gm_)
{
	SetInvisible(255-count);
	if(count>0)
		count-=5;

	if(ai)
	{
		Unit* unit_ = ai->GetTarget();
		if(unit_)
		{	
			float angle_ = GetAngleToTarget(GetPos(),unit_->GetPos());
			if(GetAlpha(gm_)<230 && cos(unit_->GetAngle()-angle_)<0)
			{				
				SetShotStop(0);
				return true;
			}
		}
	}
	SetShotStop(-1);
	
	return true;
}
bool Named_Assasin::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{	
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!GetDelay())
	{
		count = 255;
		Monster::Shot(gm_, c, focus_);
		return true;
	}
	return false;
}

void Named_Assasin::MeleeDamage(Game_Manager* gm_, Unit* target_)
{
	float angle_ = GetAngleToTarget(GetPos(),target_->GetPos());
	float damage__ = GetDamage();
	Damage_Type dt_ = DT_MELEE;
	if(cos(target_->GetAngle()-angle_)>0)
	{
		damage__*=8;
		Effect_simple_speak(gm_,"백스탭!",target_->GetPos());
		dt_ = DT_BACK_STAB;
		PlaySE(se_backstab, false);
	}


	int damage_ = target_->SetDamage(gm_, GetPos(), dt_, damage__, GetTeam());
	GiveDamage(gm_, target_, DT_MELEE, damage_);
	target_->SetSlow(20);


	if(target_->GetMirrorDamage())
	{
		SetDamage(gm_, target_->GetPos(), DT_MIRROR, target_->GetMirrorDamage(), target_->GetTeam());
	}
	if(target_->GetMirrorKnockback())
	{
		SetKnockback(target_->GetMirrorKnockback(), target_->GetMirrorKnockback()*2, GetAngleToTarget(target_->GetPos(),GetPos()));
	}
}
