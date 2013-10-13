//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: ai_stalker.h
//
// ����: �������� ai
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __AI_STALKER_H__
#define  __AI_STALKER_H__


#include "FSM.h"
#include "ai.h"

class Monster;
class Unit;


class Ai_Stalker: public Ai_Manager
{
	bool explore;
	bool escape;
	coord_def esc_pos;
	bool escape_ok;
	int left;
	int close;

public:
	Ai_Stalker(monster_state state_, Monster* unit_, Unit* head_ = NULL, int level_ = 0);
	~Ai_Stalker();
	virtual void Attack();
	//virtual void Search();
	virtual void Normal();

	bool isPlayerPinch();

	virtual void Damage(coord_def c); //�������� �޾��� ���(���ڴ� �������� ��ġ��.)
	virtual void Noise(coord_def c); //������ ����� ���(���ڴ� ������ ��ġ��.)
};




#endif // __AI_STALKER_H__