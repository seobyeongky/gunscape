//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_grenade.h
//
// 내용: 수류탄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_GRENADE_H__
#define  __SHOT_GRENADE_H__

#include "Shot_base.h"



class Shot_grenade: public Shot_base
{
protected:
	float damage;
	float power;
	float max_power;
	float range;
	coord_def decel;
	int time;
	const int const_time;
	float angle;
	int angle_inc;
	bool valid;
	float size;
	bool pentan;
public:
	Shot_grenade(Texture* texture_, Unit* unit_, int time_, float damage_, float power_, float max_power_, float range_, bool pentan_, int team_, coord_def pos_, coord_def target_);
	virtual ~Shot_grenade();
	virtual char* GetName(){return "수류탄";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
	
	virtual bool GrenadeMove(Game_Manager* gm_);
};

#endif // __SHOT_GRENADE_H__
