//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_rifle.h
//
// 내용: 능력-라이플마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_RIFLE_H__
#define  __ABIL_RIFLE_H__

#include "ability.h"

class Abil_rifle : public Ability 
{

public:
	Abil_rifle(int level_);
	virtual ~Abil_rifle();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	
	virtual bool ActiveMainWeapon(Main_Weapon* weapon_);
	virtual bool UnActiveMainWeapon(Main_Weapon* weapon_);

};

#endif // __ABIL_RIFLE_H__