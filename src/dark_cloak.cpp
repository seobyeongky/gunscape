//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: dark_cloak.cpp
//
// ����: ���������. ������ �������� ����ȭ���ִ� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "dark_cloak.h"
#include "texture_list.h"
#include "gamemanager.h"
#include "player.h"

Sub_Cloak::Sub_Cloak(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "���Ÿ���", "���ݰ� �̵��� ���ϸ�\n������°� �ȴ�", pos_, time_, user_, &tex_inter_cloak, 0, 0.0f)
{

}
Sub_Cloak::~Sub_Cloak()
{

}

float Sub_Cloak::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	if(!GetEquip())
		Equip();
	else
		UnEquip();
	return 0;
}
bool Sub_Cloak::Equip()
{
	SetEquip(true);
	return true;
}
bool Sub_Cloak::UnEquip()
{
	GetPlayer()->SetInvisible(0);
	SetEquip(false);
	return true;
}
void Sub_Cloak::Passive(Game_Manager* gm_, Player* unit_, bool current_)
{
	if(GetEquip())
	{
		int time = unit_->GetNoneMoveCount();
		if(time>60)
		{
			int alpha = (time - 60)*10;
			unit_->SetInvisible(min(255,alpha));
			if(time == 85)
			{				
				gm_->InvisibleLost(unit_->GetPos());
			}
		}
		else
			unit_->SetInvisible(0);
	}
}