//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_murder.h
//
// 내용: 능력-청부살인
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_MURDER_H__
#define  __ABIL_MURDER_H__

#include "ability.h"

class Abil_murder : public Ability 
{

public:
	Abil_murder(int level_);
	virtual ~Abil_murder();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	int GetHp();


	virtual bool KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_);

};

#endif // __ABIL_MURDER_H__