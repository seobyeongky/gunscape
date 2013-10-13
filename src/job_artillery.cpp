//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_artillery.cpp
//
// ����: ���� - ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_artillery.h"
#include "player.h"

#include "abil_bulletup.h"
#include "abil_antiexplosion.h"
#include "abil_health.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"



Job_artillery::Job_artillery():
Job_base("����")
{

}

void Job_artillery::SetPlayer(Game_Manager* gm_, Player* unit)
{	
	unit->SetName("����");

	unit->GetAbility(gm_,new Abil_bulletup(1));
	unit->GetAbility(gm_,new Abil_antiexplosion(1));
	unit->GetAbility(gm_,new Abil_health(2));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_BAZOOKA, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_GRENADE, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_CLUB, coord_def(), -1));
}

const char* Job_artillery::GetInfor()
{
	return "Ŀ�ٶ� ����ī�� ��� �ٴϴ� �����.";
}
const char* Job_artillery::GetItemInfor()
{
	return "���ι���:����ī\n��������:����ź\n��������:���";
}
const char* Job_artillery::GetAblityInfor()
{
	return "źâ���� 1����:�ִ�ź�� 20%����\n�����۾� 1����:���ߵ����� 15% ����. ������ 15% �߰�����\n���� 2����:�ִ� ü�� 25����";
}
const char* Job_artillery::GetTip()
{
	return "������ �ѹ��� ���� ���������� ���� �����ӵ��� ���߷� ���� ������������ ū �����Դϴ�.\n�׻� ���� ź���� ������ ���ο� �θ鼭 ���÷��ø� �ִ��� �̿��Ͽ� �ο�ô�.";
}