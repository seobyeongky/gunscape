//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_stalker.cpp
//
// ����: ���� - ������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_stalker.h"
#include "player.h"

#include "abil_stealth.h"
#include "abil_dex.h"
#include "abil_fast_portal.h"
#include "abil_run.h"


#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"


Job_stalker::Job_stalker():
Job_base("������")
{

}

void Job_stalker::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("������");

	unit->GetAbility(gm_,new Abil_stealth(1));
	unit->GetAbility(gm_,new Abil_dex(2));
	unit->GetAbility(gm_,new Abil_run(1));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_RIFLE_PISTOL, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_SMOKE_BOMB, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_CLUB, coord_def(), -1));
}

const char* Job_stalker::GetInfor()
{
	return "���� ���� �ڶ��ϴ� �߰��ڴ�.";
}
const char* Job_stalker::GetItemInfor()
{
	return "���ι���:����\n��������:����ź\n��������:���";
}
const char* Job_stalker::GetAblityInfor()
{
	return "���ϰ��� 1����:������ �ƴϸ� ������ ��ٷ� ��Ű������\n������ 2����:�̵��ӵ� 20% ����\n���� 1����:���� �Ͻ��� �޸��� �ӵ� 20% ����";
}
const char* Job_stalker::GetTip()
{
	return "�ſ� ���� �̵��ӵ��� �ִ��� Ȱ���սô�. �ް���ġ�鼭 �ο�°� �����ϴ�.\nª�� �ڳʶ�� ���ֿ� ���ϰ������� ������ ��Ű�� �ʰ� ���������� �ֽ��ϴ�.";
}
