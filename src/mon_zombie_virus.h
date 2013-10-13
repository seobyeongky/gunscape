//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_zombie_virus.h
//
// 내용: 바이러스를 분포하는 놈임
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_ZOMBIE_VIRUS_H__
#define  __MON_ZOMBIE_VIRUS_H__


#include "monster.h"


class Mon_zombie_virus: public Monster
{
	int count;
public:
	Mon_zombie_virus(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_zombie_virus();

	virtual bool Special_Action(Game_Manager* gm_);
	virtual void Death(Game_Manager* gm_); 
};

#endif // __MON_ZOMBIE_VIRUS_H__