//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ai.cpp
//
// 내용: 유닛의 인공지능을 담당함
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "ai.h"
#include "unit.h"
#include "monster.h"
#include "gamemanager.h"
#include "main_weapon.h"
#include "profiler.h"
#include "random.h"
#include "map.h"
#include "Astar.h"
#include "effect_piece.h"
#include <math.h>

Game_Manager* Ai_Manager::gm = NULL;
Map* Ai_Manager::map = NULL;

Ai_Manager::Ai_Manager(monster_state state_, Monster* unit_, Unit* head_, int level_):
state(state_), unit(unit_), head(head_), target(NULL), moving(false), search_time(0), targer_pos(), temp_pos(), level(min(5,level_)), count(rand_int(0,3000)),
delay(0), approach(0), angle(rand_float(0,D3DX_PI*2)), unit_angle(angle)
{
	base_state_setup(state,MS_NORMAL);
	base_state_setup(next_state,MS_NORMAL);
}



void Ai_Manager::Action()
{
	ProfileBegin("Ai_Manager::Action()");
	if(delay)
	{
		delay--;
		if(!delay)
		{
			state.SetState(next_state.GetState());
			while(!will_move.empty())
				will_move.pop();
			moving = false;
		}
	}
	else
	{
		if(count % 5 == 0)
			SearchTarget();
	}

	switch(state.GetState())
	{
	case MS_ATTACK:
		if(target)
		{//공격 상태일때
			Attack();
		}
		else
		{
			if(!delay)
				StateChange(MSI_LOST);
		}
		break;
	case MS_SEARCH:
		{
			Search();
		}
		break;
	case MS_NORMAL:
		{
			Normal();
		}
		break;
	case MS_SLEEP:
		{
			Speed();
		}
		break;
	}

	count++;
	ProfileEnd("Ai_Manager::Action()");
}
bool Ai_Manager::Astar(coord_def goal, coord_def& result, float& angle_, int move_)
{
	if(will_move.empty()){//비어있는 경우 astar경로탐색
		if(GoPosition(unit->GetPos(), goal, move_) == -1)//targer_pos: 인자1. 목표위치
		{
			moving = false;//실패했을때 잠깐동안 방황모드도 중요?
			//StateChange(MSI_LOST);
			return false;
		}
	}

	if(!moving){ //움직이는 중이 아닐때 will_move에서 무빙을 빼온다.
		coord_int temp = will_move.top();
		coord_def result_(map->GetBigX(temp.x),map->GetBigY(temp.y));
		result = result_; //temp_pos: 인자2. 다음 위치
		moving = true;

		will_move.pop();
	}

	angle_ = GetAngleToTarget(unit->GetPos(), result);

	if(distan_coord(unit->GetPos(), result)<10)
		moving = false;
	return true;
}

void Ai_Manager::Attack() //평상시의 움직임
{
	float angle_ = GetAngleToTarget(unit->GetPos(), target->GetPos());
	float dis_ = distan_coord(unit->GetPos(), target->GetPos());
	if(dis_<=80) //가까우면 플레이어의 스태미나를 채울수가 없음
	{
		target->SetStaminaDelay(100);
	}
	if(dis_<=150)
	{
		target->SetSpeedDelay(100);
	}

	int see_ = map->CollutionPosToPos(unit->GetPos(), target->GetPos()); //0이 안막혀있는거

	if(see_ && unit->isCollution()) //막혀있는 경우 플레이어의 위치를 찾아서 astar알고리즘을 이용한다.
	{
		search_time++;
		if(search_time > target->GetForgetCount()){
			StateChange(MSI_FORGET);
			search_time = 0;
			targer_pos = target->GetPos();
			return;
		}

		if(!Astar(target->GetPos(), targer_pos, angle_, 70))
			moving = false;
	}
	else
	{
		search_time = 0;
		while(!will_move.empty())
			will_move.pop();
		moving = false;
	}
	
	if(!unit->GetTargetContinue())
		unit->SetAngle(angle_);
	else
		unit->SetAngle(GetAngleToTarget(unit->GetPos(), target->GetPos()));
	
	unit->SetMoveAngle(angle_);


		
	if(see_ || unit->GetShotStop() || dis_>unit->GetMinimumDistans()+10.0f)
		approach = 1;
	else if(dis_<=unit->GetMinimumDistans())
		approach = -0.5f;
	else
		approach = 0;

	AttackMove(target, dis_, angle_, approach, see_);

}
void Ai_Manager::AttackMove(Unit* target_, float dis_, float angle_, float approach_, int see_)
{
	if(!unit->GetDelay())
	{
		if(unit->isTrueShot() || unit->GetTargetContinue() || !see_)
		{
			float dis_ = distan_coord(unit->GetPos(), target_->GetPos());
			if(!unit->GetMainWeapon() || dis_ <= unit->GetMaximumDistans())
			{
				float angle_ = unit->GetAngle();
				coord_def target_pos_=  unit->GetPos()+ coord_def(cos(angle_)*dis_,sin(angle_)*dis_);

				if(unit->isTrueShot() && target)
					unit->Shot(gm, target->GetPos(), (5-level)*0.05f);
				else
					unit->Shot(gm, target_pos_, (5-level)*0.05f);
			}
		}
	}
	if(approach_)
	{
		unit->Approach(gm, target_->GetPos(), target_);
		int move_ = unit->UnitSlipMove(gm, unit->GetSpeed(unit->GetAngle())*approach_, angle_);
		if(move_ == 1)
		{
			if(!unit->GetDelay() && approach_>0) //근접공격
				unit->Melee(gm);
		}
		else if(move_ == -1)
		{
			moving = false;
			StateChange(MSI_LOST);
		}
	}
}

void Ai_Manager::Search()
{
	float angle_ = GetAngleToTarget(unit->GetPos(), targer_pos);
	float dis_ = distan_coord(unit->GetPos(), targer_pos);
	int see_ = map->CollutionPosToPos(unit->GetPos(), targer_pos); //0이 안막혀있는거
	search_time = 0;
	if(see_ && unit->isCollution()) //막혀있는 경우 플레이어의 위치를 찾아서 astar알고리즘을 이용한다.
	{

		if(!Astar(targer_pos, temp_pos, angle_, 100))
			moving = false;
			
	}
	else
	{
		while(!will_move.empty())
			will_move.pop();
		moving = false;
	}

	
	unit->SetAngle(angle_);
	unit->SetMoveAngle(angle_);
	unit->Approach(gm, targer_pos, NULL);
	int move_ = unit->UnitSlipMove(gm, unit->GetSpeed(unit->GetAngle()), angle_);
	if(move_ == -1 || (dis_ < 10 && (count % 10 == 0)))
	{
		moving = false;
		StateChange(MSI_LOST);
	}
}
void Ai_Manager::Normal() //평상시의 움직임
{
	search_time = 0;
	if(abs(unit_angle - angle)>0.05f)
	{
		float direc_ = sin(angle-unit_angle); //왼쪽으로 회전해야할지 오른쪽으로 회전해야할지

		if(direc_>0)
			unit_angle += 0.05f;
		else
			unit_angle += -0.05f;
	}
	else
		unit_angle = angle;
	float search_angle = unit_angle;

	unit->GetSearchAngle(search_angle);

	unit->SetAngle(search_angle);
	unit->SetMoveAngle(unit_angle);
	int move_ = unit->UnitMove(gm, unit->GetSpeed(unit->GetAngle())*0.3f, angle); 
	if(move_ != 0 || count%1500 == 0)
		angle = rand_float(0,D3DX_PI*2);
}
void Ai_Manager::Speed()
{

}
bool Ai_Manager::TargetLost()
{
	bool ok_ = false;
	if(head && !head->isLive())
	{
		head = NULL;
		ok_ = true;
	}
	if(target && !target->isLive())
	{
		target = NULL;
		ok_ = true;
		StateChange(MSI_LOST);
	}
	return ok_;
}
bool Ai_Manager::TargetBilnding()
{
	bool ok_ = false;
	if(state.GetState() != MS_SEARCH)
	{
		StateChange(MSI_BILND);
		if(target)
		{
			targer_pos = target->GetPos();
		}
		else if(state.GetState() != MS_ATTACK)
			targer_pos = unit->GetPos() + coord_def((float)rand_int(-50,50),(float)rand_int(-50,50));
		target = NULL;
		ok_ = true;
	}
	return ok_;
}
bool Ai_Manager::InvisibleLost(coord_def c)
{
	bool ok_ = false;
	float temp_distan_ = distan_coord(unit->GetPos(),c);
	if(!unit->CheckFlag(MF_TRUE_SIGHT) && map->CollutionPosToPos(unit->GetPos(), c,(int)temp_distan_))
	{
		targer_pos = c;
		StateChange(MSI_FORGET);
		ok_ = true;
	}
	return ok_;
}
bool Ai_Manager::SearchTarget()
{
	
	if(state.GetState() == MS_NORMAL && unit->GetHouseIn())
		return false;

	float distan_ = 99999;
	for(list<Unit*>::iterator it = gm->unit_list.begin();it != gm->unit_list.end();it++)
	{
		if((*it)->isLive() && !(*it)->isNonTarget() && unit->GetTeam() != (*it)->GetTeam() && (*it)->isTargeting())
		{
			float temp_distan_ = distan_coord(unit->GetPos(),(*it)->GetPos());
			float unit_sight_ = unit->GetView() * unit->GetSightPenalty((*it));
			if(GetState() == MS_SLEEP)
				unit_sight_ /= 3.0f;
			if(temp_distan_ > unit_sight_) //시야밖
				continue;

			if((*it)->isNonLife())
				temp_distan_ += 100.0f;

			if(temp_distan_ < distan_)
			{
				if(unit->CheckFlag(MF_TRUE_SIGHT) || !map->CollutionPosToPos(unit->GetPos(), (*it)->GetPos(),(int)temp_distan_)) //벽을 투시할경우 || 벽에 막히지 않았을경우.
				{
					if((*it)->GetInvisible())
					{
						if(GetState() == MS_SLEEP)
							continue;
						float angle_ = GetAngleToTarget(unit->GetPos(), (*it)->GetPos()) - unit->GetAngle();
						if(cos(angle_) < cos(unit->GetSightWidth()) || temp_distan_ > distan_/2){ //GetSightWidth가 시야의 폭(각도)이다. 나중에 몹마다 바꾸기
							continue;
						}
						else{
							if(unit->GetWarning()<=900 && GetState() != MS_SEARCH) //투명인 적이 있을때 감지도. MS_SEARCH상태에선 바로감지한다.
							{
								int value_ = (int)(300*unit->GetSearchRate());
								value_+=(int)((unit_sight_-temp_distan_)*900*unit->GetSearchRate()/unit_sight_);
								unit->UpDownWarning(value_);
								if(unit->GetWarning()<=900)
									continue;
							}
						}
					}
					else
					{	
						float angle_ = GetAngleToTarget(unit->GetPos(), (*it)->GetPos()) - unit->GetAngle();
						if(cos(angle_) < cos(unit->GetSightWidth())){
							if(unit->GetWarning()<=900)
							{
								unit->UpDownWarning((*it)->GetWarningTime());
								if(unit->GetWarning()<=900)
									continue;
							}
						}
					}
					distan_ = temp_distan_;
					target = (*it);
					if(state.GetState() != MS_ATTACK)
						unit->SetDelay(20.0f);
					StateChange(MSI_FOUND);
				}
			}
		}
	}
	return false;
}
void Ai_Manager::SetTarget(Unit* target_)
{	
	target = target_;
	if(state.GetState() != MS_ATTACK)
		unit->SetDelay(20.0f);
	StateChange(MSI_FOUND);
}
void Ai_Manager::Damage(coord_def c)
{
	if(state.GetState() != MS_ATTACK)
		unit->SetDelay(20.0f);
	StateChange(MSI_ATTACKED);
	targer_pos = c;
}
void Ai_Manager::Noise(coord_def c)
{
	if(unit->GetHouseIn())
		return;
	if(state.GetState() != MS_ATTACK)
	{
		unit->SetDelay(20.0f);	
		targer_pos = c;
	}
	StateChange(MSI_NOISE);
}



int Ai_Manager::GoPosition(coord_def start_, coord_def goal_, int range_)
{
	while(!will_move.empty())
		will_move.pop();
	coord_int start_temp(map->GetMiniX(start_.x),map->GetMiniY(start_.y));
	coord_int goal_temp(map->GetMiniX(goal_.x),map->GetMiniY(goal_.y));
	if(!PathSearch(start_temp, goal_temp, will_move, *(map->minimap), range_))
	{
		StateChange(MSI_LOST);
		return -1;
	}
	if(will_move.empty())
		return -1;
	return 0;
}
void Ai_Manager::StateChange(monster_state_input input_)
{
	monster_state temp = state.GetState();

	monster_state temp_ = next_state.StateReview(input_);
	//상태가 바뀌었을떄
	if(temp_ != state.GetState() && temp_ != next_state.GetState())
	{
		next_state.StateTransition(input_);
		delay = 5;
	}


}