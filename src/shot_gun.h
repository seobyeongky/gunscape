//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_gun.h
//
// 내용: 작은 실탄형 총알
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_GUN_H__
#define  __SHOT_GUN_H__

#include "Shot_base.h"



class Shot_gun: public Shot_base
{
	float damage;
	float sniper;
	float power;
	float max_power;
	const int const_delay;
	float distance;
	int delay;
	coord_def delay_pos;
	bool valid;
	const float angle;
	const float const_speed;
	int slow_turn;
	float slow_ratio;
public:
	Shot_gun(Texture* texture_, Unit* unit_, float damage_, float sniper_, float power_, float max_power_, int team_, coord_def pos_, float angle_, float speed_, float distance_, int slow_turn_, float slow_ratio_, int delay_);
	virtual ~Shot_gun();
	virtual char* GetName(){return "총알";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
};

#endif // __SHOT_GUN_H__
