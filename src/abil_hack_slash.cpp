//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_hack_slash.cpp
//
// ����: 
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_hack_slash.h"
#include "player.h"
#include "gamemanager.h"

Abil_hack_slash::Abil_hack_slash(int level_):
Ability("�پؽ�����", level_, 5, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_hack_slash::~Abil_hack_slash()
{

}


Ability* Abil_hack_slash::Clone(int level_)
{
	return new Abil_hack_slash(level_);
}


const char* Abil_hack_slash::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ���϶����� 3�ʰ� ���ݷ��� 20%����(��ø����)";
	case 2:
		return "���� ���϶����� 4�ʰ� ���ݷ��� 20%����(��ø����)";
	case 3:
		return "���� ���ϸ��� 5�ʰ� ���ݷ��� 30%����(��ø����)";
	case 4:
		return "���� ���ϸ��� 6�ʰ� ���ݷ��� 30%����(��ø����)";
	case 5:
		return "���� ���ϸ��� 7�ʰ� ���ݷ��� 40%����(��ø����)";
	}
	return "���� ����";
}

int Abil_hack_slash::Getsecond()
{
	switch(level)
	{
	case 1:
		return 180;
	case 2:
		return 240;
	case 3:
		return 300;
	case 4:
		return 360;
	case 5:
		return 420;
	}
	return false;
}
float Abil_hack_slash::Getattack()
{
	switch(level)
	{
	case 1:
		return 1.2f;
	case 2:
		return 1.2f;
	case 3:
		return 1.3f;
	case 4:
		return 1.3f;
	case 5:
		return 1.4f;
	}
	return false;
}
bool Abil_hack_slash::KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_)
{
	player_->AttackApply(Getattack(),Getsecond(),ABK_HACK_SLASH);
	player_->StateApply("�پؽ�����",Getsecond());
	return true;
}

