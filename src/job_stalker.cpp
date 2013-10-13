//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_stalker.cpp
//
// 내용: 직업 - 추적자
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
Job_base("추적자")
{

}

void Job_stalker::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("추적자");

	unit->GetAbility(gm_,new Abil_stealth(1));
	unit->GetAbility(gm_,new Abil_dex(2));
	unit->GetAbility(gm_,new Abil_run(1));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_RIFLE_PISTOL, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_SMOKE_BOMB, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_CLUB, coord_def(), -1));
}

const char* Job_stalker::GetInfor()
{
	return "빠른 발을 자랑하는 추격자다.";
}
const char* Job_stalker::GetItemInfor()
{
	return "메인무기:권총\n보조무기:연막탄\n근접무기:곤봉";
}
const char* Job_stalker::GetAblityInfor()
{
	return "도둑걸음 1레벨:정면이 아니면 적에게 곧바로 들키지않음\n날렵함 2레벨:이동속도 20% 증가\n질주 1레벨:사용시 일시적 달리기 속도 20% 증가";
}
const char* Job_stalker::GetTip()
{
	return "매우 빠른 이동속도를 최대한 활용합시다. 뒷걸음치면서 싸우는게 좋습니다.\n짧은 코너라면 질주와 도둑걸음으로 적에게 들키지 않고 지나갈수도 있습니다.";
}
