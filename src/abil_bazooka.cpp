//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_bazooka.cpp
//
// ����: �ɷ�-����ī�����͸�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_bazooka.h"
#include "main_weapon.h"

Abil_bazooka::Abil_bazooka(int level_):
Ability("����ī ��ũ��", level_, 5, 50, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_bazooka::~Abil_bazooka()
{

}


Ability* Abil_bazooka::Clone(int level_)
{
	return new Abil_bazooka(level_);
}


const char* Abil_bazooka::GetInfor()
{
	switch(level)
	{
	case 1:
		return "����ī�� ��ݼӵ�, �Ѿ˼ӵ�����. �����ð� ����";
	case 2:
		return "����ī�� ��ݼӵ�, �Ѿ˼ӵ�����. �����ð� ����";
	case 3:
		return "����ī�� ��ݼӵ�, �Ѿ˼ӵ�����. �����ð� ����";
	case 4:
		return "����ī�� ��ݼӵ�, �Ѿ˼ӵ�����. �����ð� ����";
	case 5:
		return "����ī�� ��ݼӵ�, �Ѿ˼ӵ�����. �����ð� ����";
	}
	return "���� ����";
}


bool Abil_bazooka::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_BAZOOKA)
	{	
		weapon_->ApplyBurstSpeedApply(1.0f+0.1f*level);
		weapon_->ApplyShotSpeedApply(1.0f+0.1f*level);
		weapon_->ApplyReloadSpeed(1.0f-0.1f*level);
		return true;
	}
	return false;
}
bool Abil_bazooka::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(weapon_->GetType() == WT_BAZOOKA)
	{
		weapon_->ApplyBurstSpeedApply(1/(1.0f+0.1f*level));
		weapon_->ApplyShotSpeedApply(1/(1.0f+0.1f*level));
		weapon_->ApplyReloadSpeed(1/(1.0f-0.1f*level));
		return true;
	}
	return false;
}