//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: fire_cloth.h
//
// 내용: 서브아이템. 방화복
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __FIRE_CLOTH_H__
#define  __FIRE_CLOTH_H__

#include "sub_weapon.h"

class Sub_Fire_Cloth: public Sub_Weapon
{
public:
	Sub_Fire_Cloth(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Fire_Cloth();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip();
	virtual bool UnEquip();

	virtual bool isEquip(){return true;};
};


#endif // __FIRE_CLOTH_H__

