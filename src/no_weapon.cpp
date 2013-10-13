//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: no_weapon.cpp
//
// 내용: 무기가 없음
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "no_weapon.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "image.h"
#include "d3dx_class.h"
#include "unit.h"


No_Weapon::No_Weapon(const main_weapon_infor& infor_, coord_def pos_, int time_):
Main_Weapon(infor_, pos_, time_)
{


}
No_Weapon::~No_Weapon()
{
}
bool No_Weapon::InterfaceDraw(Direct_Manager* direct_, coord_def offset_)
{
	if(!GetEquipTexture()->Draw(offset_.x+64-600.0f/2, offset_.y-400.0f/2, 1.0f, 0.0f))
		return false;
	return true;
}
float No_Weapon::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	return -1;
}