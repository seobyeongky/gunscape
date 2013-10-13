//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_virus_shot.h
//
// 내용: 미사일
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_VIRUS_SHOT_H__
#define  __SHOT_VIRUS_SHOT_H__

#include "Shot_base.h"



class Shot_virus_shot: public Shot_base
{
	float damage;
	float power;
	float max_power;
	float range;
	float distance;
	bool valid;
	const float angle;
	const float const_speed;
	int count;

	float virus_damage;
	int virus_frame;
	int virus_time;

public:
	Shot_virus_shot(Texture* texture_, Unit* unit_, float damage_, float power_, float max_power_, float range_, float virus_damage_, int virus_frame_, int virus_time_, int team_, coord_def pos_, float angle_, float speed_, float distance_);
	virtual ~Shot_virus_shot();
	virtual char* GetName(){return "바이러스탄";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);

	void Bomb_Virus(Game_Manager* gm_);
};

#endif // __Shot_VIRUS_SHOT_H__
