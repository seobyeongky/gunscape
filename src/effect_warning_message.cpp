//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_warning_message.cpp
//
// 내용: 최종 목적
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "effect_warning_message.h"
#include "gamemanager.h"
#include "image.h"
#include "random.h"
#include "d3dx_class.h"

Effect_warning_message::Effect_warning_message(Game_Manager* gm_, const char* message_, int time_):
Shot_base(NULL, NULL, 0, coord_def(), coord_def(), STP_TEXT),
gm(gm_), message(message_), time(time_)
{


}
Effect_warning_message::~Effect_warning_message()
{


}


bool Effect_warning_message::Action(Game_Manager* gm_)
{
	time--;
	if(time<=0)
	{
		return true;
	}
	return false;
}

bool Effect_warning_message::Draw(coord_def offset_, float size_)
{
	LONG x_ = (LONG)(gm->direct->GetWidth()/2);
	LONG y_ = (LONG)(28*gm->direct->GetHR());
	RECT rc = {(LONG)(x_-200*gm->direct->GetWR()),y_,(LONG)(x_+200*gm->direct->GetWR()),y_};
	gm->direct->GetFont()->DrawTextA(NULL, message.c_str(), -1, &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255,255,255,255));
	return false;
}
