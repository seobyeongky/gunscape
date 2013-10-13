//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_bulletup.h
//
// ����: �ɷ�-źâ ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_BULLETUP_H__
#define  __ABIL_BULLETUP_H__

#include "ability.h"


class Abil_bulletup : public Ability 
{

public:
	Abil_bulletup(int level_);
	virtual ~Abil_bulletup();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	
	virtual bool ActiveMainWeapon(Main_Weapon* weapon_);
	virtual bool UnActiveMainWeapon(Main_Weapon* weapon_);

};


#endif // __ABIL_SPEEDRELOAD_H__