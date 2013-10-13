//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: trap.cpp
//
// ����: ���������. ��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "trap.h"
#include "texture_list.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_trap.h"
#include "sound.h"

Sub_Trap::Sub_Trap(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "��", "����ü���� ���� ��������\n������ ���ο츦 �Ŵ� ��\n�κ����� �������ʾƺ��δ�", pos_, time_, user_, &tex_inter_trap, 6, 5.0f)
{

}
Sub_Trap::~Sub_Trap()
{

}

float Sub_Trap::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	float x_ = start_.x + cos(angle_)*15.0f;
	float y_ = start_.y + sin(angle_)*15.0f;
	gm_->shot_list.push_back(new Shot_trap(&tex_trap, User_, 0.2f, 150, 70, 1200, team_, coord_def(x_,y_)));
	if(!UpDownNum(-1))
	{
		GetPlayer()->DeleteSubWeapon(this, -1);
		delete this; //������ �̰� ����. ����� ���۵ǳ�?
	}
	return 10;
}