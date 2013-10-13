//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_killstamina.h
//
// 내용: 능력-스태미나얻기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_KILLSTAMINA_H__
#define  __ABIL_KILLSTAMINA_H__

#include "ability.h"

class Abil_kill_stamina : public Ability 
{

public:
	Abil_kill_stamina(int level_);
	virtual ~Abil_kill_stamina();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	float Getstamina();
	
	virtual bool KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_);

};

#endif // __ABIL_KILLSTAMINA_H__