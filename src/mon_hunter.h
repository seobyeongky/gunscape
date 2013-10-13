//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_hunter.h
//
// 내용: 그물과 샷건을 쓰는 헌터
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_HUNTER_H__
#define  __MON_HUNTER_H__


#include "monster.h"


class Mon_hunter: public Monster
{
	bool net;
public:
	Mon_hunter(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_hunter();

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
};

#endif // __MON_HUNTER_H__