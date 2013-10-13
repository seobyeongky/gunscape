//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_antiexplosion.cpp
//
// ����: ���߿� ���� ���������� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_antiexplosion.h"
#include "player.h"

Abil_antiexplosion::Abil_antiexplosion(int level_):
Ability("�����۾�", level_, 3, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_antiexplosion::~Abil_antiexplosion()
{

}


Ability* Abil_antiexplosion::Clone(int level_)
{
	return new Abil_antiexplosion(level_);
}


const char* Abil_antiexplosion::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���ߵ����� 15% ����. ������ 15% �߰�����";
	case 2:
		return "���ߵ����� 40% ����. ������ 40% �߰�����";
	case 3:
		return "���ߵ����� 70% ����. ������������ �鿪";
	}
	return "���� ����";
}


bool Abil_antiexplosion::ActivePlayer(Player* player_)
{
	player_->ApplyDefense(DT_EXPLOSION, level==1?0.85f:(level==2?0.6f:0.3f));
	player_->ApplyDefense(DT_SELF_EXPLOSION, level==1?0.85f:0.6f);
	if(level == 3)
		player_->SetDefResist(DT_SELF_EXPLOSION, true);
	return true;
}
bool Abil_antiexplosion::UnActivePlayer(Player* player_)
{
	player_->ApplyDefense(DT_EXPLOSION, level==1?1/0.85f:(level==2?1/0.6f:1/0.3f));
	player_->ApplyDefense(DT_SELF_EXPLOSION, level==1?1/0.85f:1/0.6f);
	if(level == 3)
		player_->SetDefResist(DT_SELF_EXPLOSION, false);
	return false;
}