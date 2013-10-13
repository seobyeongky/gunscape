//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: FSM.h
//
// 내용: fsm클래스 선언
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __FSM_H__
#define  __FSM_H__

#include <map>
#include <vector>
using namespace std;

enum monster_state
{
	MS_ERROR=0,
	MS_NORMAL,
	MS_SLEEP,
	MS_SEARCH,
	MS_ATTACK
};

enum monster_state_input
{
	MSI_ATTACKED,
	MSI_FOUND,
	MSI_NOISE,
	MSI_WAKE,
	MSI_BILND,
	MSI_FORGET,
	MSI_SLEEP,
	MSI_LOST
};

typedef struct state_trans_infor//상태전이 정보
{
	monster_state_input input; //받을 수 있는 입력의 갯수
	monster_state after; //입력에 대한 상태전이
	state_trans_infor(monster_state_input input_, monster_state after_)
	{
		input = input_;
		after = after_;
	}
}state_trans_infor;


class FSMstate //게임프로그래밍잼..
{
	unsigned char NumofTran; //일어날 수 있는 상태전이의 갯수

	vector<state_trans_infor> trans; //상태전이에 대한 정보
	monster_state id; //고유 ID

public:
	FSMstate(monster_state id_);

	monster_state GetId(){ return id;};
	void AddTransition(monster_state_input input_, monster_state after_); //상태전이 추가
	void DelTransition(monster_state_input input_); //상태전이 제거
	monster_state Transition(monster_state_input input_); //상태전이
};



class FSMclass //상태클래스를 포인터로 넘겨주지만 new한채로 넘기지말자. 클래스안에서 메모리해제를 하지않음.
{
	map<monster_state,FSMstate*> state_map; //상태를 담은 맵
	monster_state current_state;

public:
	FSMclass(monster_state current_state_ = MS_NORMAL);

	monster_state GetState(){return current_state;};
	void SetState(monster_state state_){current_state = state_;};

	void AddState(FSMstate* Newstate_); //상태추가
	void DeleteState(monster_state state_); //상태삭제

	monster_state StateTransition(monster_state_input input_); //상태전이
	monster_state StateReview(monster_state_input input_); //상태전이 미리보기 
};


extern FSMstate state_normal;

void init_state();


void base_state_setup(FSMclass& state, monster_state first_state);


#endif // __FSM_H__