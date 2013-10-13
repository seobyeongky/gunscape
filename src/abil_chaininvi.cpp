//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_chaininvi.cpp
//
// 내용: 연쇄암습
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_chaininvi.h"
#include "player.h"
#include "gamemanager.h"
#include "effect_piece.h"

Abil_chaininvi::Abil_chaininvi(int level_):
Ability("연쇄암습", level_, 3, 50, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_chaininvi::~Abil_chaininvi()
{

}


Ability* Abil_chaininvi::Clone(int level_)
{
	return new Abil_chaininvi(level_);
}


const char* Abil_chaininvi::GetInfor()
{
	switch(level)
	{
	case 1:
		return "적을 죽이면 3초간 은신";
	case 2:
		return "적을 죽이면 5초간 은신";
	case 3:
		return "적을 죽이면 7초간 은신";
	}
	return "레벨 에러";
}

int Abil_chaininvi::Getsecond()
{
	switch(level)
	{
	case 1:
		return 180;
	case 2:
		return 300;
	case 3:
		return 420;
	}
	return false;
}

bool Abil_chaininvi::KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_)
{
	gm_->InvisibleLost(player_->GetPos());		
	Effect_invisible(gm_, player_->GetPos(), 5,  1.0f, 0.5f);
	player_->SetInvisibleturn(Getsecond());
	player_->StateApply("연쇄암습",Getsecond());

	return true;
}

