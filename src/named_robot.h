//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_robot.h
//
// 내용: 경비로봇
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NAME_ROBOT_H__
#define  __NAME_ROBOT_H__


#include "monster.h"


class Named_robot: public Monster
{
	int angle_delay; 

	int current_weapon;
	
	Main_Weapon* second_weapon;
	Main_Weapon* third_weapon;
public:
	Named_robot(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Named_robot();
	
	virtual bool Action_in(Game_Manager* gm_);

	virtual void SetWeapon(Main_Weapon* second_weapon_, Main_Weapon* third_weapon_);

	virtual bool isNamed(){return true;};	

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
	
	bool Reload(int num_);
	Main_Weapon* Current_weapon();
	Main_Weapon* Select_weapon(int num_);
	virtual void SetAngle(float angle_);

	virtual bool CanSpeeing(){return false;};	
};

#endif // __NAME_JACK_H__