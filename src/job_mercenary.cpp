//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_mercenary.cpp
//
// ����: ���� - �뺴
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_mercenary.h"
#include "player.h"

#include "abil_health.h"
#include "abil_live.h"
#include "abil_vampire.h"
#include "abil_murder.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"



Job_Mercenary::Job_Mercenary():
Job_base("�뺴")
{

}

void Job_Mercenary::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("�뺴");

	unit->GetAbility(gm_,new Abil_health(1));
	unit->GetAbility(gm_,new Abil_live(1));
	unit->GetAbility(gm_,new Abil_vampire(1));
	unit->GetAbility(gm_,new Abil_murder(1));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_ASSAUL_RIFLE, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_AXE, coord_def(), -1));
}

const char* Job_Mercenary::GetInfor()
{
	return "���� �ް� �ο�� �뺴�̴�";
}
const char* Job_Mercenary::GetItemInfor()
{
	return "���ι���:���ݼ���\n��������:�ҹ浵��";
}
const char* Job_Mercenary::GetAblityInfor()
{
	return "���� 1����:�ִ� ü�� 10����\n���������� 1����:���� ������ �Ѿ������ ü���� 10ȸ��\n������ 1����:�ΰ��� ������ �������� 15%\nû�λ��� 1����:�ΰ��� ���϶����� ü�� 1ȸ��";
}
const char* Job_Mercenary::GetTip()
{
	return "ü��ȸ���� ���õ� �ɷµ�� ����� �뺴�Դϴ�.\nü�´ɷ��� ������� ���� ���������� �����س����ϴ�.";
}
