//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_melee.h
//
// 내용: 밀리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_MELEE_H__
#define  __SHOT_MELEE_H__

#include <list>
#include <d3dx9.h>
#include "Shot_base.h"

using namespace std;

class Unit;

class Shot_melee: public Shot_base
{
protected:
	float damage;
	float power;
	float max_power;
	int time;
	const int const_time;
	bool valid;
	const float angle;
	float size;
	float width;
	int alpha;
	bool ok_backstab;

	float back_stab;

	list<Unit*> hit_unit;
public:
	Shot_melee(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, int time_, int team_, coord_def pos_, float angle_, float size_, float width_, float back_stab_);
	virtual ~Shot_melee();
	virtual char* GetName(){return "근접";};
	virtual bool Action(Game_Manager* gm_);
	virtual void Hit(Game_Manager* gm_, Unit* unit_);
	virtual bool Draw(coord_def offset_, float size_);

	virtual bool TargetLost_in();
};




#endif // __SHOT_MELEE_H__
