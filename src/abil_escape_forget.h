//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_.h
//
// 내용: 따돌리기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_ESCAPE_FORGET_H__
#define  __ABIL_ESCAPE_FORGET_H__

#include "ability.h"

class Abil_Escape_Forget : public Ability 
{

public:
	Abil_Escape_Forget(int level_);
	virtual ~Abil_Escape_Forget();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();


	virtual bool ActivePlayer(Player* player_);
	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_ESCAPE_FORGET_H__