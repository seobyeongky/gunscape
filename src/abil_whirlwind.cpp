//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_whirlwind.cpp
//
// ����: �ɷ�-�����������͸�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_whirlwind.h"
#include "melee_weapon.h"
#include "main_weapon.h"

Abil_whirlwind::Abil_whirlwind(int level_):
Ability("������", level_, 2, 30, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_whirlwind::~Abil_whirlwind()
{

}


Ability* Abil_whirlwind::Clone(int level_)
{
	return new Abil_whirlwind(level_);
}


const char* Abil_whirlwind::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ���Ⱑ �������� �����ϰ� �ȴ�";
	case 2:
		return "���� ���Ⱑ �������� �����ϰ� ��Ÿ��� 1.5�谡 �ȴ�";
	}
	return "���� ����";
}


bool Abil_whirlwind::ActiveMeleeWeapon(Melee_Weapon* weapon_)
{
	if(weapon_->GetWWPannalty())
	{
		weapon_->ApplyWidth(10.0f);
		weapon_->ApplyBurstSpeedApply(1/weapon_->GetWWPannalty());
	}
	if(level == 2)
		weapon_->ApplyDistance(1.5f);
	return false;
}

bool Abil_whirlwind::UnActiveMeleeWeapon(Melee_Weapon* weapon_)
{
	if(weapon_->GetWWPannalty())
	{
		weapon_->ApplyWidth(1/10.0f);
		weapon_->ApplyBurstSpeedApply(weapon_->GetWWPannalty());
	}
	if(level == 2)
		weapon_->ApplyDistance(1/1.5f);
	return false;
}