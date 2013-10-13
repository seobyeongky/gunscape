//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_see_sight.h
//
// 내용: 능력-시야확인
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_SEE_SIGHT_H__
#define  __ABIL_SEE_SIGHT_H__

#include "ability.h"

class Abil_see_sight : public Ability 
{
public:
	Abil_see_sight(int level_);
	virtual ~Abil_see_sight();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
	
};

#endif // __ABIL_SEE_SIGHT_H__