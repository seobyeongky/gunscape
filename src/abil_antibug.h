//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_antibug.h
//
// 내용: 능력-벌레방지약
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_ANTIBUG_H__
#define  __ABIL_ANTIBUG_H__

#include "ability.h"

class Abil_antibug : public Ability 
{
public:
	Abil_antibug(int level_);
	virtual ~Abil_antibug();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	float GetValue();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_ANTIBUG_H__