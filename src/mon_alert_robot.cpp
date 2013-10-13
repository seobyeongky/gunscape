//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_alert_robot.cpp
//
// 내용: 경보로봇
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_alert_robot.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "image.h"
#include "random.h"
#include "effect_piece.h"

Mon_alert_robot::Mon_alert_robot(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
search_angle(rand_float(0,D3DX_PI*2)), count(0)
{
	SetTargetContinue(-1);
	ApplyBackPanalty(0.0f);
}
Mon_alert_robot::~Mon_alert_robot()
{
}


bool Mon_alert_robot::charDraw(Game_Manager* gm_, coord_def offset, float size_)
{
	bool return_= false;
	float size__ = GetFlySize();
	if(GetTexture())
		return_ |= GetTexture()->Draw((GetX()-offset.x)*size_,( GetY()-offset.y)*size_, size_*size__, size_*size__, GetMoveAngle(), D3DCOLOR_ARGB(GetAlpha(gm_),255,255,255));
	return_ |=  tex_mon_alert.Draw((GetX()-offset.x)*size_,( GetY()-offset.y)*size_, size_*size__, size_*size__, GetAngle(), D3DCOLOR_ARGB(GetAlpha(gm_),255,255,255));

	if(ai->GetState() == MS_ATTACK)
	{
		if(ai->GetTarget())
		{
			coord_def c = ai->GetTarget()->GetPos();
			float size2__ = ai->GetTarget()->GetFlySize();
			return_ |=  tex_alert_target.Draw((c.x-offset.x)*size_,(c.y-offset.y)*size_, size_*size2__, size_*size2__, 0, D3DCOLOR_ARGB(GetAlpha(gm_),255,255,255));
		}
	}
	return return_;
}


bool Mon_alert_robot::Special_Action(Game_Manager* gm_)
{
	count++;
	if(count % 50 == 0)
	{
		if(ai->GetState() == MS_ATTACK)
		{
			if(ai->GetTarget())
			{
				coord_def c = ai->GetTarget()->GetPos();
				Effect_alert(gm_, c, 0.5f);
				gm_->Noise(GetTeam(),c,150.0f);				
			}
		}

	}
	search_angle+=0.05f;
	return true;
}