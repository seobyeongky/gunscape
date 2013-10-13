//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: shot_normal.h
//
// ����: ��¥ �Ϲ� ź
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_NORMAL_H__
#define  __SHOT_NORMAL_H__

#include "shot_base.h"



class Shot_normal: public Shot_base
{
	float damage;
	float power;
	float max_power;
	float distance;
	bool valid;
	const float angle;
	const float const_speed;
	int count;
public:
	Shot_normal(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, int team_, coord_def pos_, float angle_, float speed_, float distance_);
	virtual ~Shot_normal();
	virtual char* GetName(){return "�븻";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
};

#endif // __SHOT_NORMAL_H__
