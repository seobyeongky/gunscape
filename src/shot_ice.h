//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: shot_ice.h
//
// ����: �ñ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_ICE_H__
#define  __SHOT_ICE_H__

#include <vector>
#include <d3dx9.h>
#include "shot_base.h"

using namespace std;

class Unit;

class Shot_ice: public Shot_base
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
	int slow_turn;
	float slow_ratio;

	vector<Unit*> hit_unit;
public:
	Shot_ice(Texture* texture_, Unit* unit_, float damage_, float fire_power_, int time_, int team_, coord_def pos_, float angle_, float speed_, int slow_turn_, float slow_ratio_, float size_inc_);
	virtual ~Shot_ice();
	virtual char* GetName(){return "�ñ�";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);

	virtual void Damage(Game_Manager* gm_, Unit* unit_);
};


#endif // __SHOT_ICE_H__
