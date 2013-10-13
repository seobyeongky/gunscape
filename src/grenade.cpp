//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: grenade.cpp
//
// ����: ���������. ����ź
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "grenade.h"
#include "texture_list.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_grenade.h"

Sub_Grenade::Sub_Grenade(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "����ź", "������ ���÷��ø�\n���� ����ź", pos_, time_, user_, &tex_inter_bomb, 2, 5.0f)
{

}
Sub_Grenade::~Sub_Grenade()
{

}

float Sub_Grenade::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float distan_ = distan_coord(start_, pos_);
	coord_def target_ = pos_;
	if(distan_ > 100)
	{
		coord_def temp_ = target_ - start_;
		temp_ = temp_/distan_*100.0f;
		target_ = temp_ + start_;
	}
	float angle_ = GetAngleToTarget(start_, pos_);
	gm_->shot_list.push_back(new Shot_grenade(&tex_grenade, User_, 50, 100, 3, 6, 30, false, team_, start_, target_));
	if(!UpDownNum(-1))
	{
		GetPlayer()->DeleteSubWeapon(this, -1);
		delete this; //������ �̰� ����. ����� ���۵ǳ�?
	}
	return 0;
}