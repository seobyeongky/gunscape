//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: throw_knife.h
//
// 내용: 서브아이템. 투척나이프
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __THROW_KNIFE_H__
#define  __THROW_KNIFE_H__

#include "sub_weapon.h"

class Sub_Throw_knife: public Sub_Weapon
{
public:
	Sub_Throw_knife(Player* user_, coord_def pos_, int time_);
	virtual ~Sub_Throw_knife();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	virtual bool Equip(){return false;};
	virtual bool UnEquip(){return false;};
};


#endif // __THROW_KNIFE_H__

