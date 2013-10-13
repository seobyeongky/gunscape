//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_post.cpp
//
// 내용: 사용형 - 말뚝박기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_post.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_piece.h"

Abil_post::Abil_post(int level_):
Ability("말뚝박기", level_,3, 100, 1, AT_USE),
post(false), count(0)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_post::~Abil_post()
{

}


Ability* Abil_post::Clone(int level_)
{
	return new Abil_post(level_);
}


const char* Abil_post::GetInfor()
{
	switch(level)
	{
	case 1:
		return "사용시 위치 고정후 공격속도 30%증가";
	case 2:
		return "사용시 위치 고정후 공격속도 45%증가";
	case 3:
		return "사용시 위치 고정후 공격속도 60%증가";
	case 4:
		return "사용시 위치 고정후 공격속도 75%증가";
	case 5:
		return "사용시 위치 고정후 공격속도 100%증가";
	}
	return "레벨 에러";
}
float Abil_post::GetSpeed()
{
	switch(level)
	{
	case 1:
		return 1.3f;
	case 2:
		return 1.45f;
	case 3:
		return 1.6f;
	case 4:
		return 1.75f;
	case 5:
		return 2.0f;
	}
	return false;
}
bool Abil_post::Action(Game_Manager* gm_, Player* player_)
{
	if(post)
	{
		player_->SetStaminaDelay(100);
		count++;
		if(!player_->UseStamina(0.5f))
		{
			UnUse(gm_, player_);
			return false;
		}
	}
	return true;
}
bool Abil_post::Use(Game_Manager* gm_, Player* player_)
{
	if(!post)
	{
		player_->SetFixed(true);
		player_->ApplyAtkSpd(GetSpeed());
		player_->SetDelay(20);
		post = true;
		return true;
	}
	return false;
}
bool Abil_post::UnUse(Game_Manager* gm_, Player* player_)
{
	if(post)
	{
		player_->SetFixed(false);
		player_->ApplyAtkSpd(1/GetSpeed());
		player_->SetDelay(60);
		post = false;
		return true;
	}
	return false;
}