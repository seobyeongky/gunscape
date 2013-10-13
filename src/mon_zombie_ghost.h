//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: mon_zombie_ghost.h
//
// ����: ����� �������� �ݺ��ϴ� ����
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