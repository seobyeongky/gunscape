//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_fly_boss.h
//
// 내용: 몬스터 - 
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NAME_FLY_BOSS_H__
#define  __NAME_FLY_BOSS_H__


#include "monster.h"


class Named_fly_boss: public Monster
{
	int count;
public:
	Named_fly_boss(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Named_fly_boss();
	
	virtual bool isNamed(){return true;};

	virtual bool isCollution(){return false;};
	virtual bool isThrowable(){return false;};
	virtual bool isItemOk(){return false;}; 
	virtual bool isTrueShot(){return true;};

	virtual bool CanSpeeing(){return false;};	

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
};

#endif // __NAME_FLY_BOSS_H__