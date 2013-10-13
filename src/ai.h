//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: ai.h
//
// ����: ������ �ΰ������� �����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __AI_H__
#define  __AI_H__

#include "FSM.h"
#include "coord_def.h"
#include "rect.h"
#include <stack>



class Unit;
class Monster;
class Game_Manager;
class Map;

class Ai_Manager
{
protected:
	FSMclass state;
	Monster* unit;
	Unit* head;
	Unit* target;//�� ���� �����Ͷ����� ����Ʈ���� ������ �����Ҷ� Ai�Ŵ����� ��� Ž���ؾ���.
	//�� ������������ ��¿��������

	bool moving; //�����̴� ��?
	int search_time; //���� ã�����ϰ� �Ѵ� �ð�. �� �ð��� ������� search���·� ���Ѵ�.
	coord_def targer_pos; //Ž���� ��ġ.
	coord_def temp_pos; //�̵��� �ӽ� ��ġ.

	int level;
	int count;
	FSMclass next_state;
	int delay;//�����ӵ�(���Ÿ� �齺���� ��������)
	float approach; //1�� �ٰ�����. -1�� �־�����. 0�� ������ �ִ�.
	float angle;//�����̴� ����
	float unit_angle; //������ ���� �ִ� ����(angle���� �ٸ���.)

	
	stack<coord_int> will_move;

	static Game_Manager* gm;
	static Map* map;
public:
	Ai_Manager(monster_state state_, Monster* unit_, Unit* head_ = NULL, int level_ = 0);
	
	void Action();
	bool Astar(coord_def goal, coord_def& result, float& angle_, int move_); //������ �ޱ��� �����Ѵ�.
	
	virtual void Attack();
	virtual void AttackMove(Unit* target_, float dis_, float angle_, float approach_, int see_);
	virtual void Search();
	virtual void Normal();
	virtual void Speed();



	bool TargetLost();
	bool TargetBilnding();
	bool InvisibleLost(coord_def c);
	bool SearchTarget();
	void SetTarget(Unit* target_);
	virtual void Damage(coord_def c); //�������� �޾��� ���(���ڴ� �������� ��ġ��.)
	virtual void Noise(coord_def c); //������ ����� ���(���ڴ� ������ ��ġ��.)

	static void SetMap(Map* map_){map = map_;};
	static void SetGameManager(Game_Manager* gm_){gm = gm_;};

	int GoPosition(coord_def start_, coord_def goal_, int range_); //��ġ�� �̵�

	void StateChange(monster_state_input input_);


	Unit* GetTarget(){return target;};
	monster_state GetState(){return state.GetState();};
};


#endif // __AI_H__