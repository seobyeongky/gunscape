//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_teemo.cpp
//
// 내용: 직업 - 도대체 티모가 누구죠?
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "job_teemo.h"
#include "player.h"

#include "abil_escape_forget.h"
#include "abil_dex.h"
#include "abil_fast_portal.h"
#include "abil_run.h"


#include "main_weapon_list.h"
#include "sub_weapon_list.h"
#include "melee_weapon_list.h"


Job_teemo::Job_teemo():
Job_base("정찰병")
{

}

void Job_teemo::SetPlayer(Game_Manager* gm_, Player* unit)
{
	unit->SetName("정찰병");
	
	unit->GetAbility(gm_,new Abil_Escape_Forget(1));
	unit->GetAbility(gm_,new Abil_fast_portal(1));
	unit->GetAbility(gm_,new Abil_dex(1));
	unit->GetAbility(gm_,new Abil_run(1));
	
	unit->SetMainWeapon(New_Main_Weapon(MWK_DART, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_CLOAK, unit, coord_def(), -1));
	unit->SetSubWeapon(New_Sub_Weapon(SWK_TRAP, unit, coord_def(), -1));
	unit->SetMeleeWeapon(New_Melee_Weapon(MK_CLUB, coord_def(), -1));
}

const char* Job_teemo::GetInfor()
{
	return "날쌘 정찰병";
}
const char* Job_teemo::GetItemInfor()
{
	return "메인무기:독침\n보조무기:은신망토\n보조무기:덫\n근접무기:곤봉";
}
const char* Job_teemo::GetAblityInfor()
{
	return "따돌리기 1레벨:도망칠때 적을 따돌리는데 필요한 시간이 절반이 된다.\n하이패스 1레벨:포탈진입시간 50%감소. 탈출이 쉬워진다.\n날렵함 1레벨:이동속도 10% 증가\n질주 1레벨:사용시 일시적 달리기 속도 20% 증가";
}
const char* Job_teemo::GetTip()
{
	return "얍삽하게 싸우면됩니다.\n쥐처럼 쏘고 튀고 짤짤이 넣으세요. 좀비에게는 독의 데미지가 반절이 되고 로봇에게는 통하지않습니다.";
}
