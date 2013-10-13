//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_sight.cpp
//
// ����: �þ�����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_sight.h"
#include "player.h"

Abil_sight::Abil_sight(int level_):
Ability("������", level_, 3, 20, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_sight::~Abil_sight()
{

}


Ability* Abil_sight::Clone(int level_)
{
	return new Abil_sight(level_);
}


const char* Abil_sight::GetInfor()
{
	switch(level)
	{
	case 1:
		return "�þ� ����";
	case 2:
		return "�þ� ����";
	case 3:
		return "�þ� ����";
	}
	return "���� ����";
}


bool Abil_sight::ActivePlayer(Player* player_)
{
	player_->UpDownSight(13.0f*level);
	return true;
}

bool Abil_sight::UnActivePlayer(Player* player_)
{
	player_->UpDownSight(-13.0f*level);
	return false;
}