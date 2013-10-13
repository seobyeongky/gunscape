//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shot_bug.h
//
// 내용: 벌레 몸통!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_BUG_H__
#define  __SHOT_BUG_H__

#include <list>
#include <d3dx9.h>
#include "unit.h"

using namespace std;

class Shot_bug: public Unit
{	
	float damage;
	bool valid;
	Unit* head;	
	float angle;
	bool ishead;
	
	coord_def fly_speed;
	coord_def fly_acc;
	int fly_time;
	int fly;

	int delay;
	
	list<Unit*> hit_unit;
public:
	Shot_bug(Texture* texture_, Unit* unit_, float damage_, coord_def start_, coord_def goal_, int time_, int team_, int delay_);
	virtual ~Shot_bug();
	virtual bool Action(Game_Manager* gm_);
	virtual bool Action_in(Game_Manager* gm_){return false;};

	void Damage(Game_Manager* gm_, Unit* unit_);

	virtual bool Draw(Game_Manager* gm_, coord_def offset_, float size_);


	virtual bool isCollution(){return false;};
	virtual bool isThrowable(){return false;};
	virtual bool CanSpeeing(){return false;};
	virtual bool isPlayer(){return false;};
	virtual bool isNonTarget(){return (delay>0);};
	
	virtual bool TargetLost();
	virtual bool TargetBlinding(){return false;};
	virtual bool InvisibleLost(coord_def c){return false;};

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0){return false;};
	
	virtual int SetDamage(Game_Manager* gm_, coord_def c, Damage_Type type_, float damage_, int team_, float sniper_ = 1.0f, int critical_ = 0);
	virtual void SetPoison(float damage_, int turn_, Unit* unit_);
	//virtual void Damage(Game_Manager* gm_, Unit* unit_);
};

#endif // __SHOT_BUG_H__
