//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: hammer.h
//
// 내용: 서브아이템. 해머
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __HAMMER_H__
#define  __HAMMER_H__

#include "melee_weapon.h"

class Melee_Hammer: public Melee_Weapon
{
public:
	Melee_Hammer(const melee_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Melee_Hammer();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
};


#endif // __HAMMER_H__

