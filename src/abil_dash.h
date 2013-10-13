//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_dash.h
//
// 내용: 사용형 - 대쉬
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_DASH_H__
#define  __ABIL_DASH_H__

#include "ability.h"

class Abil_dash : public Ability 
{
	int delay;
public:
	Abil_dash(int level_);
	virtual ~Abil_dash();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	float GetSp();

	virtual bool Action(Game_Manager* gm_, Player* player_);
	virtual bool Use(Game_Manager* gm_, Player* player_);

};

#endif // __ABIL_DASH_H__