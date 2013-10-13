//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_mirror_damage.h
//
// 내용: 능력-반사데미지
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_MIRROR_DAMAGE_H__
#define  __ABIL_MIRROR_DAMAGE_H__

#include "ability.h"

class Abil_mirror_damage : public Ability 
{

public:
	Abil_mirror_damage(int level_);
	virtual ~Abil_mirror_damage();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	float Getdamage();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_MIRROR_DAMAGE_H__