//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_live.cpp
//
// ����: ����������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_live.h"
#include "player.h"

Abil_live::Abil_live(int level_):
Ability("����������", level_, 5, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_live::~Abil_live()
{

}


Ability* Abil_live::Clone(int level_)
{
	return new Abil_live(level_);
}


const char* Abil_live::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ������ �Ѿ������ ü���� 10ȸ��";
	case 2:
		return "���� ������ �Ѿ������ ü���� 15ȸ��";
	case 3:
		return "���� ������ �Ѿ������ ü���� 20ȸ��";
	case 4:
		return "���� ������ �Ѿ������ ü���� 25ȸ��";
	case 5:
		return "���� ������ �Ѿ������ ü���� 30ȸ��";
	}
	return "���� ����";
}

bool Abil_live::EnterMap(Game_Manager* gm_, Player* player_, int level_)
{
	player_->Heal(level*5+5);
	return true;
}
