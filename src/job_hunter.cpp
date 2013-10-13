//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_hunter.cpp
//
// ����: ���� - ��ɲ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_hunter.h"
#include "player.h"

#include "abil_dash.h"
#include "abil_sight.h"
#include "abil_antibug.h"
#include "abil_bullet.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"



Job_hunter::Job_hunter():
Job_base("��ɲ�")
{

}

void Job_hunter::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("��ɲ�");

	unit->GetAbility(gm_,new Abil_dash(1));
	unit->GetAbility(gm_,new Abil_antibug(1));
	unit->GetAbility(gm_,new Abil_sight(1));
	unit->GetAbility(gm_,new Abil_bullet(1));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_SHOT_GUN, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_NET, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_KNIFE, coord_def(), -1));
}

const char* Job_hunter::GetInfor()
{
	return "���� ���ƿ� �ɼ��� ��ɲ��̴�.";
}
const char* Job_hunter::GetItemInfor()
{
	return "���ι���:����\n��������:�׹�\n��������:������";
}
const char* Job_hunter::GetAblityInfor()
{
	return "���������� 1����:�������� �ν� ���� ����\n������ 1����:�þ� ����\n����źâ 1����:�ִ� źâ 1�� ����\n�뽬 1����:ª�� ���� ������ �뽬";
}
const char* Job_hunter::GetTip()
{
	return "������ �ָ��� ��� ������ ���մϴ�. �����̼� ��� �Ѿ��� ����ô�.\n�׹��� ���缭 ���� �������� ���߰ų� �뽬�� �̿��ؼ� �����Ȳ�� ���սô�.\n�����ð��� ����� �� �����̹Ƿ� �����ð��� �����սô�.";
}
