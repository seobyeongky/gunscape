//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_fire.h
//
// 내용: 능력-지옥불
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_FIRE_H__
#define  __ABIL_FIRE_H__

#include "ability.h"

class Abil_fire : public Ability 
{

public:
	Abil_fire(int level_);
	virtual ~Abil_fire();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);
	virtual bool ActiveMainWeapon(Main_Weapon* weapon_);

	virtual bool UnActivePlayer(Player* player_);
	virtual bool UnActiveMainWeapon(Main_Weapon* weapon_);
};

#endif // __ABIL_FIRE_H__