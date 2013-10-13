//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: grenade.h
//
// 내용: 서브아이템. 수류탄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __GRENADE_H__
#define  __GRENADE_H__

#include "sub_weapon.h"

class Sub_Grenade: public Sub_Weapon
{
public:
	Sub_Grenade(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Grenade();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip(){return false;};
	virtual bool UnEquip(){return false;};
};


#endif // __GRENADE_H__

