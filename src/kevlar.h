//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: kevlar.h
//
// 내용: 서브아이템. 방탄복
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __KEVLAR_H__
#define  __KEVLAR_H__

#include "sub_weapon.h"

class Sub_Kevlar: public Sub_Weapon
{
public:
	Sub_Kevlar(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Kevlar();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip();
	virtual bool UnEquip();

	virtual bool isEquip(){return true;};
};


#endif // __KEVLAR_H__

