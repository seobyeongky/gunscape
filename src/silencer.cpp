//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: silencer.cpp
//
// 내용: 서브아이템. 소음기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "silencer.h"
#include "texture_list.h"
#include "player.h"

Sub_Silencer::Sub_Silencer(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "소음기", "주무기 소음 30%감소", pos_, time_, user_, &tex_inter_silencer, 0, 0.0f)
{

}
Sub_Silencer::~Sub_Silencer()
{

}

float Sub_Silencer::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	if(!GetEquip())
		Equip();
	else
		UnEquip();
	return 0;
}
bool Sub_Silencer::Equip()
{
	GetPlayer()->ApplySilencer(0.7f);
	SetEquip(true);
	return true;
}
bool Sub_Silencer::UnEquip()
{
	GetPlayer()->ApplySilencer(1/0.7f);
	SetEquip(false);
	return true;
}