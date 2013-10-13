//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_politician.cpp
//
// 내용: 직업 - 추적자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_politician.h"
#include "player.h"

#include "abil_knowledge.h"
#include "abil_bare.h"
#include "abil_health.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"


Job_politician::Job_politician():
Job_base("정치인")
{

}

void Job_politician::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("정치인");

	unit->GetAbility(gm_,new Abil_bare(1));
	unit->GetAbility(gm_,new Abil_knowledge(2));
	unit->GetAbility(gm_,new Abil_health(1));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_RIFLE_PISTOL, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_CLUB, coord_def(), -1));
}

const char* Job_politician::GetInfor()
{
	return "비리와 뇌물로 얼룩진 정치인이다.";
}

const char* Job_politician::GetItemInfor()
{
	return "메인무기:권총\n근접무기:곤봉";
}
const char* Job_politician::GetAblityInfor()
{
	return "맨손전투 1레벨:근접전투에 의한 이속감소 절반. 근접데미지를 받으면 넉백을 줌\n배경지식 2레벨:레벨업시 선택하는 능력 갯수 최대치 2개 증가\n맷집 1레벨:최대 체력 10증가";
}
const char* Job_politician::GetTip()
{
	return "별다른 무기도 없고 초반에 약하지만 갈수록 강력해지는 대기만성형 직업입니다.";
}
