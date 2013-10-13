//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_see_sight.cpp
//
// ����: �þߺ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_see_sight.h"
#include "player.h"

Abil_see_sight::Abil_see_sight(int level_):
Ability("���谨��", level_, 1, 50, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_see_sight::~Abil_see_sight()
{

}


Ability* Abil_see_sight::Clone(int level_)
{
	return new Abil_see_sight(level_);
}


const char* Abil_see_sight::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� �þ߸� �� �� �ִ�.";
	}
	return "���� ����";
}

bool Abil_see_sight::ActivePlayer(Player* player_)
{
	player_->SetMonSightView(true);
	return true;
}

bool Abil_see_sight::UnActivePlayer(Player* player_)
{
	player_->SetMonSightView(false);
	return false;
}

