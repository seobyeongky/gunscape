//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_sniper.cpp
//
// 내용: 스나이퍼
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "named_sniper.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "random.h"
#include "image.h"
#include "ai_sniper.h"
#include "main_weapon.h"

Named_Sniper::Named_Sniper(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
count(0), sniper(0), target(NULL), sniper_pos()
{
}
Named_Sniper::~Named_Sniper()
{
}
bool Named_Sniper::charDraw(Game_Manager* gm_, coord_def offset, float size_)
{
	bool return_= false;
	float size__ = GetFlySize();
	if(GetTexture())
		return_ |= GetTexture()->Draw((GetX()-offset.x)*size_,( GetY()-offset.y)*size_, size_*size__, size_*size__, GetAngle(), D3DCOLOR_ARGB(GetAlpha(gm_),255,255,255));
	
	if(sniper)
	{
		if(target)
		{
			coord_def c = sniper_pos;
			float size2__ = target->GetFlySize();
			return_ |=  tex_target.Draw((c.x-offset.x)*size_,(c.y-offset.y)*size_, size_*size2__, size_*size2__, 0, D3DCOLOR_ARGB(255,255,255,255));
		}
	}
	return return_;
}
void Named_Sniper::SetAi(monster_state state_, Unit* head_, int level_)
{
	if(!ai)
	{
		ai = new Ai_Sniper(state_, this, head_, level_);
	}
}
bool Named_Sniper::Action_in(Game_Manager* gm_)
{
	if(!isLive())
	{	
		DropItem(gm_);
		return true;
	}
	if(GetWarning()>0)
		UpDownWarning(-5);

	if(weapon && GetFocus()>0)
	{
		UpDownFocus(-weapon->GetFocusCalm());
		if(GetFocus()<0)
			SetFocus(0);
	}
	
	if(!nonmove_delay && !GetFly()/*!fly.fly*/ && !sniper)
	{
		if(ai)
			ai->Action();
	}
	else
	{
	
		if(nonmove_delay)
			nonmove_delay--;
	}

	if(target_continue>0)
		target_continue--;
	if(sniper>0)
	{
		if(sniper>15 && target)
		{
			sniper_pos = target->GetPos();
		}
		sniper--;
		if(sniper==0)
		{
			count = 255;
			Monster::Shot(gm_, sniper_pos, 0.0f);
			SetShotStop(500);
		}
	}
	
	if(weapon) //현재 주아이템이 있다.
		weapon->Passive(gm_, NULL, true);//발휘되는 패시브 효과		

	Special_Action(gm_);
	CommonAction(gm_);
	return false;
}

bool Named_Sniper::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{	
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!GetDelay()  && !sniper)
	{		
		sniper = 45;
		sniper_pos = c;
		if(ai)
		{
			target = ai->GetTarget();
		}
		return true;
	}
	return false;
}
bool Named_Sniper::Special_Action(Game_Manager* gm_)
{
	SetInvisible(255-count);
	if(count>0)
		count-=5;
	return true;
}
bool Named_Sniper::TargetLost()
{
	if(target && !target->isLive())
	{
		target = NULL;
		sniper = 0;
	}
	return false;
}