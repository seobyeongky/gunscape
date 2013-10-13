//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: item.cpp
//
// 내용: 아이템 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "item.h"
#include "image.h"
#include "texture_list.h"
#include "unit.h"
#include "gamemanager.h"

char Item::temp_str[32] = "";

Item::Item(Texture* texture_, const char* name_, const char* infor_, coord_def pos_, int time_):
texture(texture_), name(name_), infor(infor_), pos(pos_), time(time_), valid(true)
{
}
Item::~Item()
{

}
bool Item::Draw(coord_def offset, float size_)
{
	Texture* circle_ = NULL;
	switch(GetItemType())
	{
	case IT_MAIN_WEAPON:
		circle_ = &tex_item_color_red;
		break;
	case IT_SUB_WEAPON:
		circle_ = &tex_item_color_yellow;
		break;
	case IT_MELEE:
		circle_ = &tex_item_color_blue;
		break;
	case IT_INSTANT:
		circle_ = &tex_item_color_green;
		break;
	default:
		return texture->Draw((pos.x-offset.x)*size_, (pos.y-offset.y)*size_, size_, 0.0f);
	}
	if(!circle_->Draw((pos.x-offset.x)*size_, (pos.y-offset.y)*size_, size_, 0.0f))
		return false;
	return texture->Draw((pos.x-offset.x)*size_, (pos.y-offset.y)*size_, size_, 0.0f);
}

bool Item::Action(Game_Manager* gm_)
{
	if(!valid)
		return true;

	if(time>0)
	{
		time--;
	}
	if(!time)
		return true;
	return false;
}