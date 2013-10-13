//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_missile.h
//
// 내용: 미사일
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_MISSIL_H__
#define  __SHOT_MISSIL_H__

#include "Shot_base.h"

class Unit;

class Shot_missile: public Shot_base
{
	float damage;
	float power;
	float max_power;
	float range;
	float distance;
	bool valid;
	float angle;
	const float const_speed;
	int guided_range;
	float guided_power;
	Unit* target;
	int count;
public:
	Shot_missile(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, float range_, int team_, coord_def pos_, float angle_, float speed_, int guided_range_, float guided_power_, float distance_);
	virtual ~Shot_missile();
	virtual char* GetName(){return "미사일";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);


	virtual bool TargetLost_in();
};

#endif // __SHOT_MISSIL_H__
