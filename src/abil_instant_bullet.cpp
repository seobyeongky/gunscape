//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_instant_bullet.cpp
//
// ����: �ɷ�-�ν��Ͻ�-źâȸ��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_instant_bullet.h"
#include "player.h"

Abil_Instant_bullet::Abil_Instant_bullet(int level_):
Ability("źâ����", level_, 1, 30, 1, AT_INSTANCE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_Instant_bullet::~Abil_Instant_bullet()
{

}


Ability* Abil_Instant_bullet::Clone(int level_)
{
	return new Abil_Instant_bullet(level_);
}


const char* Abil_Instant_bullet::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ��� źâ�� ���� ��";
	}
	return "���� ����";
}

bool Abil_Instant_bullet::InstanceActive(Player* player_)
{	
	player_->SuppleBullet((float)player_->GetMaxBullet());
	return true;
}