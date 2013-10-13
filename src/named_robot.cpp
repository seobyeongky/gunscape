//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_robot.cpp
//
// 내용: 경비로봇
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "named_robot.h"
#include "main_weapon.h"
#include "random.h"


Named_robot::Named_robot(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),angle_delay(0),current_weapon(1),
second_weapon(NULL),third_weapon(NULL)
{

}
Named_robot::~Named_robot()
{
	if(second_weapon)
		second_weapon = NULL;
	if(third_weapon)
		third_weapon = NULL;
}
bool Named_robot::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!GetDelay() && Current_weapon())
	{
		focus_ += Current_weapon()->GetFocusBase()+GetFocusSum();
		if(SetDelay(Current_weapon()->Shot(gm_, this, GetTeam(), GetPos(), c, focus_)*panalty) == -1)
		{
			SetDelay(0.0f);
			Reload(current_weapon);
		}
		else
		{
			SetTargetContinue(50);
			angle_delay = GetDelay()+5;
		}
		if(GetFocus() < Current_weapon()->GetFocusMaxReact())
			UpDownFocus(Current_weapon()->GetFocusReact());
		return true;
	}
	return false;
}
bool Named_robot::Reload(int num_)
{//나중에 bullet의 갯수에 의해서 리로딩하게 하자
	if(Select_weapon(num_))
	{
		float need_bullet = 1.0f-((float)Select_weapon(num_)->GetBullet()/(int)Select_weapon(num_)->GetMaxBullet());
		if(need_bullet)
		{
			SetDelay(Select_weapon(num_)->Reload(need_bullet));
		}
		current_weapon = rand_int(1,3);
	}
	return true;
}
Main_Weapon* Named_robot::Current_weapon()
{
	switch(current_weapon)
	{
	case 1:
		return weapon;
	case 2:
		return second_weapon;
	case 3:
		return third_weapon;
	}
	return weapon;
}
Main_Weapon* Named_robot::Select_weapon(int num_)
{
	switch(num_)
	{
	case 1:
		return weapon;
	case 2:
		return second_weapon;
	case 3:
		return third_weapon;
	}
	return weapon;
}
bool Named_robot::Action_in(Game_Manager* gm_)
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
	if(!nonmove_delay)
	{
		if(ai)
			ai->Action();
	}
	else
		nonmove_delay--;

	if(angle_delay)
		angle_delay--;
	
	if(target_continue)
		target_continue--;

	if(weapon) //현재 주아이템이 있다.
		weapon->Passive(gm_, NULL, true);//발휘되는 패시브 효과
	if(second_weapon) //현재 주아이템이 있다.
		second_weapon->Passive(gm_, NULL, true);//발휘되는 패시브 효과	
	if(third_weapon) //현재 주아이템이 있다.
		third_weapon->Passive(gm_, NULL, true);//발휘되는 패시브 효과	


	Special_Action(gm_);
	CommonAction(gm_);
	return false;
}

void Named_robot::SetWeapon(Main_Weapon* second_weapon_, Main_Weapon* third_weapon_)
{
	second_weapon = second_weapon_;
	third_weapon = third_weapon_;
	Reload(1);
	Reload(2);
	Reload(3);
}
void Named_robot::SetAngle(float angle_)
{
	if(angle_delay && current_weapon == 1)
	{
		if(abs(GetAngle() - angle_)>0.01f)
		{
			float direc_ = sin(angle_-GetAngle()); //왼쪽으로 회전해야할지 오른쪽으로 회전해야할지

			if(direc_>0)
				UpDownAngle(0.01f);
			else
				UpDownAngle(-0.01f);
		}
		else
			Unit::SetAngle(angle_);
	}
	else
		Unit::SetAngle(angle_);
};