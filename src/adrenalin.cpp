//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: adrenalin.cpp
//
// 내용: 서브아이템. 아드레날린
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "adrenalin.h"
#include "texture_list.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_grenade.h"

Sub_Adrenalin::Sub_Adrenalin(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "아드레날린", "사용시 30초간\n공격속도 100%증가", pos_, time_, user_, &tex_inter_drug, 1, 5.0f)
{

}
Sub_Adrenalin::~Sub_Adrenalin()
{

}

float Sub_Adrenalin::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{	
	User_->AttackSpeedApply(2.0f,1800,ABK_ADRENALIN);
	User_->StateApply("아드레날린",1800);
	if(!UpDownNum(-1))
	{
		GetPlayer()->DeleteSubWeapon(this, -1);
		delete this; //끝나면 이걸 지움. 제대로 동작되나?
	}
	return 0;
}