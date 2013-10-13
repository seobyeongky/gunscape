//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_deathbomb.h
//
// 내용: 능력-연쇄폭발
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_DEATHBOMB_H__
#define  __ABIL_DEATHBOMB_H__

#include "ability.h"

class Abil_deathbomb : public Ability 
{
public:
	Abil_deathbomb(int level_);
	virtual ~Abil_deathbomb();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	float GetDamage();
	float GetRange();

	virtual bool KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_);

};

#endif // __ABIL_DEATHBOMB_H__