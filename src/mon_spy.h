//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: mon_spy.h
//
// ����: �� ���� ���� ������!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_SPY_H__
#define  __MON_SPY_H__


#include "monster.h"


class Mon_spy: public Monster
{
	int count;//��� ����� ���̴� �ð�

public:
	Mon_spy(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_spy();

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
	virtual bool Special_Action(Game_Manager* gm_);
};

#endif // __MON_SPY_H__