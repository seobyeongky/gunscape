//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_flame.cpp
//
// ����: �ɷ�-ȭ�����⸶���͸�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_flame.h"
#include "main_weapon.h"

Abil_flame::Abil_flame(int level_):
Ability("���̷� ��ũ��", level_, 5, 50, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_flame::~Abil_flame()
{

}


Ability* Abil_flame::Clone(int level_)
{
	return new Abil_flame(level_);
}


const char* Abil_flame::GetInfor()
{
	switch(level)
	{
	case 1:
		return "ȭ�������� �ִ� ź�� 8%����, ��Ÿ� ����";
	case 2:
		return "ȭ�������� �ִ� ź�� 16%����, ��Ÿ� ����";
	case 3:
		return "ȭ�������� �ִ� ź�� 24%����, ��Ÿ� ����";
	case 4:
		return "ȭ�������� �ִ� ź�� 32%����, ��Ÿ� ����";
	case 5:
		return "ȭ�������� �ִ� ź�� 40%����, ��Ÿ� ����";		
	}
	return "���� ����";
}


bool Abil_flame::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_FLAME_THROWER)
	{	
		weapon_->ApplyMaxBullet(1.0f+0.08f*level);
		weapon_->UpDownDistance(4.0f*level);
		return true;
	}
	return false;
}
bool Abil_flame::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_FLAME_THROWER)
	{
		weapon_->ApplyMaxBullet(1/(1.0f+0.08f*level));
		weapon_->UpDownDistance(-4.0f*level);
		return true;
	}
	return false;
}