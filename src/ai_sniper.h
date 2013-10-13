//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ai_sniper.h
//
// 내용: 스나이퍼의 ai
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

	virtual void Damage(coord_def c); //데미지를 받았을 경우(인자는 공격자의 위치다.)
	virtual void Noise(coord_def c); //소음을 들었을 경우(인자는 소음의 위치다.)
};




#endif // __AI_SNIPER_H__