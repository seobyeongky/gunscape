//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_map.h
//
// 내용: 능력-맵핵
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_MAP_H__
#define  __ABIL_MAP_H__

#include "ability.h"

class Abil_map : public Ability 
{
public:
	Abil_map(int level_);
	virtual ~Abil_map();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_SEE_SIGHT_H__