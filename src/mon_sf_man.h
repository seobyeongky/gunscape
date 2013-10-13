//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_sf_man.h
//
// 내용: 특수부대
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_SF_MAN_H__
#define  __MON_SF_MAN_H__


#include "monster.h"


class Mon_sf_man: public Monster
{
	bool smoke;
public:
	Mon_sf_man(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_sf_man();

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
};

#endif // __MON_SF_MAN_H__