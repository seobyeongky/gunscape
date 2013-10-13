//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_fling.cpp
//
// 내용: 적을 뒤집어 버리는 벌레. 무섭다!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "mon_bug_fling.h"
#include "gamemanager.h"

Mon_bug_filng::Mon_bug_filng(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
fling(true)
{

}
Mon_bug_filng::~Mon_bug_filng()
{

}

void Mon_bug_filng::MeleeDamage(Game_Manager* gm_, Unit* target_)
{
	target_->SetDamage(gm_, GetPos(), DT_MELEE, GetDamage(), GetTeam());
	target_->SetSlow(100);
	if(fling)
	{
		float angle_ = GetAngleToTarget(target_->GetPos(),GetPos());
		float knockback_ = 50.0f;
		coord_def knock_pos = target_->GetPos()+coord_def(cos(angle_)*knockback_,sin(angle_)*knockback_);
		int i =  gm_->map->CollutionPosToPos( target_->GetPos(), knock_pos,(int)knockback_);
		if(i)
		{
			knockback_ =(float)i,0;
		}
		knockback_= max(0, knockback_-target_->GetSize());
		knock_pos = target_->GetPos()+coord_def(cos(angle_)*knockback_,sin(angle_)*knockback_);
		target_->Fly(gm_, knock_pos, 20);
		SetStop(20);
		fling = false;
	}
}