//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: mon_bug_fly.h
//
// ����: ���� - �޶ѱ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_BUG_FLY_H__
#define  __MON_BUG_FLY_H__


#include "monster.h"


class Mon_bug_fly: public Monster
{
	int fly_delay;
public:
	Mon_bug_fly(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_bug_fly();

	virtual bool Special_Action(Game_Manager* gm_);

	virtual void Approach(Game_Manager* gm_, coord_def c, Unit* target_);
};

#endif // __MON_BUG_FLY_H__