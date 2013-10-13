//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_speedreload.cpp
//
// ����: �ɷ�-���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_speedreload.h"
#include "main_weapon.h"

Abil_speedreload::Abil_speedreload(int level_):
Ability("���ǵ帮�ε�", level_, 3, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_speedreload::~Abil_speedreload()
{

}


Ability* Abil_speedreload::Clone(int level_)
{
	return new Abil_speedreload(level_);
}


float Abil_speedreload::GetSpeed()
{
	switch(level)
	{
	case 1:
		return 0.8f;
	case 2:
		return 0.6f;
	case 3:
		return 0.25f;
	}
	return false;
}


const char* Abil_speedreload::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� �ӵ� 20%����";
	case 2:
		return "���� �ӵ� 40%����";
	case 3:
		return "���� �ӵ� 75%����";
	}
	return "���� ����";
}


bool Abil_speedreload::ActiveMainWeapon(Main_Weapon* weapon_)
{
	weapon_->ApplyReloadSpeed(GetSpeed());
	return true;
}
bool Abil_speedreload::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	weapon_->ApplyReloadSpeed(1/GetSpeed());
	return true;
}