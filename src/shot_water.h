//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_water.h
//
// 내용: 물분사기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_WATER_H__
#define  __SHOT_WATER_H__

#include <vector>
#include <d3dx9.h>
#include "shot_fire.h"

using namespace std;

class Unit;

class Shot_water: public Shot_fire
{
	float power;
	float max_power;
public:
	Shot_water(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, int time_, int team_, coord_def pos_, float angle_, float speed_, float size_inc_);
	virtual ~Shot_water();
	
	virtual char* GetName(){return "물";};
	virtual void Damage(Game_Manager* gm_, Unit* unit_);
};


#endif // __SHOT_WATER_H__
