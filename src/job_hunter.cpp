//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_hunter.cpp
//
// 내용: 직업 - 사냥꾼
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
Job_base("사냥꾼")
{

}

void Job_hunter::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("사냥꾼");

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
	return "동물 수렵에 능숙한 사냥꾼이다.";
}
const char* Job_hunter::GetItemInfor()
{
	return "메인무기:샷건\n보조무기:그물\n근접무기:나이프";
}
const char* Job_hunter::GetAblityInfor()
{
	return "벌레방지약 1레벨:벌레들의 인식 범위 감소\n망원경 1레벨:시야 증가\n예비탄창 1레벨:최대 탄창 1개 증가\n대쉬 1레벨:짧은 순간 앞으로 대쉬";
}
const char* Job_hunter::GetTip()
{
	return "샷건은 멀리서 쏘면 위력이 약합니다. 가까이서 모든 총알을 맞춥시다.\n그물을 맞춰서 적의 움직임을 멈추거나 대쉬를 이용해서 위기상황을 피합시다.\n장전시간이 상당히 긴 무기이므로 장전시간을 조심합시다.";
}
