//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_chaininvi.h
//
// 내용: 능력-죽이면 투명
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_CHAININVI_H__
#define  __ABIL_CHAININVI_H__

#include "ability.h"

class Abil_chaininvi : public Ability 
{

public:
	Abil_chaininvi(int level_);
	virtual ~Abil_chaininvi();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	int Getsecond();

	virtual bool KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_);


};

#endif // __ABIL_CHAININVI_H__