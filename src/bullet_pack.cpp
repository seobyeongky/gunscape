//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: bullet_pack.cpp
//
// ����: ���������. źâ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "bullet_pack.h"
#include "texture_list.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_grenade.h"

Sub_Bullet_pack::Sub_Bullet_pack(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "źâ����", "�Ҹ�� źâ�� ���� ����", pos_, time_, user_, &tex_inter_box, 1, 5.0f)
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
		delete this; //������ �̰� ����. ����� ���۵ǳ�?
	}
	return 0;
}