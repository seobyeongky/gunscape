//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_immortal.h
//
// 내용: 사용형 - 불사의분노
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_IMMORTAL_H__
#define  __ABIL_IMMORTAL_H__

#include "ability.h"

class Abil_immortal : public Ability 
{
	int count;
	bool immortal;
public:
	Abil_immortal(int level_);
	virtual ~Abil_immortal();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	float GetConsum();

	virtual bool Action(Game_Manager* gm_, Player* player_);

	virtual bool isUsing(){return immortal;};
	virtual bool Use(Game_Manager* gm_, Player* player_);
	virtual bool UnUse(Game_Manager* gm_, Player* player_);

	
	void End(Game_Manager* gm_, Player* player_);
};

#endif // __ABIL_IMMORTAL_H__