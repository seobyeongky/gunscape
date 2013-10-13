//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: running_shoes.h
//
// ����: ���������. ���׽���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __RUNNING_SHOES_H__
#define  __RUNNING_SHOES_H__

#include "sub_weapon.h"

class Sub_Running_Shoes: public Sub_Weapon
{
public:
	Sub_Running_Shoes(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Running_Shoes();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip();
	virtual bool UnEquip();

	virtual bool isEquip(){return true;};
};


#endif // __RUNNING_SHOES_H__

