//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_antiexplosion.h
//
// 내용: 능력-성형작약
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_ANTIEXPLOSION_H__
#define  __ABIL_ANTIEXPLOSION_H__

#include "ability.h"

class Abil_antiexplosion : public Ability 
{

public:
	Abil_antiexplosion(int level_);
	virtual ~Abil_antiexplosion();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_ANTIEXPLOSION_H__