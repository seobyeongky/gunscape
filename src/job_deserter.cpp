//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_deserter.cpp
//
// 내용: 직업 - 탈영병
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_deserter.h"
#include "player.h"

#include "abil_health.h"
#include "abil_bulletbonus.h"
#include "abil_escape_forget.h"
#include "abil_moonwalk.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"



Job_deserter::Job_deserter():
Job_base("탈영병")
{

}

void Job_deserter::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("탈영병");

	unit->GetAbility(gm_,new Abil_health(1));
	unit->GetAbility(gm_,new Abil_bulletbonus(1));
	unit->GetAbility(gm_,new Abil_moonwalk(1));
	unit->GetAbility(gm_,new Abil_Escape_Forget(1));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_ASSAUL_RIFLE, coord_def(), -1));
	//unit->SetMainWeapon(New_Main_Weapon(MWK_HEAVY, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_KEVLAR, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_KNIFE, coord_def(), -1));
}

const char* Job_deserter::GetInfor()
{
	return "무기를 무장한채로 군대를 탈영한 병사다.";
}
const char* Job_deserter::GetItemInfor()
{
	return "메인무기:돌격소총\n보조무기:방탄복\n근접무기:나이프";
}
const char* Job_deserter::GetAblityInfor()
{
	return "맷집 1레벨:최대 체력 10증가\n물자보충 1레벨:다음 층으로 넘어갈때마다 탄창 1개를 얻음\n문워크 1레벨:뒷걸음 속도 패널티 50%감소\n따돌리기 1레벨:도망칠때 적을 따돌리는데 필요한 시간이 절반이 된다.";
}
const char* Job_deserter::GetTip()
{
	return "기본적인 직업입니다.";
}
