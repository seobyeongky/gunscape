//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_mirror_damage.cpp
//
// ����: �ݻ絥����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_mirror_damage.h"
#include "player.h"

Abil_mirror_damage::Abil_mirror_damage(int level_):
Ability("���ð���", level_, 3, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_mirror_damage::~Abil_mirror_damage()
{

}


Ability* Abil_mirror_damage::Clone(int level_)
{
	return new Abil_mirror_damage(level_);
}


const char* Abil_mirror_damage::GetInfor()
{
	switch(level)
	{
	case 1:
		return "������ ������������ �޾����� �ݻ絥������ ��";
	case 2:
		return "������ ������������ �޾����� �ݻ絥������ ��";
	case 3:
		return "������ ������������ �޾����� �ݻ絥������ ��";
	}
	return "���� ����";
}

float Abil_mirror_damage::Getdamage()
{
	switch(level)
	{
	case 1:
		return 15.0f;
	case 2:
		return 30.0f;
	case 3:
		return 50.0f;
	}
	return false;
}

bool Abil_mirror_damage::ActivePlayer(Player* player_)
{
	player_->SetMirrorDamage(Getdamage());
	return true;
}
bool Abil_mirror_damage::UnActivePlayer(Player* player_)
{
	player_->SetMirrorDamage(0.0f);
	return false;
}