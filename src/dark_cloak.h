//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: dark_cloak.h
//
// 내용: 서브아이템. 보호색 망토
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __DARK_CLOAK_H__
#define  __DARK_CLOAK_H__

#include "sub_weapon.h"

class Sub_Cloak: public Sub_Weapon
{
public:
	Sub_Cloak(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Cloak();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip();
	virtual bool UnEquip();

	virtual void Passive(Game_Manager* gm_, Player* unit_, bool current_);

	virtual bool isEquip(){return true;};
};


#endif // __DARK_CLOAK_H__

