//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_instant_heal.h
//
// 내용: 능력-인스턴스-즉시회복
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_INSTANT_HEAL_H__
#define  __ABIL_INSTANT_HEAL_H__

#include "ability.h"

class Abil_Instant_heal : public Ability 
{
public:
	Abil_Instant_heal(int level_);
	virtual ~Abil_Instant_heal();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool InstanceActive(Player* player_);
};

#endif // __ABIL_INSTANT_HEAL_H__