//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ai_fly_bug.h
//
// 내용: 잠자리의 ai
//
//////////////////////////////////////////////////////////////////////////////////////////////////




#include "FSM.h"
#include "coord_def.h"
#include "gamemanager.h"
#include "rect.h"
#include "ai.h"
#include "ai_fly_bug.h"
#include "unit.h"
#include "random.h"
#include "monster.h"
#include "map.h"
#include <stack>
#include <d3dx9.h>


Ai_Fly_bug::Ai_Fly_bug(monster_state state_, Monster* unit_, Unit* head_ , int level_):
Ai_Manager(state_, unit_, head_, level_)
{
}
Ai_Fly_bug::~Ai_Fly_bug()
{
}


void Ai_Fly_bug::Search()
{
	float angle_ = GetAngleToTarget(unit->GetPos(), targer_pos);
	float dis_ = distan_coord(unit->GetPos(), targer_pos);
	int see_ = map->CollutionPosToPos(unit->GetPos(), targer_pos); //0이 안막혀있는거
	search_time = 0;


	unit->SetAngle(angle_);
	unit->Approach(gm, targer_pos, NULL);
	int move_ = unit->UnitSlipMove(gm, unit->GetSpeed(unit->GetAngle()), angle_);
	if(move_ == -1 || (dis_ < 10 && (count % 10 == 0)))
	{
		moving = false;
		StateChange(MSI_LOST);
	}
}
