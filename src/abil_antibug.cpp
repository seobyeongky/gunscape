//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_antibug.cpp
//
// ����: ���� �νĹ��� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_antibug.h"
#include "player.h"

Abil_antibug::Abil_antibug(int level_):
Ability("����������", level_, 2, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_antibug::~Abil_antibug()
{

}


Ability* Abil_antibug::Clone(int level_)
{
	return new Abil_antibug(level_);
}


const char* Abil_antibug::GetInfor()
{
	switch(level)
	{
	case 1:
		return "�������� �ν� ���� ����";
	case 2:
		return "�������� �ν� ���� ���� ����";
	}
	return "���� ����";
}


float Abil_antibug::GetValue()
{
	switch(level)
	{
	case 1:
		return 0.7f;
	case 2:
		return 0.4f;
	}
	return false;
}


bool Abil_antibug::ActivePlayer(Player* player_)
{
	player_->ApplySneak(VT_BUG,GetValue());
	return true;
}

bool Abil_antibug::UnActivePlayer(Player* player_)
{
	player_->ApplySneak(VT_BUG,1/GetValue());
	return false;
}