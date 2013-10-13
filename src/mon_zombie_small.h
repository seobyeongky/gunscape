//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_zombie_small.h
//
// 내용: 작은좀비.(때려서 시야를 줄인다.)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_ZOMBIE_SMALL_H__
#define  __MON_ZOMBIE_SMALL_H__


#include "monster.h"


class Mon_zombie_small: public Monster
{
public:
	Mon_zombie_small(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_zombie_small();
	
	virtual void MeleeDamage(Game_Manager* gm_, Unit* target_);
};

#endif // __MON_ZOMBIE_SMALL_H__