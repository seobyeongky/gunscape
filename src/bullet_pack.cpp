//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: bullet_pack.cpp
//
// 내용: 서브아이템. 탄창상자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "bullet_pack.h"
#include "texture_list.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_grenade.h"

Sub_Bullet_pack::Sub_Bullet_pack(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "탄창상자", "소모시 탄창이 가득 찬다", pos_, time_, user_, &tex_inter_box, 1, 5.0f)
{

}
Sub_Bullet_pack::~Sub_Bullet_pack()
{

}

float Sub_Bullet_pack::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{	
	User_->SuppleBullet(10.0f);
	if(!UpDownNum(-1))
	{
		GetPlayer()->DeleteSubWeapon(this, -1);
		delete this; //끝나면 이걸 지움. 제대로 동작되나?
	}
	return 0;
}