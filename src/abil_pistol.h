//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_pistol.h
//
// 내용: 능력-권총마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_PISTOL_H__
#define  __ABIL_PISTOL_H__

#include "ability.h"

class Abil_pistol : public Ability 
{

public:
	Abil_pistol(int level_);
	virtual ~Abil_pistol();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	
	virtual bool ActiveMainWeapon(Main_Weapon* weapon_);
	virtual bool UnActiveMainWeapon(Main_Weapon* weapon_);

};

#endif // __ABIL_PISTOL_H__