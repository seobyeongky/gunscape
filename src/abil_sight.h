//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_sight.h
//
// 내용: 능력 구현쉽게 하기위한 틀
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_SIGHT_H__
#define  __ABIL_SIGHT_H__

#include "ability.h"

class Abil_sight : public Ability 
{

public:
	Abil_sight(int level_);
	virtual ~Abil_sight();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_SIGHT_H__