//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_teemo.cpp
//
// ����: ���� - ����ü Ƽ�� ������?
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_teemo.h"
#include "player.h"

#include "abil_escape_forget.h"
#include "abil_dex.h"
#include "abil_fast_portal.h"
#include "abil_run.h"


#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"


Job_teemo::Job_teemo():
Job_base("������")
{

}

void Job_teemo::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("������");
	
	unit->GetAbility(gm_,new Abil_Escape_Forget(1));
	unit->GetAbility(gm_,new Abil_fast_portal(1));
	unit->GetAbility(gm_,new Abil_dex(1));
	unit->GetAbility(gm_,new Abil_run(1));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_DART, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_CLOAK, unit, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_TRAP, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_CLUB, coord_def(), -1));
}

const char* Job_teemo::GetInfor()
{
	return "���� ������";
}
const char* Job_teemo::GetItemInfor()
{
	return "���ι���:��ħ\n��������:���Ÿ���\n��������:��\n��������:���";
}
const char* Job_teemo::GetAblityInfor()
{
	return "�������� 1����:����ĥ�� ���� �������µ� �ʿ��� �ð��� ������ �ȴ�.\n�����н� 1����:��Ż���Խð� 50%����. Ż���� ��������.\n������ 1����:�̵��ӵ� 10% ����\n���� 1����:���� �Ͻ��� �޸��� �ӵ� 20% ����";
}
const char* Job_teemo::GetTip()
{
	return "����ϰ� �ο��˴ϴ�.\n��ó�� ��� Ƣ�� ©©�� ��������. ���񿡰Դ� ���� �������� ������ �ǰ� �κ����Դ� �������ʽ��ϴ�.";
}
