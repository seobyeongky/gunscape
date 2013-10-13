//////////////////////////////////////////////////////////////////////////////////////////////////
//
// ÆÄÀÏÀÌ¸§: shot_bomb.h
//
// ³»¿ë: Æø¹ß!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_BOMB_H__
#define  __SHOT_BOMB_H__

#include "Shot_base.h"



class Shot_bomb: public Shot_base
{
protected:
	float damage;
	float power;
	float max_power;
	float range;
public:
	Shot_bomb(Unit* unit_, coord_def pos_, float damage_, float power_, float max_power_, float range_, int team_);
	virtual ~Shot_bomb();
	virtual char* GetName(){return "ÆøÅº";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
};

#endif // __SHOT_BOMB_H__
