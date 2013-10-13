//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_big_zombie.h
//
// 내용: 바위좀비
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_BIG_ZOMBIE_H__
#define  __MON_BIG_ZOMBIE_H__


#include "monster.h"


class Mon_big_zombie: public Monster
{
	bool throws;
	int count;
	int throw_count;
	int frame;
public:
	Mon_big_zombie(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_big_zombie();

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
	
	virtual bool Special_Action(Game_Manager* gm_);

	virtual bool Throw(Game_Manager* gm_, coord_def c);

	virtual void Approach(Game_Manager* gm_, coord_def c, Unit* target_);


	virtual bool isThrowable(){return false;};
};

#endif // __MON_ZOMBIE_BOOMER_H__