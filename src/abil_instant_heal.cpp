//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_instant_heal.cpp
//
// ����: �ɷ�-�ν��Ͻ�-���ȸ��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_instant_heal.h"
#include "player.h"

Abil_Instant_heal::Abil_Instant_heal(int level_):
Ability("���ȸ��", level_, 1, 30, 1, AT_INSTANCE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_Instant_heal::~Abil_Instant_heal()
{

}


Ability* Abil_Instant_heal::Clone(int level_)
{
	return new Abil_Instant_heal(level_);
}


const char* Abil_Instant_heal::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ��� ü���� 100 ȸ��";
	}
	return "���� ����";
}

bool Abil_Instant_heal::InstanceActive(Player* player_)
{	
	player_->Heal(100);
	return true;
}