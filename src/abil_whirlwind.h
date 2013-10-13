//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_whirlwind.h
//
// 내용: 능력-휠윈드
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_WHIRLWIND_H__
#define  __ABIL_WHIRLWIND_H__

#include "ability.h"

class Abil_whirlwind : public Ability 
{

public:
	Abil_whirlwind(int level_);
	virtual ~Abil_whirlwind();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	
	virtual bool ActiveMeleeWeapon(Melee_Weapon* weapon_);

	virtual bool UnActiveMeleeWeapon(Melee_Weapon* weapon_);

};

#endif // __ABIL_WHIRLWIND_H__