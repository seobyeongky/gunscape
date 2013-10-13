//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_escape_forget.cpp
//
// ����: ��������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_escape_forget.h"
#include "player.h"

Abil_Escape_Forget::Abil_Escape_Forget(int level_):
Ability("��������", level_, 2, 100, /*�ʿ䷹��*/1, /*�ɷ�����*/AT_PASSIVE)
{
}


Abil_Escape_Forget::~Abil_Escape_Forget()
{

}


Ability* Abil_Escape_Forget::Clone(int level_)
{
	return new Abil_Escape_Forget(level_);
}


const char* Abil_Escape_Forget::GetInfor()
{
	switch(level)
	{
	case 1:
		return "����ĥ�� ���� �������µ� �ʿ��� �ð��� ������ �ȴ�.";
	case 2:
		return "����ĥ�� ���� ��ٷ� �������� �ȴ�.";
	}
	return "���� ����";
}


bool Abil_Escape_Forget::ActivePlayer(Player* player_)
{
	if(level == 1)
		player_->SetForgetCount(300);
	else if(level == 2)
		player_->SetForgetCount(50);
	return true;
}

bool Abil_Escape_Forget::UnActivePlayer(Player* player_)
{
	if(level == 1)
		player_->SetForgetCount(600);
	else if(level == 2)
		player_->SetForgetCount(600);

	return false;
}