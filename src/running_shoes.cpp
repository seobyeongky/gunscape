//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: running_shoes.cpp
//
// 내용: 서브아이템. 런닝슈즈
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "running_shoes.h"
#include "texture_list.h"
#include "player.h"

Sub_Running_Shoes::Sub_Running_Shoes(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "런닝슈즈", "이동속도가 10%증가", pos_, time_, user_, &tex_inter_shoes, 0, 0.0f)
{

}
Sub_Running_Shoes::~Sub_Running_Shoes()
{

}

float Sub_Running_Shoes::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	if(!GetEquip())
		Equip();
	else
		UnEquip();
	return 0;
}
bool Sub_Running_Shoes::Equip()
{
	GetPlayer()->ApplySpeed(1.1f);
	SetEquip(true);
	return true;
}
bool Sub_Running_Shoes::UnEquip()
{
	GetPlayer()->ApplySpeed(1/1.1f);
	SetEquip(false);
	return true;
}