//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: burrow2.h
//
// ����: ���� �ʹ� �о ai�Ŵ����� �������̱����� �ָ� ����
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