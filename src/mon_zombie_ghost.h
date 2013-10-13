//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_zombie_ghost.h
//
// 내용: 투명과 비투명을 반복하는 좀비
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_ZOMBIE_GHOST_H__
#define  __MON_ZOMBIE_GHOST_H__


#include "monster.h"


class Mon_zombie_ghost: public Monster
{
	int count;
	int cycle;
public:
	Mon_zombie_ghost(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_zombie_ghost();

	virtual bool Special_Action(Game_Manager* gm_);
};

#endif // __MON_ZOMBIE_GHOST_H__