//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_killstamina.cpp
//
// ����: 
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_killstamina.h"
#include "player.h"
#include "gamemanager.h"

Abil_kill_stamina::Abil_kill_stamina(int level_):
Ability("�������", level_, 3, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_kill_stamina::~Abil_kill_stamina()
{

}


Ability* Abil_kill_stamina::Clone(int level_)
{
	return new Abil_kill_stamina(level_);
}


const char* Abil_kill_stamina::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ���϶����� ���¹̳��� ���� ȸ��";
	case 2:
		return "���� ���϶����� ���¹̳��� ���� ȸ���ϰ� �̼��� ��� ����";
	case 3:
		return "���� ���ϸ��� ���¹̳��� ���� ȸ���ϰ� �̼��� ��� ����";
	}
	return "���� ����";
}

float Abil_kill_stamina::Getstamina()
{
	switch(level)
	{
	case 1:
		return 25.0f;
	case 2:
		return 60.0f;
	case 3:
		return 999.0f;
	}
	return false;
}

bool Abil_kill_stamina::KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_)
{
	player_->UpDownStamina(Getstamina());

	if(level>=2)
	{
		player_->SlowApply(1.6f,level==2?50:100,SK_KILL_STAMINA);
		player_->StateApply("�������",level==2?50:100);
	}
	return true;
}

