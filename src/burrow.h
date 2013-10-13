//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: burrow.h
//
// 내용: 버로우 적
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __BURROW_H__
#define  __BURROW_H__

#include "unit.h"
#include "monster.h"
#include <vector>

using namespace std;


enum Brrow_Type
{
	BT_SMALL_ZOMBIE,
	BT_ZOMBIE_VIRUS,
	BT_ZOMBIE_VIRUS_SMALL,
	BT_MAX
};

class Burrow: public Unit
{
	int time;
	float range;
	bool react;
	vector<Monster_Index> mon_list;
	vector<coord_def> pos_list;

	void SetMonPos(Game_Manager* gm_);
	void CreateMonster(Brrow_Type type_);
public:
	Burrow(coord_def pos_, int time_, float range_, Brrow_Type type_);
	virtual ~Burrow();

	virtual bool Action_in(Game_Manager* gm_);
	virtual bool isPlayer(){return false;};
	virtual bool isThrowable(){return false;};
	virtual bool isNonLife(){return true;};
	virtual bool TargetLost(){return false;};
	virtual bool TargetBlinding(){return false;};
	virtual bool InvisibleLost(coord_def c){return false;};

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0){return false;};

	virtual bool CanSpeeing(){return false;};	
};


#endif // __BURROW_H__