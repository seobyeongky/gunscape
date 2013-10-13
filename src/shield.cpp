//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: shield.cpp
//
// 내용: 서브아이템. 전투방패
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "shield.h"
#include "texture_list.h"
#include "player.h"

Sub_Shield::Sub_Shield(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "전투방패", "모든 데미지를 20%감소\n이동속도가 15%감소", pos_, time_, user_, &tex_inter_sheild, 0, 0.0f)
{

}
Sub_Shield::~Sub_Shield()
{

}

float Sub_Shield::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	if(!GetEquip())
		Equip();
	else
		UnEquip();
	return 0;
}
bool Sub_Shield::Equip()
{
	GetPlayer()->ApplyDefense(DT_ALL, 0.8f);
	GetPlayer()->ApplySpeed(0.85f);
	SetEquip(true);
	return true;
}
bool Sub_Shield::UnEquip()
{
	GetPlayer()->ApplyDefense(DT_ALL, 1/0.8f);
	GetPlayer()->ApplySpeed(1/0.85f);
	SetEquip(false);
	return true;
}