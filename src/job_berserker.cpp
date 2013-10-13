//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_berserker.cpp
//
// ����: ���� - ������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_berserker.h"
#include "player.h"

#include "abil_health.h"
#include "abil_berserker.h"
#include "abil_whirlwind.h"
#include "abil_vampire.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"



Job_berserker::Job_berserker():
Job_base("������")
{

}

void Job_berserker::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("������");

	//unit->SetMainWeapon(New_Main_Weapon(MWK_RIFLE_PISTOL, coord_def(), -1));
	unit->GetAbility(gm_,new Abil_health(1));
	unit->GetAbility(gm_,new Abil_berserker(1));
	unit->GetAbility(gm_,new Abil_whirlwind(1));
	unit->GetAbility(gm_,new Abil_vampire(1));
	
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_AXE, coord_def(), -1));
}

const char* Job_berserker::GetInfor()
{
	return "����ȭ�� ����Ͽ� ��������� �ο�� �������.";
}
const char* Job_berserker::GetItemInfor()
{
	return "��������:�ҹ浵��";
}
const char* Job_berserker::GetAblityInfor()
{
	return "���� 1����:�ִ� ü�� 10����\n����ȭ 1����:������ ���� ����ȭ. ������������ �鿪(źâ 0.5�� �Ҹ�)\n������ 1����:���� ���Ⱑ �������� �����ϰ� �ȴ�\n������ 1����:�ΰ��� ������ �������� 15%";
}
const char* Job_berserker::GetTip()
{
	return "������ ��� ���������� ����ȭ�� �ɷ��� ���� ������ ���������� ���������ϴ�.\n���� �������� �������� �ѱ⸦ ����ϴ� ���� ���� �Ѿ��� ���ϹǷ� ������ ���ϴ°� �����ϴ�.";
}
