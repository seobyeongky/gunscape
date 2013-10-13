//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_zombie_boomer.h
//
// 내용: 구토좀비
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_ZOMBIE_BOOMER_H__
#define  __MON_ZOMBIE_BOOMER_H__


#include "monster.h"


class Mon_zombie_boomer: public Monster
{
	bool virus;
	int count;
public:
	Mon_zombie_boomer(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_zombie_boomer();

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
};

#endif // __MON_ZOMBIE_BOOMER_H__