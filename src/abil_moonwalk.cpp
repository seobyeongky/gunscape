//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_moonwalk.cpp
//
// ����: �ް����� �г�Ƽ ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_moonwalk.h"
#include "player.h"

Abil_moonwalk::Abil_moonwalk(int level_):
Ability("����ũ", level_, 2, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_moonwalk::~Abil_moonwalk()
{

}


Ability* Abil_moonwalk::Clone(int level_)
{
	return new Abil_moonwalk(level_);
}


const char* Abil_moonwalk::GetInfor()
{
	switch(level)
	{
	case 1:
		return "�ް��� �ӵ� �г�Ƽ 50%����";
	case 2:
		return "�ް��� �ӵ� �г�Ƽ ����";
	}
	return "���� ����";
}


bool Abil_moonwalk::ActivePlayer(Player* player_)
{
	player_->ApplyBackPanalty(level==1?0.5f:0.0f);
	return true;
}

bool Abil_moonwalk::UnActivePlayer(Player* player_)
{
	if(level == 1)
		player_->ApplyBackPanalty(2.0f);
	else
		player_->SetBackPanalty(1.0f);
	return false;
}