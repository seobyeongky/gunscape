//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_trap.h
//
// 내용: 함정!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_TRAP_H__
#define  __SHOT_TRAP_H__

#include "Shot_base.h"



class Shot_trap: public Shot_base
{
	float slow_rate;
	int slow_time;
	int stop_time;
	int time;
	bool valid;
	float angle;
public:
	Shot_trap(Texture* texture_, Unit* unit_, float slow_rate_, int slow_time_, int stop_time_, int time_, int team_, coord_def pos_);
	virtual ~Shot_trap();
	virtual char* GetName(){return "함정";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
};

#endif // __SHOT_NET_H__
