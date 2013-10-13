//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: kevlar.cpp
//
// 내용: 서브아이템. 방탄복
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "kevlar.h"
#include "texture_list.h"
#include "player.h"

Sub_Kevlar::Sub_Kevlar(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "방탄복", "실탄류 데미지 30%감소", pos_, time_, user_, &tex_inter_cloth, 0, 0.0f)
{

}
Sub_Kevlar::~Sub_Kevlar()
{

}

float Sub_Kevlar::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	if(!GetEquip())
		Equip();
	else
		UnEquip();
	return 0;
}
bool Sub_Kevlar::Equip()
{
	GetPlayer()->ApplyDefense(DT_BULLET, 0.7f);
	SetEquip(true);
	return true;
}
bool Sub_Kevlar::UnEquip()
{
	GetPlayer()->ApplyDefense(DT_BULLET, 1/0.7f);
	SetEquip(false);
	return true;
}