//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: ai_sniper.h
//
// ����: ���������� ai
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __AI_SNIPER_H__
#define  __AI_SNIPER_H__


#include "FSM.h"
#include "ai.h"

class Monster;
class Unit;


class Ai_Sniper: public Ai_Manager
{
	bool explore;
	bool escape;
	coord_def esc_pos;
	bool escape_ok;

public:
	Ai_Sniper(monster_state state_, Monster* unit_, Unit* head_ = NULL, int level_ = 0);
	~Ai_Sniper();
	virtual void Attack();

	virtual void Damage(coord_def c); //�������� �޾��� ���(���ڴ� �������� ��ġ��.)
	virtual void Noise(coord_def c); //������ ����� ���(���ڴ� ������ ��ġ��.)
};




#endif // __AI_SNIPER_H__