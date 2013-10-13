//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_flame.h
//
// 내용: 능력-화염방사기마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_FLAME_H__
#define  __ABIL_FLAME_H__

#include "ability.h"

class Abil_flame : public Ability 
{

public:
	Abil_flame(int level_);
	virtual ~Abil_flame();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	
	virtual bool ActiveMainWeapon(Main_Weapon* weapon_);
	virtual bool UnActiveMainWeapon(Main_Weapon* weapon_);

};

#endif // __ABIL_FLAME_H__