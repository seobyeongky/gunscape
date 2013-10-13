//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_fast_portal.h
//
// 내용: 능력-빠른 포탈
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_FAST_PORTAL_H__
#define  __ABIL_FAST_PORTAL_H__

#include "ability.h"

class Abil_fast_portal : public Ability 
{

public:
	Abil_fast_portal(int level_);
	virtual ~Abil_fast_portal();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	
	bool ActiveGame(Game_Manager* gm_, Player* player_);

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_FAST_PORTAL_H__