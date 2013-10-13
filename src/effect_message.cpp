//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_piece.cpp
//
// 내용: 이펙트 - 글자 띄우기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "effect_message.h"
#include "gamemanager.h"
#include "image.h"
#include "random.h"
#include "d3dx_class.h"


Effect_Message::Effect_Message(Game_Manager* gm_, const char* message_, coord_def pos_):
Shot_base(NULL, NULL, -1, pos_, coord_def(0, -0.5f)), 
gm(gm_), message(message_), time(50), valid(true), color(D3DCOLOR_ARGB(255,randA(255), randA(255), randA(255)))
{
}



Effect_Message::Effect_Message(Game_Manager* gm_, const char* message_, coord_def pos_, D3DCOLOR color_):
Shot_base(NULL, NULL, -1, pos_, coord_def(0, -0.5f)), 
gm(gm_), message(message_), time(50), valid(true), color(color_)
{

}

Effect_Message::~Effect_Message()
{

}

bool Effect_Message::Action(Game_Manager* gm_)
{
	if(valid)
	{
		Move();
		color -= 5 << 24;

		time--;
		if(time<0)
			valid = false;
	}


	if(!valid)
	{
		return true;
	}
	return false;
}


bool Effect_Message::Draw(coord_def offset_, float size_)
{
	//어헐
	LONG x_ = (LONG)((GetX()-((LONG)offset_.x))*size_+gm->direct->GetWidth()/2);
	LONG y_ = (LONG)((GetY()-((LONG)offset_.y))*size_+gm->direct->GetHeight()/2);
	RECT rc = {(LONG)(x_-100*gm->direct->GetWR()),y_,(LONG)(x_+100*gm->direct->GetWR()),y_};
	gm->direct->GetFont()->DrawTextA(NULL, message.c_str(), -1, &rc, DT_CENTER | DT_NOCLIP, color);
	return true;
}


void Effect_simple_speak(Game_Manager* gm_, const char* message_, coord_def pos_)
{
	gm_->shot_list.push_back(new Effect_Message(gm_, message_, pos_));
}