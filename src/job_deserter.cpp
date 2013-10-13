//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_deserter.cpp
//
// ����: ���� - Ż����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_deserter.h"
#include "player.h"

#include "abil_health.h"
#include "abil_bulletbonus.h"
#include "abil_escape_forget.h"
#include "abil_moonwalk.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"



Job_deserter::Job_deserter():
Job_base("Ż����")
{

}

void Job_deserter::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("Ż����");

	unit->GetAbility(gm_,new Abil_health(1));
	unit->GetAbility(gm_,new Abil_bulletbonus(1));
	unit->GetAbility(gm_,new Abil_moonwalk(1));
	unit->GetAbility(gm_,new Abil_Escape_Forget(1));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_ASSAUL_RIFLE, coord_def(), -1));
	//unit->SetMainWeapon(New_Main_Weapon(MWK_HEAVY, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_KEVLAR, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_KNIFE, coord_def(), -1));
}

const char* Job_deserter::GetInfor()
{
	return "���⸦ ������ä�� ���븦 Ż���� �����.";
}
const char* Job_deserter::GetItemInfor()
{
	return "���ι���:���ݼ���\n��������:��ź��\n��������:������";
}
const char* Job_deserter::GetAblityInfor()
{
	return "���� 1����:�ִ� ü�� 10����\n���ں��� 1����:���� ������ �Ѿ������ źâ 1���� ����\n����ũ 1����:�ް��� �ӵ� �г�Ƽ 50%����\n�������� 1����:����ĥ�� ���� �������µ� �ʿ��� �ð��� ������ �ȴ�.";
}
const char* Job_deserter::GetTip()
{
	return "�⺻���� �����Դϴ�.";
}
