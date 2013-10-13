//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: ai_fly_bug.h
//
// ����: ���ڸ��� ai
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __AI_FLY_BUG_H__
#define  __AI_FLY_BUG_H__


#include "FSM.h"
#include "ai.h"

class Monster;
class Unit;


class Ai_Fly_bug: public Ai_Manager
{

public:
	Ai_Fly_bug(monster_state state_, Monster* unit_, Unit* head_ = NULL, int level_ = 0);
	~Ai_Fly_bug();
	virtual void Search();
};




#endif // __AI_FLY_BUG_H__