//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_rock.h
//
// 내용: 바위
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_ROCK_H__
#define  __SHOT_ROCK_H__

#include "shot_grenade.h"



class Shot_rock: public Shot_grenade
{
	int bunch;
	int const_time;
public:
	Shot_rock(Texture* texture_, Unit* unit_, int time_, float damage_, int bunch_, float power_, float max_power_, float range_, bool pentan_, int team_, coord_def pos_, coord_def target_);
	virtual ~Shot_rock();
	virtual char* GetName(){return "바위";};

	virtual bool Bomb(Game_Manager* gm_, float power_, float max_power_, float damage_, float range_, bool selfbomb_ = true, bool noise_ = true);

};

#endif // __SHOT_ROCK_H__
