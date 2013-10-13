//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_map.cpp
//
// ����: �þߺ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_map.h"
#include "player.h"

Abil_map::Abil_map(int level_):
Ability("����", level_, 1, 5, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_map::~Abil_map()
{

}


Ability* Abil_map::Clone(int level_)
{
	return new Abil_map(level_);
}


const char* Abil_map::GetInfor()
{
	switch(level)
	{
	case 1:
		return "������ �� ��ü�� ��Ż�� ��ġ�� Ȯ�� �� �� �ִ�.";
	}
	return "���� ����";
}

bool Abil_map::ActivePlayer(Player* player_)
{
	player_->SetMapHack(true);
	return true;
}

bool Abil_map::UnActivePlayer(Player* player_)
{
	player_->SetMapHack(false);
	return false;
}