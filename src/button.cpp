//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: button.cpp
//
// 내용: 스위치
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "button.h"
#include "gamemanager.h"
#include "d3dx_class.h"
#include "image.h"
#include "texture_list.h"
#include "player.h"
#include "effect_piece.h"

Button::Button(coord_def pos_):
Item(&tex_item_button, "스위치", "탈출하는데 필요한 스위치", pos_, 0), on(false), count(0)
{

}

bool Button::InforDraw(Direct_Manager* direct_, coord_def offset_)
{
	//RECT rc={(LONG)offset_.x, (LONG)offset_.y+16, (LONG)offset_.x+128, 1000};
	//direct_->GetFont()->DrawTextA(NULL,"탈출 하는 중...", -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);

	//offset_.x+=20;
	//offset_.y+=50;
	//tex_system_gauge_border.Draw(offset_.x+30.0f-direct_->GetWidth()/2,  offset_.y-direct_->GetHeight()/2, 1.0f, 0.0f);
	//float pecen_ = time/300.0f;
	//tex_system_gauge.Draw(offset_.x-17.0f + 47*pecen_-direct_->GetWidth()/2,  offset_.y-direct_->GetHeight()/2, pecen_, 1.0f, 0.0f);
	return true;
}
bool Button::Action(Game_Manager* gm_)
{
	if(!valid)		
		return true;
	if(!on && gm_->isPlayerLive())
	{
		count++;
		if(count%50==0)
			Effect_switch(gm_,GetPos(),1.0f);

		coord_def temp = gm_->GetPlayerPos();
		if(gm_->player->collution(GetPos(), 10) && !gm_->player->GetNet())
		{
			Effect(gm_, gm_->player);
		}
	}
	return false;
}
bool Button::Effect(Game_Manager* gm_, Player* unit_)
{
	on = true;
	texture = &tex_item_button2;
	return true;
}