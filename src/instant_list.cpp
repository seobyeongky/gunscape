//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: instant_list.cpp
//
// 내용: 즉시 아이템
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "instant_list.h"
#include "item_heal.h"
#include "item_bullet.h"


Item* New_Instant(Instant_Kind kind_, coord_def pos_, int time_)
{
	Item* temp = NULL;
	switch(kind_)
	{
	case IK_NONE:
	case IK_HEAL:
	default:
		temp = new Item_heal(pos_, time_);
	break;
	case IK_BULLET:
		temp = new Item_bullet(pos_, time_);
	break;
	}
	return temp;
}