//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_rifle.cpp
//
// ����: �ɷ�-�����ø����͸�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_rifle.h"
#include "main_weapon.h"

Abil_rifle::Abil_rifle(int level_):
Ability("������ ��ũ��", level_, 5, 50, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_rifle::~Abil_rifle()
{

}


Ability* Abil_rifle::Clone(int level_)
{
	return new Abil_rifle(level_);
}


const char* Abil_rifle::GetInfor()
{
	switch(level)
	{
	case 1:
		return "�������� �ִ� ź�� 8%����, �ݵ� ����";
	case 2:
		return "�������� �ִ� ź�� 16%����, �ݵ� ����";
	case 3:
		return "�������� �ִ� ź�� 24%����, �ݵ� ����";
	case 4:
		return "�������� �ִ� ź�� 32%����, �ݵ� ����";
	case 5:
		return "�������� �ִ� ź�� 40%����, �ݵ� ����";	
	}
	return "���� ����";
}


bool Abil_rifle::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_RIFLE)
	{	
		weapon_->ApplyMaxBullet(1.0f+0.08f*level);
		weapon_->ApplyFocusReact(1.0f-0.1f*level);
		return true;
	}
	return false;
}
bool Abil_rifle::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_RIFLE)
	{
		weapon_->ApplyMaxBullet(1/(1.0f+0.08f*level));
		weapon_->ApplyFocusReact(1/(1.0f-0.1f*level));
		return true;
	}
	return false;
}