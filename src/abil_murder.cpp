//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_murder.cpp
//
// 내용: 능력-청부살인
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_murder.h"
#include "player.h"
#include "monster.h"
#include "random.h"

Abil_murder::Abil_murder(int level_):
Ability("청부살인", level_, 5, 50, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_murder::~Abil_murder()
{

}


Ability* Abil_murder::Clone(int level_)
{
	return new Abil_murder(level_);
}


const char* Abil_murder::GetInfor()
{
	switch(level)
	{
	case 1:
		return "인간을 죽일때마다 체력 1회복";
	case 2:
		return "인간을 죽일때마다 최대 체력 1증가";
	case 3:
		return "인간을 죽일때마다 최대 체력 1~2증가";
	case 4:
		return "인간을 죽일때마다 최대 체력 2증가";
	case 5:
		return "인간을 죽일때마다 최대 체력 3증가";
	}
	return "레벨 에러";
}

int Abil_murder::GetHp()
{
	switch(level)
	{
	case 1:
		return 0;
	case 2:
		return 1;
	case 3:
		return rand_int(1,2);
	case 4:
		return 2;
	case 5:
		return 3;
	}
	return false;
}

bool Abil_murder::KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_)
{
	if(monster_->GetKind() == VT_HUMAN)
	{
		if(level>=2)
		{
			int hp_ = GetHp();
			player_->UpDownMaxHp(hp_);
			player_->Heal(hp_);
		}
		else
			player_->Heal(1);
	}

	return true;
}

