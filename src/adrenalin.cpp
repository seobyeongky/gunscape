//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: adrenalin.cpp
//
// ����: ���������. �Ƶ巹����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "adrenalin.h"
#include "texture_list.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_grenade.h"

Sub_Adrenalin::Sub_Adrenalin(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "�Ƶ巹����", "���� 30�ʰ�\n���ݼӵ� 100%����", pos_, time_, user_, &tex_inter_drug, 1, 5.0f)
{

}
Sub_Adrenalin::~Sub_Adrenalin()
{

}

float Sub_Adrenalin::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{	
	User_->AttackSpeedApply(2.0f,1800,ABK_ADRENALIN);
	User_->StateApply("�Ƶ巹����",1800);
	if(!UpDownNum(-1))
	{
		GetPlayer()->DeleteSubWeapon(this, -1);
		delete this; //������ �̰� ����. ����� ���۵ǳ�?
	}
	return 0;
}