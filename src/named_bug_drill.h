//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_bug_drill.h
//
// 내용: 몬스터 - 드릴벌레!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NAMED_BUG_DRILL_H__
#define  __NAMED_BUG_DRILL_H__


#include "monster.h"


class Named_bug_drill: public Monster
{
	float fly_speed;
	float fly_angle;

	int count;
	float accel;

	int drill_delay;

	int drill_count;
	coord_def driil_pos;
public:
	Named_bug_drill(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Named_bug_drill();
	
	virtual void SetAi(monster_state state_, Unit* head_ = NULL, int level_ = 0);

	virtual bool charDraw(Game_Manager* gm_, coord_def offset, float size_);

	virtual bool Action_in(Game_Manager* gm_);

	virtual int UnitMove(Game_Manager* gm_, float speed_, float angle_);
	virtual int UnitSlipMove(Game_Manager* gm_, float speed_, float angle_);

	virtual bool isCollution();
	virtual bool isThrowable(){return false;};
	virtual bool isNamed(){return true;};	
	virtual bool isItemOk(){return false;};
	virtual bool isViewName(){return (GetFly()>0);};

	virtual bool CanSpeeing(){return false;};	
	
	virtual bool isTrueShot(){return true;};
	virtual bool isNonTarget(){return true;};

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
	//virtual void Approach(Game_Manager* gm_, coord_def c, Unit* target_);
	virtual bool Melee(Game_Manager* gm_);
};

#endif // __NAMED_BUG_DRILL_H__