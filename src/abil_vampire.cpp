//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_vampire.cpp
//
// ����: �ΰ��� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_vampire.h"
#include "player.h"

Abil_vampire::Abil_vampire(int level_):
Ability("������", level_, 3, 30, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_vampire::~Abil_vampire()
{

}


Ability* Abil_vampire::Clone(int level_)
{
	return new Abil_vampire(level_);
}


float Abil_vampire::GetVamp()
{
	switch(level)
	{
	case 1:
		return 0.15f;
	case 2:
		return 0.3f;
	case 3:
		return 0.5f;
	}
	return false;
}



const char* Abil_vampire::GetInfor()
{
	static char temp[32];
	sprintf_s(temp,32,"�ΰ��� ������ �������� %g%%",100*GetVamp());
	return temp;
}


bool Abil_vampire::ActivePlayer(Player* player_)
{
	player_->UpDownVamp(VT_HUMAN,DT_MELEE,GetVamp());
	return true;
}

bool Abil_vampire::UnActivePlayer(Player* player_)
{
	player_->UpDownVamp(VT_HUMAN,DT_MELEE,-GetVamp());
	return false;
}