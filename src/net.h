//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: net.h
//
// 내용: 서브아이템. 그물
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NET_H__
#define  __NET_H__

#include "sub_weapon.h"

class Sub_Net: public Sub_Weapon
{
public:
	Sub_Net(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Net();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip(){return false;};
	virtual bool UnEquip(){return false;};
};


#endif // __NET_H__

