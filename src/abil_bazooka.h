//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_bazooka.h
//
// 내용: 능력-바주카마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_BAZOOKA_H__
#define  __ABIL_BAZOOKA_H__

#include "ability.h"

class Abil_bazooka : public Ability 
{

public:
	Abil_bazooka(int level_);
	virtual ~Abil_bazooka();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	
	virtual bool ActiveMainWeapon(Main_Weapon* weapon_);
	virtual bool UnActiveMainWeapon(Main_Weapon* weapon_);

};

#endif // __ABIL_BAZOOKA_H__