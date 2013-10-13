//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_virus.h
//
// 내용: 바이러스를 흘리고 다니는 큰좀비
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NAMED_VIRUS_H__
#define  __NAMED_VIRUS_H__


#include "monster.h"


class Named_virus: public Monster
{
	int count;
public:
	Named_virus(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Named_virus();

	virtual bool Special_Action(Game_Manager* gm_);

	virtual bool isNamed(){return true;};
};

#endif // __NAMED_VIRUS_H__