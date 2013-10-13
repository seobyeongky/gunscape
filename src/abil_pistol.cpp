//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_pistol.cpp
//
// ����: �ɷ�-���Ѹ����͸�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_pistol.h"
#include "main_weapon.h"

Abil_pistol::Abil_pistol(int level_):
Ability("���� ��ũ��", level_, 5, 50, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_pistol::~Abil_pistol()
{

}


Ability* Abil_pistol::Clone(int level_)
{
	return new Abil_pistol(level_);
}


const char* Abil_pistol::GetInfor()
{
	switch(level)
	{
	case 1:
		return "������ �ִ� ź�� 1����, �ݵ� ����, ��ݼӵ� ����";
	case 2:
		return "������ �ִ� ź�� 2����, �ݵ� ����, ��ݼӵ� ����";
	case 3:
		return "������ �ִ� ź�� 3����, �ݵ� ����, ��ݼӵ� ����";
	case 4:
		return "������ �ִ� ź�� 4����, �ݵ� ����, ��ݼӵ� ����";
	case 5:
		return "������ �ִ� ź�� 5����, �ݵ� ����, ��ݼӵ� ����";	
	}
	return "���� ����";
}


bool Abil_pistol::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_PISTOL)
	{	
		weapon_->SetMaxBullet(weapon_->GetMaxBullet()+level);
		weapon_->ApplyFocusReact(1.0f-0.1f*level);
		weapon_->ApplyBurstSpeedApply(1.0f+0.1f*level);
		return true;
	}
	return false;
}
bool Abil_pistol::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_PISTOL)
	{
		weapon_->SetMaxBullet(weapon_->GetMaxBullet()-level);
		weapon_->ApplyFocusReact(1/(1.0f-0.1f*level));
		weapon_->ApplyBurstSpeedApply(1/(1.0f+0.1f*level));
		return true;
	}
	return false;
}