//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_stealth.cpp
//
// ����: ���ϰ���(�ʰ� �߰�)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_stealth.h"
#include "player.h"

Abil_stealth::Abil_stealth(int level_):
Ability("���ϰ���", level_, 3, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_stealth::~Abil_stealth()
{

}


Ability* Abil_stealth::Clone(int level_)
{
	return new Abil_stealth(level_);
}


const char* Abil_stealth::GetInfor()
{
	switch(level)
	{
	case 1:
		return "������ �ƴϸ� ������ ��ٷ� ��Ű������";
	case 2:
		return "������ �ƴҶ� ������ �ݹ��� ��Ű���ʴ� �ð��� ����";
	case 3:
		return "������ �ƴҶ� ������ �ݹ��� ��Ű���ʴ� �ð��� ����";
	}
	return "���� ����";
}


int Abil_stealth::GetTime()
{
	switch(level)
	{
	case 1:
		return 400;
	case 2:
		return 150;
	case 3:
		return 90;
	}
	return false;
}




bool Abil_stealth::ActivePlayer(Player* player_)
{
	player_->SetWarningTime(GetTime());
	return true;
}

bool Abil_stealth::UnActivePlayer(Player* player_)
{
	player_->SetWarningTime(1000);
	return false;
}