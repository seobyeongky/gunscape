//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: adrenalin.h
//
// 내용: 서브아이템. 아드레날린
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ADRENALIN_H__
#define  __ADRENALIN_H__

#include "sub_weapon.h"

class Sub_Adrenalin: public Sub_Weapon
{
public:
	Sub_Adrenalin(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Adrenalin();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip(){return false;};
	virtual bool UnEquip(){return false;};
};


#endif // __ADRENALIN_H__

