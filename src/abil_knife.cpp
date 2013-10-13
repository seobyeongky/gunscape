//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_knife.cpp
//
// ����: �ɷ�-�����������͸�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_knife.h"
#include "melee_weapon.h"
#include "main_weapon.h"

Abil_knife::Abil_knife(int level_):
Ability("�ϻ���", level_, 4, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_knife::~Abil_knife()
{

}


Ability* Abil_knife::Clone(int level_)
{
	return new Abil_knife(level_);
}


const char* Abil_knife::GetInfor()
{
	switch(level)
	{
	case 1:
		return "��� �齺��, ��弦 ������ 1.25��";
	case 2:
		return "��� �齺��, ��弦 ������ 1.5��";
	case 3:
		return "��� �齺��, ��弦 ������ 2��";
	case 4:
		return "��� �齺��, ��弦 ������ 2.5��";
	}
	return "���� ����";
}
float Abil_knife::GetDamage()
{
	switch(level)
	{
	case 1:
		return 1.25f;
	case 2:
		return 1.5f;
	case 3:
		return 2.0f;
	case 4:
		return 2.5f;
	}
	return false;
}


bool Abil_knife::ActiveMeleeWeapon(Melee_Weapon* weapon_)
{
	if(weapon_->GetBackStab()>1.0f)
		weapon_->ApplyBackStab(GetDamage());
	return false;
}
bool Abil_knife::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetSniper()>1.0f)
		weapon_->ApplySniper(GetDamage());
	return false;
}
bool Abil_knife::UnActiveMeleeWeapon(Melee_Weapon* weapon_)
{
	if(weapon_->GetBackStab()>1.0f)
		weapon_->ApplyBackStab(1/GetDamage());
	return false;
}
bool Abil_knife::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetSniper()>1.0f)
		weapon_->ApplySniper(1/GetDamage());
	return false;
}