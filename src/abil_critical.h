//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_critical.h
//
// 내용: 능력-크리티컬
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_CRITICAL_H__
#define  __ABIL_CRITICAL_H__

#include "ability.h"

class Abil_critical : public Ability 
{


	float GetSpeed();
public:
	Abil_critical(int level_);
	virtual ~Abil_critical();

	virtual Ability* Clone(int level_);

	virtual int GetCritical();

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_CRITICAL_H__