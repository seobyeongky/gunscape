//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_vaccine.cpp
//
// 내용: 바이러스 면역
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_vaccine.h"
#include "player.h"
#include "main_weapon.h"

Abil_vaccine::Abil_vaccine(int level_):
Ability("항체", level_, 2, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_vaccine::~Abil_vaccine()
{

}


Ability* Abil_vaccine::Clone(int level_)
{
	return new Abil_vaccine(level_);
}

const char* Abil_vaccine::GetInfor()
{
	switch(level)
	{
	case 1:
		return "바이러스 방어력 50%증가";
	case 2:
		return "바이러스에 면역";
	}
	return "레벨 에러";
}


bool Abil_vaccine::ActivePlayer(Player* player_)
{
	if(level == 1)
		player_->ApplyDefense(DT_VIRUS, 0.5f);
	else
		player_->SetDefResist(DT_VIRUS, true);
	return true;
}

bool Abil_vaccine::UnActivePlayer(Player* player_)
{
	if(level == 1)
		player_->ApplyDefense(DT_VIRUS, 2.0f);
	else
		player_->SetDefResist(DT_VIRUS, false);
	return false;
}