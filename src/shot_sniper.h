//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_sniper.h
//
// 내용: 스나이퍼 팡!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_SNIPER_H__
#define  __SHOT_SNIPER_H__

#include "Shot_base.h"


class Shot_sniper: public Shot_base
{
	float damage;
	float sniper;
	float power;
	float max_power;
	float distance;
	int count;
	int delay;
	coord_def start_pos;
	coord_def end_pos;
	const float angle;
public:
	Shot_sniper(Texture* texture_, Unit* unit_, float damage_, float sniper_, float power_, float max_power_, int team_, coord_def pos_, float angle__, float distance_, int delay_);
	virtual ~Shot_sniper();
	virtual char* GetName(){return "저격";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
};

#endif // __SHOT_SNIPER_H__
