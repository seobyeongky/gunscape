//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_shot_gun.h
//
// 내용: 능력-샷건마스터리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_SHOT_GUN_H__
#define  __ABIL_SHOT_GUN_H__

#include "ability.h"

class Abil_shot_gun : public Ability 
{

public:
	Abil_shot_gun(int level_);
	virtual ~Abil_shot_gun();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	
	virtual bool ActiveMainWeapon(Main_Weapon* weapon_);
	virtual bool UnActiveMainWeapon(Main_Weapon* weapon_);

};

#endif // __ABIL_SHOT_GUN_H__