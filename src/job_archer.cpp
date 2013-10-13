//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_archer.cpp
//
// ����: ���� - �ü�(�ٲٱ�)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_archer.h"
#include "player.h"

#include "abil_critical.h"
#include "abil_chaininvi.h"
#include "abil_stealth.h"
#include "abil_invisible.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"



Job_archer::Job_archer():
Job_base("ø��")
{

}

void Job_archer::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("ø��");

	unit->GetAbility(gm_,new Abil_critical(1));
	unit->GetAbility(gm_,new Abil_chaininvi(1));
	unit->GetAbility(gm_,new Abil_stealth(2));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_BOW, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_KNIFE, coord_def(), -1));
}

const char* Job_archer::GetInfor()
{
	return "���� ���̷� ���� ����� ���� �ӵ��� �ϻ��Ѵ�.";
}
const char* Job_archer::GetItemInfor()
{
	return "���ι���:Ȱ\n��������:������";
}
const char* Job_archer::GetAblityInfor()
{
	return "ġ��Ÿ 1����:��Ų ������ 15% Ȯ���� �齺��, ��弦 ����\n����Ͻ� 1����:���� ���̸� 3�ʰ� ����\n���ϰ��� 2����:������ �ƴҶ� ������ �ݹ��� ��Ű���ʴ� �ð��� ����";
}
const char* Job_archer::GetTip()
{
	return "���ϰ����� �̿��� ������ �ִ� ���� �绡�� �ϻ��ϴµ� �����սô�.\n���� ��� ����Ͻ��� ȿ���� ��� �ϻ��� �õ��� �� �ֽ��ϴ�.\n�ϻ쿡 ���� �ð��� �־����������Ƿ� Ȱ�� �̿��� �ϻ��� ���������� �̿��սô�.\nȤ�� ��Ų���̶� ġ��Ÿ�� ȿ���� ����� �� �ֽ��ϴ�.";
}
