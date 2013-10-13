//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_stealth.h
//
// 내용: 능력-도둑걸음(늦게 발견)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_STEALTH_H__
#define  __ABIL_STEALTH_H__

#include "ability.h"

class Abil_stealth : public Ability 
{
public:
	Abil_stealth(int level_);
	virtual ~Abil_stealth();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	
	int GetTime();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_STEALTH_H__