//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_health.cpp
//
// ����: ü�� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_health.h"
#include "player.h"

Abil_health::Abil_health(int level_):
Ability("����", level_, 5, 50, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_health::~Abil_health()
{

}


Ability* Abil_health::Clone(int level_)
{
	return new Abil_health(level_);
}


int Abil_health::GetHp()
{
	switch(level)
	{
	case 1:
		return 10;
	case 2:
		return 25;
	case 3:
		return 45;
	case 4:
		return 70;
	case 5:
		return 100;
	}
	return false;
}



const char* Abil_health::GetInfor()
{
	static char temp[32];
	sprintf_s(temp,32,"�ִ� ü�� %d����",GetHp());
	return temp;
}


bool Abil_health::ActivePlayer(Player* player_)
{
	player_->UpDownMaxHp(GetHp());
	player_->Heal(GetHp());
	return true;
}

bool Abil_health::UnActivePlayer(Player* player_)
{
	player_->UpDownMaxHp(-GetHp());
	player_->UpDownHp(-GetHp());
	return false;
}