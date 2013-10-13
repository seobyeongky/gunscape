//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: barricade.h
//
// 내용: 서브아이템. 바리케이트
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __BARRICADE_H__
#define  __BARRICADE_H__

#include "sub_weapon.h"

class Sub_Barricade: public Sub_Weapon
{
public:
	Sub_Barricade(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Barricade();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip(){return false;};
	virtual bool UnEquip(){return false;};
};


#endif // __BARRICADE_H__

