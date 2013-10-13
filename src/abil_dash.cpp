//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_dash.cpp
//
// 내용: 사용형 - 대쉬
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_dash.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_piece.h"

Abil_dash::Abil_dash(int level_):
Ability("대쉬", level_,3, 100, 1, AT_USE),
delay(0)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_dash::~Abil_dash()
{

}


Ability* Abil_dash::Clone(int level_)
{
	return new Abil_dash(level_);
}


const char* Abil_dash::GetInfor()
{
	switch(level)
	{
	case 1:
		return "짧은 순간 앞으로 대쉬";
	case 2:
		return "대쉬사용시 드는 스태미너 소모감소.";/* 적통과가능*/
	case 3:
		return "대쉬사용시 드는 스태미너 소모추가감소.";/* 대쉬중 방어력증가*/
	}
	return "레벨 에러";
}
float Abil_dash::GetSp()
{
	switch(level)
	{
	case 1:
		return 30.0f;
	case 2:
		return 25.0f;
	case 3:
		return 15.0f;
	}
	return false;
}
bool Abil_dash::Action(Game_Manager* gm_, Player* player_)
{
	if(delay)
		delay--;
	return true;
}


bool Abil_dash::Use(Game_Manager* gm_, Player* player_)
{
	if(!delay)
	{
		if(player_->UseStamina(GetSp()))
		{
			player_->SetStaminaDelay(100);
			//player_->SlowApply(1.5f, 100);
			player_->SetKnockback(5.0f, 5.0f, player_->GetAngle());
			delay = 30;
			return true;
		}
	}
	return false;
}