//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_berserker.h
//
// 내용: 그물과 샷건을 쓰는 헌터
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NAMED_BERSERKER_H__
#define  __NAMED_BERSERKER_H__


#include "monster.h"


class Named_Berserker: public Monster
{
	int berserker;
	int delay;
	int count;
public:
	Named_Berserker(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Named_Berserker();
	
	virtual bool Special_Action(Game_Manager* gm_);

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
		
	virtual bool isNamed(){return true;};	
};

#endif // __NAMED_BERSERKER_H__