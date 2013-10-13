//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_shot_gun.cpp
//
// ����: �ɷ�-���Ǹ����͸�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_shot_gun.h"
#include "main_weapon.h"

Abil_shot_gun::Abil_shot_gun(int level_):
Ability("���� ��ũ��", level_, 5, 50, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_shot_gun::~Abil_shot_gun()
{

}


Ability* Abil_shot_gun::Clone(int level_)
{
	return new Abil_shot_gun(level_);
}


const char* Abil_shot_gun::GetInfor()
{
	switch(level)
	{
	case 1:
		return "������ �ѹ��� ������ �Ѿ� ���� 1 ����, �˹� ����";
	case 2:
		return "������ �ѹ��� ������ �Ѿ� ���� 2 ����, �˹� ����";
	case 3:
		return "������ �ѹ��� ������ �Ѿ� ���� 3 ����, �˹� ����";
	case 4:
		return "������ �ѹ��� ������ �Ѿ� ���� 4 ����, �˹� ����";
	case 5:
		return "������ �ѹ��� ������ �Ѿ� ���� 5 ����, �˹� ����";	
	}
	return "���� ����";
}


bool Abil_shot_gun::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_SHOTGUN)
	{	
		weapon_->UpDownBunch(level);
		weapon_->ApplyPower(1.0f-0.2f*level);
		weapon_->ApplyMaxPower(1.0f-0.2f*level);
		return true;
	}
	return false;
}
bool Abil_shot_gun::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_SHOTGUN)
	{
		weapon_->UpDownBunch(-level);
		weapon_->ApplyPower(1/(1.0f-0.2f*level));
		weapon_->ApplyMaxPower(1/(1.0f-0.2f*level));
		return true;
	}
	return false;
}