//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_run.h
//
// 내용: 사용형 - 달리기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_RUN_H__
#define  __ABIL_RUN_H__

#include "ability.h"

class Abil_run : public Ability 
{
	int count;
	bool run;
public:
	Abil_run(int level_);
	virtual ~Abil_run();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	float GetSpeed();

	virtual bool Action(Game_Manager* gm_, Player* player_);

	virtual bool isUsing(){return run;};
	virtual bool Use(Game_Manager* gm_, Player* player_);
	virtual bool UnUse(Game_Manager* gm_, Player* player_);
};

#endif // __ABIL__H__