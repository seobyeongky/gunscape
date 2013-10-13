//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_bulletup.cpp
//
// ����: �ɷ�-źâ ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_bulletup.h"
#include "main_weapon.h"

Abil_bulletup::Abil_bulletup(int level_):
Ability("źâ����", level_, 5, 30, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_bulletup::~Abil_bulletup()
{

}


Ability* Abil_bulletup::Clone(int level_)
{
	return new Abil_bulletup(level_);
}



const char* Abil_bulletup::GetInfor()
{
	switch(level)
	{
	case 1:
		return "�ִ�ź�� 20%����";
	case 2:
		return "�ִ�ź�� 40%����";
	case 3:
		return "�ִ�ź�� 60%����";
	case 4:
		return "�ִ�ź�� 80%����";
	case 5:
		return "�ִ�ź�� 100%����";
	}
	return "���� ����";
}



bool Abil_bulletup::ActiveMainWeapon(Main_Weapon* weapon_)
{
	weapon_->ApplyMaxBullet(1.0f+0.2f*level);
	return true;
}
bool Abil_bulletup::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	weapon_->ApplyMaxBullet(1/(1.0f+0.2f*level));
	return true;
}