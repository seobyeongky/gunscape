//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_shadow.cpp
//
// ����: �νĹ��� ��������(����)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_shadow.h"
#include "player.h"

Abil_shadow::Abil_shadow(int level_):
Ability("�׸��ڰȱ�", level_, 2, 5, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_shadow::~Abil_shadow()
{

}


Ability* Abil_shadow::Clone(int level_)
{
	return new Abil_shadow(level_);
}


const char* Abil_shadow::GetInfor()
{
	switch(level)
	{
	case 1:
		return "������ �ν� ���� ����";
	case 2:
		return "������ �ν� ���� ����";
	}
	return "���� ����";
}


float Abil_shadow::GetValue()
{
	switch(level)
	{
	case 1:
		return 0.8f;
	case 2:
		return 0.6f;
	}
	return false;
}


bool Abil_shadow::ActivePlayer(Player* player_)
{
	player_->ApplySneak(VT_ALL,GetValue());
	return true;
}

bool Abil_shadow::UnActivePlayer(Player* player_)
{
	player_->ApplySneak(VT_ALL,1/GetValue());
	return false;
}