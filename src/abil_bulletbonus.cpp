//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_bulletbonus.cpp
//
// 내용: 탄창얻기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_bulletbonus.h"
#include "player.h"

Abil_bulletbonus::Abil_bulletbonus(int level_):
Ability("물자보충", level_, 3, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_bulletbonus::~Abil_bulletbonus()
{

}


Ability* Abil_bulletbonus::Clone(int level_)
{
	return new Abil_bulletbonus(level_);
}


const char* Abil_bulletbonus::GetInfor()
{
	switch(level)
	{
	case 1:
		return "다음 층으로 넘어갈때마다 탄창 1개를 얻음";
	case 2:
		return "다음 층으로 넘어갈때마다 탄창 2개를 얻음";
	case 3:
		return "다음 층으로 넘어갈때마다 탄창 3개를 얻음";
	}
	return "레벨 에러";
}
bool Abil_bulletbonus::EnterMap(Game_Manager* gm_, Player* player_, int level_)
{
	player_->SuppleBullet((float)level);
	return true;
}
