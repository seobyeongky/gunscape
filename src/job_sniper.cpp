//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_sniper.cpp
//
// ����: ���� - ���ݼ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_sniper.h"
#include "player.h"

#include "abil_live.h"
#include "abil_sight.h"
#include "abil_shadow.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"


Job_sniper::Job_sniper():
Job_base("���ݼ�")
{

}

void Job_sniper::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("���ݼ�");

	unit->GetAbility(gm_,new Abil_live(1));
	unit->GetAbility(gm_,new Abil_shadow(1));
	unit->GetAbility(gm_,new Abil_sight(2));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_SNIPER, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_CLOAK, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_KNIFE, coord_def(), -1));
}

const char* Job_sniper::GetInfor()
{
	return "�ָ��� ���� �ϻ��ϴ� ���ݼ���.";
}

const char* Job_sniper::GetItemInfor()
{
	return "���ι���:���ݶ�����\n��������:���Ÿ���\n��������:������";
}
const char* Job_sniper::GetAblityInfor()
{
	return "���������� 1����:���� ������ �Ѿ������ ü���� 10ȸ��\n�׸��ڰȱ� 1����:������ �ν� ���� ����\n������ 2����:�þ� ����";
}
const char* Job_sniper::GetTip()
{
	return "���콺 ��Ŭ������ �������� �������� ���ݷ��� 2�谡 �Ǵ� ���ݸ�尡 �˴ϴ�.\n���� �þ߹ۿ����� �ڳʿ��� �̸� ����� ������ �ϰ� ���ݸ��� ���� ��ٸ��ô�.";
}