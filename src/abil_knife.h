//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_knife.h
//
// 내용: 능력-나이프마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_KNIFE_H__
#define  __ABIL_KNIFE_H__

#include "ability.h"

class Abil_knife : public Ability 
{

public:
	Abil_knife(int level_);
	virtual ~Abil_knife();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	float GetDamage();

	
	virtual bool ActiveMeleeWeapon(Melee_Weapon* weapon_);
	virtual bool ActiveMainWeapon(Main_Weapon* weapon_);
	virtual bool UnActiveMeleeWeapon(Melee_Weapon* weapon_);
	virtual bool UnActiveMainWeapon(Main_Weapon* weapon_);

};

#endif // __ABIL_KNIFE_H__