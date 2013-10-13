//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_deathbomb.cpp
//
// ����: ��������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_deathbomb.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_bomb.h"
#include "monster.h"

Abil_deathbomb::Abil_deathbomb(int level_):
Ability("��������", level_, 4, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_deathbomb::~Abil_deathbomb()
{

}


Ability* Abil_deathbomb::Clone(int level_)
{
	return new Abil_deathbomb(level_);
}


const char* Abil_deathbomb::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ���϶����� ������ ������ �ֺ��� ������ �������� �ش�";
	case 2:
		return "���� ���϶����� ������ ������ �ֺ��� ������ �������� �ش�";
	case 3:
		return "���� ���϶����� ������ ������ �ֺ��� ������ �������� �ش�";
	case 4:
		return "���� ���϶����� ������ ������ �ֺ��� ������ �������� �ش�";
	}
	return "���� ����";
}

float Abil_deathbomb::GetDamage()
{
	switch(level)
	{
	case 1:
		return 15.0f;
	case 2:
		return 25.0f;
	case 3:
		return 40.0f;
	case 4:
		return 80.0f;
	}
	return false;
}
float Abil_deathbomb::GetRange()
{
	switch(level)
	{
	case 1:
		return 15.0f;
	case 2:
		return 20.0f;
	case 3:
		return 25.0f;
	case 4:
		return 40.0f;
	}
	return false;
}
bool Abil_deathbomb::KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_)
{
	gm_->shot_list.push_back(new Shot_bomb(player_, monster_->GetPos(), GetDamage(), 1.0f, 2.0f, GetRange(), player_->GetTeam()));			

	return true;
}