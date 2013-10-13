//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_bloodreload.cpp
//
// ����: ��������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_bloodreload.h"
#include "player.h"

Abil_bloodreload::Abil_bloodreload(int level_):
Ability("��������", level_, 3, 30, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_bloodreload::~Abil_bloodreload()
{

}


Ability* Abil_bloodreload::Clone(int level_)
{
	return new Abil_bloodreload(level_);
}


int Abil_bloodreload::GetCost()
{
	switch(level)
	{
	case 1:
		return 20;
	case 2:
		return 10;
	case 3:
		return 3;
	}
	return false;
}



const char* Abil_bloodreload::GetInfor()
{
	static char temp[64];
	sprintf_s(temp,64,"���� źȯ�� ������ ü�� %d�� �Ҹ��ϰ� ��������",GetCost());
	return temp;
}


bool Abil_bloodreload::ActivePlayer(Player* player_)
{
	player_->SetBloodReload(GetCost());
	return true;
}

bool Abil_bloodreload::UnActivePlayer(Player* player_)
{
	player_->SetBloodReload(0);
	return false;
}