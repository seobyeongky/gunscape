//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_pyro.cpp
//
// ����: ���� - ��ȭ��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_pyro.h"
#include "player.h"

#include "abil_speedreload.h"
#include "abil_fire.h"
#include "abil_health.h"


#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"




Job_pyro::Job_pyro():
Job_base("��ȭ��")
{

}

void Job_pyro::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("��ȭ��");

	unit->GetAbility(gm_,new Abil_fire(1));
	unit->GetAbility(gm_,new Abil_speedreload(1));
	unit->GetAbility(gm_,new Abil_health(2));

	unit->SetMainWeapon(New_Main_Weapon(MWK_FLAME_THROWER, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_AXE, coord_def(), -1));
}

const char* Job_pyro::GetInfor()
{
	return "��ȭ �� ��ü�� ���� ��ȭ���̴�.";
}
const char* Job_pyro::GetItemInfor()
{
	return "���ι���:ȭ������\n��������:�ҹ浵��";
}
const char* Job_pyro::GetAblityInfor()
{
	return "������ 1����:ȭ������ 25%����\n���ǵ帮�ε� 1����:���� �ӵ� 20%����\n���� 2����:�ִ� ü�� 25����";
}
const char* Job_pyro::GetTip()
{
	return "ȭ������� ��Ÿ��� ª���Ƿ� ���Ÿ� ���̸� �ڳʸ� �̿��Ͽ� ���� �Ÿ��� ���Խô�.\nȭ�����Ⱑ ���� �����ϴ� ���� �ִ��� Ȱ���ϰ� �ſ� �� �����ð��� �����սô�.";
}
