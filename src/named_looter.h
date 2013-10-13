//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_looter.h
//
// 내용: 쪼렙 좀비네임드 약탈자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NAME_LOOTER_H__
#define  __NAME_LOOTER_H__


#include "monster.h"


class Named_looter: public Monster
{
public:
	Named_looter(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Named_looter();

	virtual bool isNamed(){return true;};	
};

#endif // __NAME_JACK_H__