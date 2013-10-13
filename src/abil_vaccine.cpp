//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_vaccine.cpp
//
// ����: ���̷��� �鿪
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_vaccine.h"
#include "player.h"
#include "main_weapon.h"

Abil_vaccine::Abil_vaccine(int level_):
Ability("��ü", level_, 2, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
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
		return "���̷��� ���� 50%����";
	case 2:
		return "���̷����� �鿪";
	}
	return "���� ����";
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