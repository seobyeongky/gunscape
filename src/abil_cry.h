//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_cry.h
//
// 내용: 사용형 - 외침
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_CRY_H__
#define  __ABIL_CRY_H__

#include "ability.h"

class Abil_cry : public Ability 
{
	int delay;
public:
	Abil_cry(int level_);
	virtual ~Abil_cry();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	float GetSp();
	int GetStun();

	virtual bool Action(Game_Manager* gm_, Player* player_);
	virtual bool Use(Game_Manager* gm_, Player* player_);

};

#endif // __ABIL_CRY_H__