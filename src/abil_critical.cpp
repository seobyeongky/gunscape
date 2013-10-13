//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_critical.cpp
//
// 내용: 능력-크리티컬
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_critical.h"
#include "player.h"

Abil_critical::Abil_critical(int level_):
Ability("치명타", level_, 5, 50, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}
Abil_critical::~Abil_critical()
{

}
Ability* Abil_critical::Clone(int level_)
{
	return new Abil_critical(level_);
}
int Abil_critical::GetCritical()
{
	switch(level)
	{
	case 1:
		return 15;
	case 2:
		return 25;
	case 3:
		return 35;
	case 4:
		return 50;
	case 5:
		return 65;
	}
	return false;
}

const char* Abil_critical::GetInfor()
{
	static char temp[64];
	sprintf_s(temp,64,"들킨 적에도 %d%% 확률로 백스텝, 헤드샷 가능",GetCritical());
	return temp;
}

bool Abil_critical::ActivePlayer(Player* player_)
{
	player_->UpDownCritical(GetCritical());
	return true;
}

bool Abil_critical::UnActivePlayer(Player* player_)
{
	player_->UpDownCritical(-GetCritical());
	return false;
}