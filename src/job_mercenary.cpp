//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_mercenary.cpp
//
// 내용: 직업 - 용병
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_mercenary.h"
#include "player.h"

#include "abil_health.h"
#include "abil_live.h"
#include "abil_vampire.h"
#include "abil_murder.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"



Job_Mercenary::Job_Mercenary():
Job_base("용병")
{

}

void Job_Mercenary::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("용병");

	unit->GetAbility(gm_,new Abil_health(1));
	unit->GetAbility(gm_,new Abil_live(1));
	unit->GetAbility(gm_,new Abil_vampire(1));
	unit->GetAbility(gm_,new Abil_murder(1));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_ASSAUL_RIFLE, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_AXE, coord_def(), -1));
}

const char* Job_Mercenary::GetInfor()
{
	return "돈을 받고 싸우는 용병이다";
}
const char* Job_Mercenary::GetItemInfor()
{
	return "메인무기:돌격소총\n근접무기:소방도끼";
}
const char* Job_Mercenary::GetAblityInfor()
{
	return "맷집 1레벨:최대 체력 10증가\n생존전문가 1레벨:다음 층으로 넘어갈때마다 체력을 10회복\n흡혈귀 1레벨:인간형 적에게 근접흡혈 15%\n청부살인 1레벨:인간을 죽일때마다 체력 1회복";
}
const char* Job_Mercenary::GetTip()
{
	return "체력회복과 관련된 능력들로 무장된 용병입니다.\n체력능력을 기반으로 높은 생존력으로 진행해나갑니다.";
}
