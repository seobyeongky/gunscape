//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_repress.cpp
//
// 내용: 초기진압
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_repress.h"
#include "player.h"

Abil_repress::Abil_repress(int level_):
Ability("초기진압", level_, 5, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_repress::~Abil_repress()
{

}


Ability* Abil_repress::Clone(int level_)
{
	return new Abil_repress(level_);
}


const char* Abil_repress::GetInfor()
{
	switch(level)
	{
	case 1:
		return "다음 층으로 넘어갈때마다 20초간 공격력 20% 증가";
	case 2:
		return "다음 층으로 넘어갈때마다 20초간 공격력 35% 증가";
	case 3:
		return "다음 층으로 넘어갈때마다 20초간 공격력 50% 증가";
	case 4:
		return "다음 층으로 넘어갈때마다 20초간 공격력 70% 증가";
	case 5:
		return "다음 층으로 넘어갈때마다 20초간 공격력 100% 증가";
	}
	return "레벨 에러";
}
float Abil_repress::Getattack()
{
	switch(level)
	{
	case 1:
		return 1.20f;
	case 2:
		return 1.35f;
	case 3:
		return 1.5f;
	case 4:
		return 1.7f;
	case 5:
		return 2.0f;
	}
	return false;
}

bool Abil_repress::EnterMap(Game_Manager* gm_, Player* player_, int level_)
{	
	player_->AttackApply(Getattack(),1200,ABK_PORTAL);
	player_->StateApply("초기진압",1200);
	return true;
}
