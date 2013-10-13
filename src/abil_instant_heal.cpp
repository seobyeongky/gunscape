//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_instant_heal.cpp
//
// 내용: 능력-인스턴스-즉시회복
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_instant_heal.h"
#include "player.h"

Abil_Instant_heal::Abil_Instant_heal(int level_):
Ability("즉시회복", level_, 1, 30, 1, AT_INSTANCE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_Instant_heal::~Abil_Instant_heal()
{

}


Ability* Abil_Instant_heal::Clone(int level_)
{
	return new Abil_Instant_heal(level_);
}


const char* Abil_Instant_heal::GetInfor()
{
	switch(level)
	{
	case 1:
		return "배우는 즉시 체력을 100 회복";
	}
	return "레벨 에러";
}

bool Abil_Instant_heal::InstanceActive(Player* player_)
{	
	player_->Heal(100);
	return true;
}