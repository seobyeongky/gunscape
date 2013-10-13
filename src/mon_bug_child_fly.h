//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_child_fly.h
//
// 내용: 몬스터 - 비행충
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_BUG_CHILD_FLY_H__
#define  __MON_BUG_CHILD_FLY_H__


#include "mon_bug_fly2.h"


class Mon_bug_child_fly: public Mon_bug_fly2
{
	int return_time;
	
	Unit* target;
	Unit* head;
public:
	Mon_bug_child_fly(monster_infor& infor_, Unit* head_, Unit* target_, float x_, float y_, int team_, int return_time_, int time_ = 0);
	
	virtual void SetAi(monster_state state_, Unit* head_ = NULL, int level_ = 0);


	virtual bool Action_in(Game_Manager* gm_);

	
	virtual void SetFlyAngle(float angle_);

	virtual bool TargetLost();

};

#endif // __MON_BUG_CHILD_FLY_H__