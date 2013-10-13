//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: smoke_grenade.h
//
// 내용: 서브아이템. 연막탄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SMOKE_GRENADE_H__
#define  __SMOKE_GRENADE_H__

#include "sub_weapon.h"

class Sub_Smoke_Grenade: public Sub_Weapon
{
public:
	Sub_Smoke_Grenade(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Smoke_Grenade();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip(){return false;};
	virtual bool UnEquip(){return false;};
};


#endif // __SMOKE_GRENADE_H__

