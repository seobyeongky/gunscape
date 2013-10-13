//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: Shot_smoke_bomb.h
//
// ����: ����ź
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_SMOKE_BOME_H__
#define  __SHOT_SMOKE_BOME_H__

#include "shot_grenade.h"



class Shot_smoke_bomb: public Shot_grenade  
{
	int smoke_time;
public:
	Shot_smoke_bomb(Texture* texture_, Unit* unit_, int time_, int smoke_time_, float range_, int team_, coord_def pos_, coord_def target_);
	virtual ~Shot_smoke_bomb();
	virtual char* GetName(){return "����";};

	virtual bool Bomb(Game_Manager* gm_, float power_, float max_power_, float damage_, float range_, bool selfbomb_ = true, bool noise_ = true);
};

#endif // __SHOT_SMOKE_BOME_H__
