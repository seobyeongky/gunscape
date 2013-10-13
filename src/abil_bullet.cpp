//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_bullet.cpp
//
// ����: �ɷ� - ���� źâ
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_bullet.h"
#include "player.h"

Abil_bullet::Abil_bullet(int level_):
Ability("����źâ", level_,/*�ִ뷹��*/3, /*Ȯ��*/100, /*�ʿ䷹��*/1, /*�ɷ�����*/AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_bullet::~Abil_bullet()
{

}


Ability* Abil_bullet::Clone(int level_)
{
	return new Abil_bullet(level_);
}


const char* Abil_bullet::GetInfor()
{
	switch(level)
	{
	case 1:
		return "�ִ� źâ 1�� ����";
	case 2:
		return "�ִ� źâ 2�� ����";
	case 3:
		return "�ִ� źâ 3�� ����";
	}
	return "���� ����";
}
bool Abil_bullet::ActivePlayer(Player* player_)
{
	player_->UpDownMaxBullet(level);
	return true;
}

bool Abil_bullet::UnActivePlayer(Player* player_)
{
	player_->UpDownMaxBullet(-level);
	return false;
}