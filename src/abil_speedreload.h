//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_speedreload.h
//
// ����: �ɷ�-���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_SPEEDRELOAD_H__
#define  __ABIL_SPEEDRELOAD_H__

#include "ability.h"


class Abil_speedreload : public Ability 
{

public:
	Abil_speedreload(int level_);
	virtual ~Abil_speedreload();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	float GetSpeed();
	
	virtual bool ActiveMainWeapon(Main_Weapon* weapon_);
	virtual bool UnActiveMainWeapon(Main_Weapon* weapon_);

};


#endif // __ABIL_SPEEDRELOAD_H__