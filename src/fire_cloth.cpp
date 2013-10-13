//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: kevlar.cpp
//
// 내용: 서브아이템. 방화복
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "fire_cloth.h"
#include "texture_list.h"
#include "player.h"

Sub_Fire_Cloth::Sub_Fire_Cloth(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "방화복", "화염 데미지 40%감소", pos_, time_, user_, &tex_inter_cloth, 0, 0.0f)
{

}
Sub_Fire_Cloth::~Sub_Fire_Cloth()
{

}

float Sub_Fire_Cloth::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	if(!GetEquip())
		Equip();
	else
		UnEquip();
	return 0;
}
bool Sub_Fire_Cloth::Equip()
{
	GetPlayer()->ApplyDefense(DT_BULLET, 0.6f);
	SetEquip(true);
	return true;
}
bool Sub_Fire_Cloth::UnEquip()
{
	GetPlayer()->ApplyDefense(DT_FIRE, 1/0.6f);
	SetEquip(false);
	return true;
}