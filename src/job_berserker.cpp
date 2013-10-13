//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_berserker.cpp
//
// 내용: 직업 - 광전사
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_berserker.h"
#include "player.h"

#include "abil_health.h"
#include "abil_berserker.h"
#include "abil_whirlwind.h"
#include "abil_vampire.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"



Job_berserker::Job_berserker():
Job_base("광전사")
{

}

void Job_berserker::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("광전사");

	//unit->SetMainWeapon(New_Main_Weapon(MWK_RIFLE_PISTOL, coord_def(), -1));
	unit->GetAbility(gm_,new Abil_health(1));
	unit->GetAbility(gm_,new Abil_berserker(1));
	unit->GetAbility(gm_,new Abil_whirlwind(1));
	unit->GetAbility(gm_,new Abil_vampire(1));
	
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_AXE, coord_def(), -1));
}

const char* Job_berserker::GetInfor()
{
	return "광폭화를 사용하여 근접무기로 싸우는 광전사다.";
}
const char* Job_berserker::GetItemInfor()
{
	return "근접무기:소방도끼";
}
const char* Job_berserker::GetAblityInfor()
{
	return "맷집 1레벨:최대 체력 10증가\n광폭화 1레벨:강력한 근접 광폭화. 근접데미지에 면역(탄창 0.5개 소모)\n휠윈드 1레벨:근접 무기가 전방향을 공격하게 된다\n흡혈귀 1레벨:인간형 적에게 근접흡혈 15%";
}
const char* Job_berserker::GetTip()
{
	return "도끼만 들고 시작하지만 광폭화의 능력을 통해 강력한 근접전투가 가능해집니다.\n좀비나 벌레에겐 강하지만 총기를 사용하는 적을 상대로 한없이 약하므로 전투를 피하는게 좋습니다.";
}
