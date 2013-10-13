//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: item_heal.cpp
//
// 내용: 힐링아이템
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "item_heal.h"
#include "player.h"
#include "texture_list.h"



Item_heal::Item_heal(coord_def pos_, int time_):
Item(&tex_item_heal, "회복키트", "피 30회복", pos_, time_)
{
}
Item_heal::~Item_heal()
{
}

bool Item_heal::Effect(Game_Manager* gm_, Player* unit_)
{
	if(unit_ && unit_->isLive() && unit_->GetHp() != (int)unit_->GetMaxHp())
	{
		int heal_ = 30;
		unit_->Heal(heal_);
		Erase();
		return true;
	}
	return false;
}