//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_refle_fire.h
//
// 내용: 튕기는 화염
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_REFLE_FIRE_H__
#define  __SHOT_REFLE_FIRE_H__

#include <list>
#include <d3dx9.h>
#include "shot_base.h"

using namespace std;

class Unit;

class Shot_refle_fire: public Shot_base
{
protected:
	float damage;
	int fire_time;
	float fire_damage;
	coord_def decel;
	int time;
	bool valid;
	float speed_absol;
	float angle;

	int bounce;

	int count;

	list<Unit*> hit_unit;
public:
	Shot_refle_fire(Texture* texture_, Unit* unit_, float damage_, int fire_time_, float fire_damage_, int time_, int team_, coord_def pos_, float angle_, float speed_, int bounce_);
	virtual ~Shot_refle_fire();
	virtual char* GetName(){return "반사화염";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);

	virtual void Damage(Game_Manager* gm_, Unit* unit_);

	virtual bool TargetLost_in();
};


#endif // __SHOT_REFLE_FIRE_H__
