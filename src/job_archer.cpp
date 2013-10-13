//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_archer.cpp
//
// 내용: 직업 - 궁수(바꾸기)
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
Job_base("첩자")
{

}

void Job_archer::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("첩자");

	unit->GetAbility(gm_,new Abil_critical(1));
	unit->GetAbility(gm_,new Abil_chaininvi(1));
	unit->GetAbility(gm_,new Abil_stealth(2));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_BOW, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_KNIFE, coord_def(), -1));
}

const char* Job_archer::GetInfor()
{
	return "적들 사이로 몰래 숨어들어서 빠른 속도로 암살한다.";
}
const char* Job_archer::GetItemInfor()
{
	return "메인무기:활\n근접무기:나이프";
}
const char* Job_archer::GetAblityInfor()
{
	return "치명타 1레벨:들킨 적에도 15% 확률로 백스텝, 헤드샷 가능\n연쇄암습 1레벨:적을 죽이면 3초간 은신\n도둑걸음 2레벨:정면이 아닐때 적에게 금방은 들키지않는 시간이 증가";
}
const char* Job_archer::GetTip()
{
	return "도둑걸음을 이용해 가까이 있는 적을 재빨리 암살하는데 성공합시다.\n이후 얻는 연쇄암습의 효과로 계속 암살을 시도할 수 있습니다.\n암살에 많은 시간이 주어지지않으므로 활을 이용한 암살을 적극적으로 이용합시다.\n혹시 들킨적이라도 치명타의 효과를 기대할 수 있습니다.";
}
