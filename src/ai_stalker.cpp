//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: ai_stalker.h
//
// ����: �������� ai
//
//////////////////////////////////////////////////////////////////////////////////////////////////




#include "FSM.h"
#include "coord_def.h"
#include "gamemanager.h"
#include "rect.h"
#include "ai.h"
#include "ai_stalker.h"
#include "unit.h"
#include "random.h"
#include "monster.h"
#include "map.h"
#include <stack>
#include <d3dx9.h>


Ai_Stalker::Ai_Stalker(monster_state state_, Monster* unit_, Unit* head_ , int level_):
Ai_Manager(state_, unit_, head_, level_), explore(false), escape(false), esc_pos(), escape_ok(false), left(1), close(1)
{
}
Ai_Stalker::~Ai_Stalker()
{
}
void Ai_Stalker::Attack() //������ ������
{
	float angle_ = GetAngleToTarget(unit->GetPos(), target->GetPos());
	float dis_ = distan_coord(unit->GetPos(), target->GetPos());
	if(dis_<=50) //������ �÷��̾��� ���¹̳��� ä����� ����
	{
		target->SetStaminaDelay(100);
	}
	if(dis_<=150)
	{
		target->SetSpeedDelay(100);
	}

	int see_ = map->CollutionPosToPos(unit->GetPos(), target->GetPos()); //0�� �ȸ����ִ°�
	if(count%50 == 0){
		if(target->isPlayer()){
			if(!escape){
				if(!left){
					left += rand_int(-1,1);
				}
				else{
					if(rand_int(0,1)<1)
						left *= rand_int(-1,1);
					close = rand_int(0,10);
				}
				if(!isPlayerPinch()){
					//�÷��̾��� ������ �����Ѵ�.
					escape = true;
					escape_ok = true;
					while(distan_coord(target->GetPos(),(esc_pos = gm->GetRandomPos()))<200);
				}
			}
			else{
				if(isPlayerPinch()){
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


	if(escape/*isPlayerPinch()*/)//�÷��̾ �������������� ����ģ��.
	{
		if(!Astar(esc_pos, targer_pos, angle_, 70))
			escape = false;

		//�̵��� �������� ���� ��ġ����
		//if(!see_){
		//	angle_ = GetAngleToTarget(unit->GetPos(), target->GetPos());
		//}

	}
	else
	{
		escape = false;
		escape_ok = false;

		if(see_) //�����ִ� ��� �÷��̾��� ��ġ�� ã�Ƽ� astar�˰����� �̿��Ѵ�.
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
	else if(see_ || dis_>unit->GetMinimumDistans()+close*3)
	{
		angle_ += D3DX_PI/8.0f*left;
		approach = 1;
	}
	else if(dis_<=unit->GetMinimumDistans())
		approach = -1;
	else
	{
		approach = 1;
		angle_ += D3DX_PI/2.0f*left;
	}

	AttackMove(target, dis_, angle_, approach, see_);

}

void Ai_Stalker::Normal()
{
	search_time = 0;
	if(!explore)
	{
		targer_pos = gm->GetRandomPos();
		explore  = true;
	}
	float angle_ = GetAngleToTarget(unit->GetPos(), targer_pos);
	float dis_ = distan_coord(unit->GetPos(), targer_pos);
	int see_ = map->CollutionPosToPos(unit->GetPos(), targer_pos); //0�� �ȸ����ִ°�
	search_time = 0;
	if(see_) //�����ִ� ��� �÷��̾��� ��ġ�� ã�Ƽ� astar�˰����� �̿��Ѵ�.
	{

		if(!Astar(targer_pos, temp_pos, angle_, -1)){
			explore = false;
		}
	}
	else
	{
		while(!will_move.empty())
			will_move.pop();
		moving = false;
	}


	unit->SetAngle(angle_);
	unit->Approach(gm, targer_pos, NULL);
	int move_ = unit->UnitSlipMove(gm, unit->GetSpeed(unit->GetAngle()), angle_);
	if(move_ == -1 || (dis_ < 10 && (count % 10 == 0)))
	{
		explore = false;
	}
}
	

bool Ai_Stalker::isPlayerPinch()
{
	for(list<Unit*>::iterator it = gm->unit_list.begin();it != gm->unit_list.end(); it++)
	{
		if((*it) != unit){
			Ai_Manager* ai_ = (*it)->GetAi();
			if(ai_){
				if(ai_->GetState() == MS_ATTACK){
					if(ai_->GetTarget()->isPlayer())
						return true;
				}
			}
		}
	}
	return false;
}
void Ai_Stalker::Damage(coord_def c)
{
	if(state.GetState() != MS_ATTACK)
		unit->SetDelay(20.0f);
	StateChange(MSI_ATTACKED);
}
void Ai_Stalker::Noise(coord_def c)
{
	if(state.GetState() != MS_ATTACK)
		unit->SetDelay(20.0f);
	StateChange(MSI_NOISE);
}