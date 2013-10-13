//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_invisible.h
//
// 내용: 사용형 - 투명
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_INVISIBLE_H__
#define  __ABIL_INVISIBLE_H__

#include "ability.h"

class Abil_invisible : public Ability 
{
	bool is_invi;
	int invisible;
public:
	Abil_invisible(int level_);
	virtual ~Abil_invisible();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	float GetConsum();
	float GetSpeed();

	virtual bool Action(Game_Manager* gm_, Player* player_);

	virtual bool isUsing(){return is_invi;};
	virtual bool Use(Game_Manager* gm_, Player* player_);
	virtual bool UnUse(Game_Manager* gm_, Player* player_);

	virtual float GetUseBullet(){return 0.5f;};
};

#endif // __ABIL_INVISIBLE_H__