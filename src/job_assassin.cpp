//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_stalker.cpp
//
// ����: ���� - ������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_assassin.h"
#include "player.h"

#include "abil_invisible.h"
#include "abil_knife.h"
#include "abil_state_view.h"
#include "abil_sleep.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"


Job_assassin::Job_assassin():
Job_base("�ϻ���")
{

}

void Job_assassin::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("�ϻ���");

	unit->GetAbility(gm_,new Abil_knife(1));
	unit->GetAbility(gm_,new Abil_invisible(2));
	unit->GetAbility(gm_,new Abil_state_view(1));

	unit->SetMainWeapon(New_Main_Weapon(MWK_RIFLE_PISTOL_BIG, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_SILENCER, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_KNIFE, coord_def(), -1));
}

const char* Job_assassin::GetInfor()
{
	return "���� ���� ����ϴ� �ϻ��ڴ�.";
}
const char* Job_assassin::GetItemInfor()
{
	return "���ι���:����Ʈ �̱�\n��������:������\n��������:������";
}
const char* Job_assassin::GetAblityInfor()
{
	return "�ϻ��� 1����:��� �齺��, ��弦 ������ 1.25��\n���� 1����:���� ���¿� �����Ҹ� �˾�ç �� �ִ�\n���� 2����:���� ���Ż���, �̼Ӱ���(źâ 0.5�� �Ҹ�)";
}

const char* Job_assassin::GetTip()
{
	return "���� ���� ǥ�ð� ? ����̶�� ���� �÷��̾ ��ġ �� æ �����Դϴ�.\n���� ������ ��ġ��æ ���¿��� �������� ���ݽ� �齺������ ���� �� �ֽ��ϴ�.\n���� �þ� �ۿ��� ���Ż��·� �����ؾ��մϴ�. �ٸ�, �þ� �����̸� ���ŵ� ��ų �� �ֽ��ϴ�.\n�̹� ��Ų ��볪 ���ֺ��� ���� ���� ������ �齺�� �ѹ濡 �� �״� ���̹Ƿ� �������� �����սô�.";
}