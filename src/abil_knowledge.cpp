//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_knowledge.cpp
//
// ����: ���ôɷ� 1�� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_knowledge.h"
#include "player.h"

Abil_knowledge::Abil_knowledge(int level_):
Ability("�������", level_, 3, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_knowledge::~Abil_knowledge()
{

}


Ability* Abil_knowledge::Clone(int level_)
{
	return new Abil_knowledge(level_);
}


const char* Abil_knowledge::GetInfor()
{
	switch(level)
	{
	case 1:
		return "�������� �����ϴ� �ɷ� ���� �ִ�ġ 1�� ����";
	case 2:
		return "�������� �����ϴ� �ɷ� ���� �ִ�ġ 2�� ����";
	case 3:
		return "�������� �����ϴ� �ɷ� ���� �ִ�ġ 3�� ����";
	}
	return "���� ����";
}

bool Abil_knowledge::ActivePlayer(Player* player_)
{
	player_->SetSelectAbilityNum(3+level);
	return true;
}

bool Abil_knowledge::UnActivePlayer(Player* player_)
{
	player_->SetSelectAbilityNum(3);
	return false;
}