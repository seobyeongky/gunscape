//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_pyro.cpp
//
// 내용: 직업 - 방화범
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_pyro.h"
#include "player.h"

#include "abil_speedreload.h"
#include "abil_fire.h"
#include "abil_health.h"


#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"




Job_pyro::Job_pyro():
Job_base("방화범")
{

}

void Job_pyro::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("방화범");

	unit->GetAbility(gm_,new Abil_fire(1));
	unit->GetAbility(gm_,new Abil_speedreload(1));
	unit->GetAbility(gm_,new Abil_health(2));

	unit->SetMainWeapon(New_Main_Weapon(MWK_FLAME_THROWER, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_AXE, coord_def(), -1));
}

const char* Job_pyro::GetInfor()
{
	return "방화 그 자체를 즐기는 방화범이다.";
}
const char* Job_pyro::GetItemInfor()
{
	return "메인무기:화염방사기\n근접무기:소방도끼";
}
const char* Job_pyro::GetAblityInfor()
{
	return "지옥불 1레벨:화염방어력 25%증가\n스피드리로드 1레벨:장전 속도 20%감소\n맷집 2레벨:최대 체력 25증가";
}
const char* Job_pyro::GetTip()
{
	return "화염방사기는 사거리가 짧으므로 원거리 적이면 코너를 이용하여 적과 거리를 줄입시다.\n화염방사기가 적을 관통하는 것을 최대한 활용하고 매우 긴 장전시간을 조심합시다.";
}
