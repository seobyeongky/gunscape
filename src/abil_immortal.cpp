//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_immortal.cpp
//
// 내용: 사용형 - 불사의분노
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_immortal.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_piece.h"

Abil_immortal::Abil_immortal(int level_):
Ability("불사신", level_,3, 100, 1, AT_USE),
immortal(false), count(0)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_immortal::~Abil_immortal()
{

}


Ability* Abil_immortal::Clone(int level_)
{
	return new Abil_immortal(level_);
}


const char* Abil_immortal::GetInfor()
{
	switch(level)
	{
	case 1:
		return "사용중에 체력이 1아래로 내려가지않음";
	case 2:
		return "사용중에 체력이 1아래로 내려가지않음";
	case 3:
		return "사용중에 체력이 1아래로 내려가지않음";
	}
	return "레벨 에러";
}
float Abil_immortal::GetConsum()
{
	switch(level)
	{
	case 1:
		return 1.0f;
	case 2:
		return 0.7f;
	case 3:
		return 0.4f;
	}
	return false;
}
bool Abil_immortal::Action(Game_Manager* gm_, Player* player_)
{
	if(immortal)
	{
		player_->SetStaminaDelay(100);
		if(count%2 == 0)
		{
			Effect_immortal(gm_, player_->GetPos(), 1, 0.5f);
		}
		count++;
		if(!player_->UseStamina(GetConsum()))
		{
			End(gm_, player_);
			return false;
		}
	}
	return true;
}
bool Abil_immortal::Use(Game_Manager* gm_, Player* player_)
{
	if(!immortal)
	{
		player_->SetImmortal(true);
		immortal = true;
		return true;
	}
	return false;
}
bool Abil_immortal::UnUse(Game_Manager* gm_, Player* player_)
{
	return false;
}


void Abil_immortal::End(Game_Manager* gm_, Player* player_)
{	
	if(immortal)
	{
		player_->SetImmortal(false);
		immortal = false;
	}
}