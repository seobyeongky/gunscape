//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_dex.cpp
//
// ����: �ӵ� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_dex.h"
#include "player.h"

Abil_dex::Abil_dex(int level_):
Ability("������", level_, 5, 30, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_dex::~Abil_dex()
{

}


Ability* Abil_dex::Clone(int level_)
{
	return new Abil_dex(level_);
}


const char* Abil_dex::GetInfor()
{
	switch(level)
	{
	case 1:
		return "�̵��ӵ� 10% ����";
	case 2:
		return "�̵��ӵ� 20% ����";
	case 3:
		return "�̵��ӵ� 35% ����";
	case 4:
		return "�̵��ӵ� 50% ����";
	case 5:
		return "�̵��ӵ� 70% ����";
	}
	return "���� ����";
}

float Abil_dex::GetSpeed()
{
	switch(level)
	{
	case 1:
		return 1.1f;
	case 2:
		return 1.2f;
	case 3:
		return 1.35f;
	case 4:
		return 1.5f;
	case 5:
		return 1.7f;
	}
	return false;
}


bool Abil_dex::ActivePlayer(Player* player_)
{
	player_->ApplySpeed(GetSpeed());
	return true;
}

bool Abil_dex::UnActivePlayer(Player* player_)
{
	player_->ApplySpeed(1/GetSpeed());
	return false;
}