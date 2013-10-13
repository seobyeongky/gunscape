//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: item_bullet.cpp
//
// ����: źâ������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "item_bullet.h"
#include "player.h"
#include "texture_list.h"



Item_bullet::Item_bullet(coord_def pos_, int time_):
Item(&tex_item_bullet, "źâ", "źâ 1�� ����", pos_, time_)
{
}
Item_bullet::~Item_bullet()
{
}

bool Item_bullet::Effect(Game_Manager* gm_, Player* unit_)
{
	if(unit_ && unit_->isLive() && unit_->GetBullet() != unit_->GetMaxBullet())
	{
		unit_->SuppleBullet(1.0f);
		Erase();
		return true;
	}
	return false;
}