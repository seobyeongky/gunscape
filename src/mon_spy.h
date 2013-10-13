//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_spy.h
//
// 내용: 디스 몬스터 이즈 스파이!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_SPY_H__
#define  __MON_SPY_H__


#include "monster.h"


class Mon_spy: public Monster
{
	int count;//잠시 모습이 보이는 시간

public:
	Mon_spy(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_spy();

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
	virtual bool Special_Action(Game_Manager* gm_);
};

#endif // __MON_SPY_H__