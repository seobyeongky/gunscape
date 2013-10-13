//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_bullet.h
//
// 내용: 능력 - 예비 탄창
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_BULLET_H__
#define  __ABIL_BULLET_H__

#include "ability.h"

class Abil_bullet : public Ability 
{

public:
	Abil_bullet(int level_);
	virtual ~Abil_bullet();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_BULLET_H__