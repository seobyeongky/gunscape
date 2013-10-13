//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_murder.cpp
//
// ����: �ɷ�-û�λ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_murder.h"
#include "player.h"
#include "monster.h"
#include "random.h"

Abil_murder::Abil_murder(int level_):
Ability("û�λ���", level_, 5, 50, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_murder::~Abil_murder()
{

}


Ability* Abil_murder::Clone(int level_)
{
	return new Abil_murder(level_);
}


const char* Abil_murder::GetInfor()
{
	switch(level)
	{
	case 1:
		return "�ΰ��� ���϶����� ü�� 1ȸ��";
	case 2:
		return "�ΰ��� ���϶����� �ִ� ü�� 1����";
	case 3:
		return "�ΰ��� ���϶����� �ִ� ü�� 1~2����";
	case 4:
		return "�ΰ��� ���϶����� �ִ� ü�� 2����";
	case 5:
		return "�ΰ��� ���϶����� �ִ� ü�� 3����";
	}
	return "���� ����";
}

int Abil_murder::GetHp()
{
	switch(level)
	{
	case 1:
		return 0;
	case 2:
		return 1;
	case 3:
		return rand_int(1,2);
	case 4:
		return 2;
	case 5:
		return 3;
	}
	return false;
}

bool Abil_murder::KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_)
{
	if(monster_->GetKind() == VT_HUMAN)
	{
		if(level>=2)
		{
			int hp_ = GetHp();
			player_->UpDownMaxHp(hp_);
			player_->Heal(hp_);
		}
		else
			player_->Heal(1);
	}

	return true;
}

