//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: burrow2.h
//
// 내용: 맵이 너무 넓어서 ai매니저를 부하줄이기위해 멀면 정지
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __BURROW2_H__
#define  __BURROW2_H__

#include "unit.h"
#include "monster.h"



class Burrow2: public Unit
{
	bool sleep;
	Monster_Index mon;

public:
	Burrow2(coord_def pos_, int time_, Monster_Index mon_);
	virtual ~Burrow2();

	virtual bool Action_in(Game_Manager* gm_);
	virtual bool isPlayer(){return false;};
	virtual bool isNonLife(){return true;};
	virtual bool isThrowable(){return false;};
	virtual bool TargetLost(){return false;};
	virtual bool TargetBlinding(){return false;};
	virtual bool InvisibleLost(coord_def c){return false;};
	virtual void Sleep();

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0){return false;};
};


#endif // __BURROW2_H__