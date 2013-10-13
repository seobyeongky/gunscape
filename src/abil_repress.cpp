//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_repress.cpp
//
// ����: �ʱ�����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_repress.h"
#include "player.h"

Abil_repress::Abil_repress(int level_):
Ability("�ʱ�����", level_, 5, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_repress::~Abil_repress()
{

}


Ability* Abil_repress::Clone(int level_)
{
	return new Abil_repress(level_);
}


const char* Abil_repress::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ������ �Ѿ������ 20�ʰ� ���ݷ� 20% ����";
	case 2:
		return "���� ������ �Ѿ������ 20�ʰ� ���ݷ� 35% ����";
	case 3:
		return "���� ������ �Ѿ������ 20�ʰ� ���ݷ� 50% ����";
	case 4:
		return "���� ������ �Ѿ������ 20�ʰ� ���ݷ� 70% ����";
	case 5:
		return "���� ������ �Ѿ������ 20�ʰ� ���ݷ� 100% ����";
	}
	return "���� ����";
}
float Abil_repress::Getattack()
{
	switch(level)
	{
	case 1:
		return 1.20f;
	case 2:
		return 1.35f;
	case 3:
		return 1.5f;
	case 4:
		return 1.7f;
	case 5:
		return 2.0f;
	}
	return false;
}

bool Abil_repress::EnterMap(Game_Manager* gm_, Player* player_, int level_)
{	
	player_->AttackApply(Getattack(),1200,ABK_PORTAL);
	player_->StateApply("�ʱ�����",1200);
	return true;
}
