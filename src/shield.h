//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shield.h
//
// 내용: 서브아이템. 전투방패
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHIELD_H__
#define  __SHIELD_H__

#include "sub_weapon.h"

class Sub_Shield: public Sub_Weapon
{
public:
	Sub_Shield(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Shield();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip();
	virtual bool UnEquip();


	virtual bool isEquip(){return true;};
};


#endif // __SHIELD_H__

