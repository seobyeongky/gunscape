//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_stalker.cpp
//
// 내용: 직업 - 추적자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_assassin.h"
#include "player.h"

#include "abil_invisible.h"
#include "abil_knife.h"
#include "abil_state_view.h"
#include "abil_sleep.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"


Job_assassin::Job_assassin():
Job_base("암살자")
{

}

void Job_assassin::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("암살자");

	unit->GetAbility(gm_,new Abil_knife(1));
	unit->GetAbility(gm_,new Abil_invisible(2));
	unit->GetAbility(gm_,new Abil_state_view(1));

	unit->SetMainWeapon(New_Main_Weapon(MWK_RIFLE_PISTOL_BIG, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_SILENCER, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_KNIFE, coord_def(), -1));
}

const char* Job_assassin::GetInfor()
{
	return "적을 몰래 기습하는 암살자다.";
}
const char* Job_assassin::GetItemInfor()
{
	return "메인무기:데저트 이글\n보조무기:소음기\n근접무기:나이프";
}
const char* Job_assassin::GetAblityInfor()
{
	return "암살기술 1레벨:모든 백스탭, 헤드샷 데미지 1.25배\n직감 1레벨:적의 상태와 위험요소를 알아챌 수 있다\n은신 2레벨:사용시 은신상태, 이속감소(탄창 0.5개 소모)";
}

const char* Job_assassin::GetTip()
{
	return "몬스터 위의 표시가 ? 모양이라면 아직 플레이어를 눈치 못 챈 상태입니다.\n적이 이쪽을 눈치못챈 상태에서 나이프로 공격시 백스탭으로 죽일 수 있습니다.\n적의 시야 밖에서 은신상태로 접근해야합니다. 다만, 시야 정면이면 은신도 들킬 수 있습니다.\n이미 들킨 상대나 적주변에 빨간 원이 없으면 백스탭 한방에 안 죽는 적이므로 권총으로 공격합시다.";
}