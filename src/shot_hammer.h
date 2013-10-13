//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_hammer.h
//
// 내용: 밀리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_HAMMER_H__
#define  __SHOT_HAMMER_H__

#include "Shot_melee.h"


class Shot_hammer: public Shot_melee
{

public:
	Shot_hammer(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, int time_, int team_, coord_def pos_, float angle_, float size_, float width_, float back_stab_);
	virtual ~Shot_hammer();



	virtual void Hit(Game_Manager* gm_, Unit* unit_);
};




#endif // __SHOT_HAMMER_H__
