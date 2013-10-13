//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_scream.h
//
// 내용: 비명 네임드
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NAMED_SCREAM_H__
#define  __NAMED_SCREAM_H__


#include "monster.h"


class Named_Scream: public Monster
{
	int scream;
public:
	Named_Scream(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Named_Scream();

	virtual void Death(Game_Manager* gm_); 
	
	virtual bool Special_Action(Game_Manager* gm_);

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);

	virtual bool isNamed(){return true;};
};

#endif // __NAMED_SCREAM_H__