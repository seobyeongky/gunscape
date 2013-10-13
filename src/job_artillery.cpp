//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_artillery.cpp
//
// 내용: 직업 - 포병
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_artillery.h"
#include "player.h"

#include "abil_bulletup.h"
#include "abil_antiexplosion.h"
#include "abil_health.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"



Job_artillery::Job_artillery():
Job_base("포병")
{

}

void Job_artillery::SetPlayer(Game_Manager* gm_, Player* unit)
{	
	unit->SetName("포병");

	unit->GetAbility(gm_,new Abil_bulletup(1));
	unit->GetAbility(gm_,new Abil_antiexplosion(1));
	unit->GetAbility(gm_,new Abil_health(2));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_BAZOOKA, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_GRENADE, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_CLUB, coord_def(), -1));
}

const char* Job_artillery::GetInfor()
{
	return "커다란 바주카를 들고 다니는 병사다.";
}
const char* Job_artillery::GetItemInfor()
{
	return "메인무기:바주카\n보조무기:수류탄\n근접무기:곤봉";
}
const char* Job_artillery::GetAblityInfor()
{
	return "탄창증가 1레벨:최대탄수 20%증가\n성형작약 1레벨:폭발데미지 15% 감소. 자폭시 15% 추가감소\n맷집 2레벨:최대 체력 25증가";
}
const char* Job_artillery::GetTip()
{
	return "강력한 한방을 가진 직업이지만 느린 장전속도와 폭발로 인한 자폭데미지는 큰 위험입니다.\n항상 남은 탄수와 자폭을 염두에 두면서 스플래시를 최대한 이용하여 싸웁시다.";
}