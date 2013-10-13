//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_hack_slash.h
//
// 내용: 능력-핵앤 ㅅ슬래쉬!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_HACK_SLASH_H__
#define  __ABIL_HACK_SLASH_H__

#include "ability.h"

class Abil_hack_slash : public Ability 
{

public:
	Abil_hack_slash(int level_);
	virtual ~Abil_hack_slash();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	
	int Getsecond();
	float Getattack();
	
	virtual bool KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_);

};


#endif // __ABIL_HACK_SLASH_H__