//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_fire.h
//
// 내용: 화염방사
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_FIRE_H__
#define  __SHOT_FIRE_H__

#include <list>
#include <d3dx9.h>
#include "shot_base.h"

using namespace std;

class Unit;

class Shot_fire: public Shot_base
{
protected:
	float damage;
	float fire_power;
	coord_def decel;
	int time;
	bool valid;
	const float angle;
	float size;
	const float size_inc;
	D3DCOLOR color;

	list<Unit*> hit_unit;
public:
	Shot_fire(Texture* texture_, Unit* unit_, float damage_, float fire_power_, int time_, int team_, coord_def pos_, float angle_, float speed_, float size_inc_);
	virtual ~Shot_fire();
	virtual char* GetName(){return "화염";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
	
	virtual bool TargetLost_in();

	virtual void Damage(Game_Manager* gm_, Unit* unit_);
};


#endif // __SHOT_FIRE_H__
