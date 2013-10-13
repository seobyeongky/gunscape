//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_sniper.cpp
//
// 내용: 직업 - 저격수
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_sniper.h"
#include "player.h"

#include "abil_live.h"
#include "abil_sight.h"
#include "abil_shadow.h"

#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"


Job_sniper::Job_sniper():
Job_base("저격수")
{

}

void Job_sniper::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("저격수");

	unit->GetAbility(gm_,new Abil_live(1));
	unit->GetAbility(gm_,new Abil_shadow(1));
	unit->GetAbility(gm_,new Abil_sight(2));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_SNIPER, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_CLOAK, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_KNIFE, coord_def(), -1));
}

const char* Job_sniper::GetInfor()
{
	return "멀리서 적을 암살하는 저격수다.";
}

const char* Job_sniper::GetItemInfor()
{
	return "메인무기:저격라이플\n보조무기:은신망토\n근접무기:나이프";
}
const char* Job_sniper::GetAblityInfor()
{
	return "생존전문가 1레벨:다음 층으로 넘어갈때마다 체력을 10회복\n그림자걷기 1레벨:적들의 인식 범위 감소\n망원경 2레벨:시야 증가";
}
const char* Job_sniper::GetTip()
{
	return "마우스 우클릭으로 움직이지 못하지만 공격력이 2배가 되는 저격모드가 됩니다.\n적의 시야밖에서나 코너에서 미리 망토로 은신을 하고 저격모드로 적을 기다립시다.";
}