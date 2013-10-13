//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_poison.h
//
// 내용: 독침. 엣홈님보고잇나?
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_POISON_H__
#define  __SHOT_POISON_H__

#include "Shot_base.h"



class Shot_poison: public Shot_base
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
	Shot_poison(Texture* texture_, Unit* unit_, float damage_, float sniper_, float power_, float max_power_, int team_, coord_def pos_, float angle_, float speed_, float distance_, int slow_turn_, float slow_ratio_, int delay_);
	virtual ~Shot_poison();
	virtual char* GetName(){return "독침";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
};

#endif // __SHOT_POISON_H__
