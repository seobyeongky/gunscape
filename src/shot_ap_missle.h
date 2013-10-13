//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_ap_missle.h
//
// 내용: 관통미사일
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_AP_MISSIL_H__
#define  __SHOT_AP_MISSIL_H__

#include "Shot_base.h"

#include <list>

using namespace std;


class Shot_ap_missile: public Shot_base
{
	float damage;
	float power;
	float max_power;
	float distance;
	bool valid;
	const float angle;
	const float const_speed;
	int count;

	list<Unit*> hit_unit;
public:
	Shot_ap_missile(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, int team_, coord_def pos_, float angle_, float speed_, float distance_);
	virtual ~Shot_ap_missile();

	virtual char* GetName(){return "박격포";};

	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);

	virtual bool TargetLost_in();

	virtual void Damage(Game_Manager* gm_, Unit* unit_, float power_, float max_power_);
};

#endif // __SHOT_MISSIL_H__
