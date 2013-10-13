//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: FSM.cpp
//
// 내용: fsm클래스 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "FSM.h"

FSMstate::FSMstate(monster_state id_):
NumofTran(0), id(id_)
{
	trans.reserve(32);
}

void FSMstate::AddTransition(monster_state_input input_, monster_state after_)
{
	trans.push_back(state_trans_infor(input_,after_));
	NumofTran++;
}
void FSMstate::DelTransition(monster_state_input input_)
{
	vector<state_trans_infor>::iterator it;
	for(it = trans.begin(); it!=trans.end() ; it++)
	{
		if((*it).input == input_)
		{
			trans.erase(it);
			return;
		}
	}
}

monster_state FSMstate::Transition(monster_state_input input_)
{
	vector<state_trans_infor>::iterator it;
	for(it = trans.begin(); it!=trans.end() ; it++)
	{
		if((*it).input == input_)
		{ 
			return (*it).after;
		}
	}
	return id;
}

FSMclass::FSMclass(monster_state current_state_):
current_state(current_state_)
{
}

void FSMclass::AddState(FSMstate* Newstate_)
{
	map<monster_state,FSMstate*>::iterator it;

	if(!state_map.empty()) //이미 존재하는 상태인경우
	{
		it = state_map.find(Newstate_->GetId());
		if(it != state_map.end())
			return;
	}

	state_map.insert(pair<monster_state,FSMstate*>(Newstate_->GetId(),Newstate_));
}

void FSMclass::DeleteState(monster_state state_)
{
	map<monster_state,FSMstate*>::iterator it;

	if(!state_map.empty()) //존재하는 경우
	{
		it = state_map.find(state_);
		if(it != state_map.end())
		{
			state_map.erase(it);
		}
	}
}


monster_state FSMclass::StateTransition(monster_state_input input_)
{	
	if(!current_state)
		return MS_ERROR;


	map<monster_state,FSMstate*>::iterator it;

	if(!state_map.empty()) //존재하는 경우
	{
		it = state_map.find(current_state);
		if(it != state_map.end())
		{
			FSMstate *pState = (FSMstate*)((*it).second);
			current_state = pState->Transition(input_);
			return current_state;
		}
	}
	return MS_ERROR;
}
monster_state FSMclass::StateReview(monster_state_input input_)
{
	if(!current_state)
		return MS_ERROR;


	map<monster_state,FSMstate*>::iterator it;

	if(!state_map.empty()) //존재하는 경우
	{
		it = state_map.find(current_state);
		if(it != state_map.end())
		{
			FSMstate *pState = (FSMstate*)((*it).second);
			return pState->Transition(input_);
		}
		else
			return GetState();
	}
	return MS_ERROR;



}



//아래부터 상태
FSMstate state_normal(MS_NORMAL);
FSMstate state_sleep(MS_SLEEP);
FSMstate state_search(MS_SEARCH);
FSMstate state_atack(MS_ATTACK);


void init_state()
{
	//상태 노말: 적을 발견하지않고 떠도는 상태
	state_normal.AddTransition(MSI_FOUND,MS_ATTACK);
	state_normal.AddTransition(MSI_ATTACKED,MS_SEARCH);
	state_normal.AddTransition(MSI_NOISE,MS_SEARCH);
	state_normal.AddTransition(MSI_BILND,MS_SEARCH);
	state_normal.AddTransition(MSI_SLEEP,MS_SLEEP);

	//상태 수면: 한 자리에서 자는 상태
	state_sleep.AddTransition(MSI_NOISE,MS_SEARCH);
	state_sleep.AddTransition(MSI_ATTACKED,MS_SEARCH);
	state_sleep.AddTransition(MSI_FOUND,MS_ATTACK);
	state_sleep.AddTransition(MSI_WAKE,MS_NORMAL);
	state_sleep.AddTransition(MSI_BILND,MS_SEARCH);

	//상태 탐색: 낌새를 눈치채고 적을 찾는다.
	state_search.AddTransition(MSI_FOUND,MS_ATTACK);
	state_search.AddTransition(MSI_LOST,MS_NORMAL);
	state_atack.AddTransition(MSI_LOST,MS_SEARCH);

	//상태 공격: 목표를 잡음
	state_atack.AddTransition(MSI_LOST,MS_NORMAL);
	state_atack.AddTransition(MSI_BILND,MS_SEARCH);
	state_atack.AddTransition(MSI_FORGET,MS_SEARCH);
	
}

void base_state_setup(FSMclass& state, monster_state first_state)
{
	state.AddState(&state_normal);
	state.AddState(&state_sleep);
	state.AddState(&state_search);
	state.AddState(&state_atack);

	state.SetState(first_state);
}