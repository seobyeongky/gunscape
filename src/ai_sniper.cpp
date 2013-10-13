//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ai_sniper.h
//
// 내용: 추적자의 ai
//
//////////////////////////////////////////////////////////////////////////////////////////////////




#include "FSM.h"
#include "coord_def.h"
#include "gamemanager.h"
#include "rect.h"
#include "ai.h"
#include "ai_sniper.h"
#include "unit.h"
#include "random.h"
#include "monster.h"
#include "map.h"
#include <stack>
#include <d3dx9.h>


Ai_Sniper::Ai_Sniper(monster_state state_, Monster* unit_, Unit* head_ , int level_):
Ai_Manager(state_, unit_, head_, level_), explore(false), escape(false), esc_pos(), escape_ok(false)
{
}
Ai_Sniper::~Ai_Sniper()
{
}
void Ai_Sniper::Attack() //평상시의 움직임
{
	float angle_ = GetAngleToTarget(unit->GetPos(), target->GetPos());
	float dis_ = distan_coord(unit->GetPos(), target->GetPos());
	if(dis_<=50) //가까우면 플레이어의 스태미나를 채울수가 없음
	{
		target->SetStaminaDelay(100);
	}
	if(dis_<=150)
	{
		target->SetSpeedDelay(100);
	}

	int see_ = map->CollutionPosToPos(unit->GetPos(), target->GetPos()); //0이 안막혀있는거
	if(count%50 == 0){
		if(target->isPlayer()){
			if(!escape){
				if(unit->GetShotStop()){
					//샷을 쏘지않는다. 튄다.
					escape = true;
					escape_ok = true;
					while(distan_coord(target->GetPos(),(esc_pos = gm->GetRandomPos()))<200);
				}
			}
			else{
				if(!unit->GetShotStop()){
					escape = false;
					escape_ok = false;
				}
			}
		}
		else{
			escape = false;
			escape_ok = false;
		}

	}


	if(escape)
	{
		if(!Astar(esc_pos, targer_pos, angle_, 70))
			escape = false;

		//이동이 끝났을떄 새로 위치지정
		//if(!see_){
		//	angle_ = GetAngleToTarget(unit->GetPos(), target->GetPos());
		//}

	}
	else
	{
		escape = false;
		escape_ok = false;

		if(see_) //막혀있는 경우 플레이어의 위치를 찾아서 astar알고리즘을 이용한다.
		{
			search_time++;
			if(search_time > target->GetForgetCount()+500){
				StateChange(MSI_FORGET);
				search_time = 0;
				moving = false;
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
	}
	if(!see_)
		unit->SetAngle(GetAngleToTarget(unit->GetPos(), target->GetPos()));
	else
		unit->SetAngle(angle_);



	if(escape)
		approach = 1;		
	else if(see_ || unit->GetShotStop() || dis_>unit->GetMinimumDistans()+10.0f)
		approach = 1;
	else if(dis_<=unit->GetMinimumDistans())
		approach = -0.5f;
	else
		approach = 0;


	AttackMove(target, dis_, angle_, approach, see_);

}

void Ai_Sniper::Damage(coord_def c)
{
	if(state.GetState() != MS_ATTACK)
		unit->SetDelay(20.0f);
	StateChange(MSI_ATTACKED);
}
void Ai_Sniper::Noise(coord_def c)
{
	if(state.GetState() != MS_ATTACK)
		unit->SetDelay(20.0f);
	StateChange(MSI_NOISE);
}