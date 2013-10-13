//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: silencer.h
//
// 내용: 서브아이템. 소음기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SILENCER_H__
#define  __SILENCER_H__

#include "sub_weapon.h"

class Sub_Silencer: public Sub_Weapon
{
public:
	Sub_Silencer(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Silencer();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip();
	virtual bool UnEquip();

	virtual bool isEquip(){return true;};
};


#endif // __SILENCER_H__

