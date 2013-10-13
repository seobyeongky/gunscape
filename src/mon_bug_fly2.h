//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_fly2.h
//
// 내용: 몬스터 - 비행충
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_BUG_FLY2_H__
#define  __MON_BUG_FLY2_H__


#include "monster.h"


class Mon_bug_fly2: public Monster
{
protected:
	float fly_speed;
	float fly_angle;

	int count;
	float accel;
public:
	Mon_bug_fly2(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_bug_fly2();
	
	virtual void SetAi(monster_state state_, Unit* head_ = NULL, int level_ = 0);

	virtual bool charDraw(Game_Manager* gm_, coord_def offset, float size_);

	virtual bool Action_in(Game_Manager* gm_);

	virtual int UnitMove(Game_Manager* gm_, float speed_, float angle_);
	virtual int UnitSlipMove(Game_Manager* gm_, float speed_, float angle_);

	virtual bool isCollution();
	virtual bool isThrowable(){return false;};
	virtual bool isItemOk(){return false;}; 

	virtual bool CanSpeeing(){return false;};	
};

#endif // __MON_BUG_FLY2_H__