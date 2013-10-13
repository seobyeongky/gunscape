//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_moonwalk.h
//
// 내용: 능력-문워크
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_MOONWALK_H__
#define  __ABIL_MOONWALK_H__

#include "ability.h"

class Abil_moonwalk : public Ability 
{

public:
	Abil_moonwalk(int level_);
	virtual ~Abil_moonwalk();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_MOONWALK_H__