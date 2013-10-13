//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_zombie_noise.h
//
// 내용: 죽을때 거대한 소리를 냄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_ZOMBIE_NOISE_H__
#define  __MON_ZOMBIE_NOISE_H__


#include "monster.h"


class Mon_zombie_noise: public Monster
{
	bool noise;
	int count;
public:
	Mon_zombie_noise(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_zombie_noise();

	virtual void Death(Game_Manager* gm_); 

	
};

#endif // __MON_ZOMBIE_NOISE_H__