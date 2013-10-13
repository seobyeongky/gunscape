//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_politician.cpp
//
// ����: ���� - ������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_politician.h"
#include "player.h"

#include "abil_knowledge.h"
#include "abil_bare.h"
#include "abil_health.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"


Job_politician::Job_politician():
Job_base("��ġ��")
{

}

void Job_politician::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("��ġ��");

	unit->GetAbility(gm_,new Abil_bare(1));
	unit->GetAbility(gm_,new Abil_knowledge(2));
	unit->GetAbility(gm_,new Abil_health(1));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_RIFLE_PISTOL, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_CLUB, coord_def(), -1));
}

const char* Job_politician::GetInfor()
{
	return "�񸮿� ������ ����� ��ġ���̴�.";
}

const char* Job_politician::GetItemInfor()
{
	return "���ι���:����\n��������:���";
}
const char* Job_politician::GetAblityInfor()
{
	return "�Ǽ����� 1����:���������� ���� �̼Ӱ��� ����. ������������ ������ �˹��� ��\n������� 2����:�������� �����ϴ� �ɷ� ���� �ִ�ġ 2�� ����\n���� 1����:�ִ� ü�� 10����";
}
const char* Job_politician::GetTip()
{
	return "���ٸ� ���⵵ ���� �ʹݿ� �������� ������ ���������� ��⸸���� �����Դϴ�.";
}
