//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: trap.h
//
// 내용: 서브아이템. 덫
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __TRAP_H__
#define  __TRAP_H__

#include "sub_weapon.h"

class Sub_Trap: public Sub_Weapon
{
public:
	Sub_Trap(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Trap();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip(){return false;};
	virtual bool UnEquip(){return false;};
};


#endif // __TRAP_H__

