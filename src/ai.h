//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ai.h
//
// 내용: 유닛의 인공지능을 담당함
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
	Unit* target;//이 유닛 포인터때문에 리스트에서 유닛을 제거할때 Ai매니져를 모두 탐색해야함.
	//좀 귀찮아지지만 어쩔수가업음

	bool moving; //움직이는 중?
	int search_time; //적을 찾지못하고 쫓는 시간. 이 시간이 길어지면 search상태로 변한다.
	coord_def targer_pos; //탐색할 위치.
	coord_def temp_pos; //이동할 임시 위치.

	int level;
	int count;
	FSMclass next_state;
	int delay;//반응속도(원거리 백스탭을 쓰기위해)
	float approach; //1은 다가가다. -1은 멀어지다. 0은 가만히 있다.
	float angle;//움직이는 방향
	float unit_angle; //유닛이 보고 있는 방향(angle과는 다르다.)

	
	stack<coord_int> will_move;

	static Game_Manager* gm;
	static Map* map;
public:
	Ai_Manager(monster_state state_, Monster* unit_, Unit* head_ = NULL, int level_ = 0);
	
	void Action();
	bool Astar(coord_def goal, coord_def& result, float& angle_, int move_); //리턴은 앵글을 리턴한다.
	
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
	virtual void Damage(coord_def c); //데미지를 받았을 경우(인자는 공격자의 위치다.)
	virtual void Noise(coord_def c); //소음을 들었을 경우(인자는 소음의 위치다.)

	static void SetMap(Map* map_){map = map_;};
	static void SetGameManager(Game_Manager* gm_){gm = gm_;};

	int GoPosition(coord_def start_, coord_def goal_, int range_); //위치로 이동

	void StateChange(monster_state_input input_);


	Unit* GetTarget(){return target;};
	monster_state GetState(){return state.GetState();};
};


#endif // __AI_H__