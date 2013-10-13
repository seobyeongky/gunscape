//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_live.cpp
//
// 내용: 생존전문가
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_live.h"
#include "player.h"

Abil_live::Abil_live(int level_):
Ability("생존전문가", level_, 5, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_live::~Abil_live()
{

}


Ability* Abil_live::Clone(int level_)
{
	return new Abil_live(level_);
}


const char* Abil_live::GetInfor()
{
	switch(level)
	{
	case 1:
		return "다음 층으로 넘어갈때마다 체력을 10회복";
	case 2:
		return "다음 층으로 넘어갈때마다 체력을 15회복";
	case 3:
		return "다음 층으로 넘어갈때마다 체력을 20회복";
	case 4:
		return "다음 층으로 넘어갈때마다 체력을 25회복";
	case 5:
		return "다음 층으로 넘어갈때마다 체력을 30회복";
	}
	return "레벨 에러";
}

bool Abil_live::EnterMap(Game_Manager* gm_, Player* player_, int level_)
{
	player_->Heal(level*5+5);
	return true;
}
