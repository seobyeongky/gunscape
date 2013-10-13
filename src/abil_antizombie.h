//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_antizombie.h
//
// 내용: 능력-좀비전문가
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_ANTIZOMBIE_H__
#define  __ABIL_ANTIZOMBIE_H__

#include "ability.h"

class Abil_antizombie : public Ability 
{
	int count;
public:
	Abil_antizombie(int level_);
	virtual ~Abil_antizombie();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	float GetSpeed();
	float GetRange();
	virtual bool Action(Game_Manager* gm_, Player* player_);
	virtual bool ActiveGame(Game_Manager* gm_, Player* player_);
};

#endif // __ABIL_ANTIZOMBIE_H__