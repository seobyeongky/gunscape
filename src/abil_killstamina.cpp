//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_killstamina.cpp
//
// 내용: 
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_killstamina.h"
#include "player.h"
#include "gamemanager.h"

Abil_kill_stamina::Abil_kill_stamina(int level_):
Ability("사기증진", level_, 3, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_kill_stamina::~Abil_kill_stamina()
{

}


Ability* Abil_kill_stamina::Clone(int level_)
{
	return new Abil_kill_stamina(level_);
}


const char* Abil_kill_stamina::GetInfor()
{
	switch(level)
	{
	case 1:
		return "적을 죽일때마다 스태미나가 조금 회복";
	case 2:
		return "적을 죽일때마다 스태미나가 많이 회복하고 이속이 잠깐 증가";
	case 3:
		return "적을 죽일마다 스태미나가 전부 회복하고 이속이 잠깐 증가";
	}
	return "레벨 에러";
}

float Abil_kill_stamina::Getstamina()
{
	switch(level)
	{
	case 1:
		return 25.0f;
	case 2:
		return 60.0f;
	case 3:
		return 999.0f;
	}
	return false;
}

bool Abil_kill_stamina::KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_)
{
	player_->UpDownStamina(Getstamina());

	if(level>=2)
	{
		player_->SlowApply(1.6f,level==2?50:100,SK_KILL_STAMINA);
		player_->StateApply("사기증진",level==2?50:100);
	}
	return true;
}

