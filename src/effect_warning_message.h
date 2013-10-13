//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_warning_message.h
//
// 내용: 마지막층에서의 목적이다
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __EFFECT_WARNING_MESSAGE_H__
#define  __EFFECT_WARNING_MESSAGE_H__

#include <vector>
#include <d3dx9.h>
#include "Shot_base.h"

using namespace std;


class Effect_warning_message: public Shot_base
{
	Game_Manager* gm;//의도하던바가 아님

	string message;
	int time;
	
public:
	Effect_warning_message(Game_Manager* gm_, const char* message_, int time_);
	virtual ~Effect_warning_message();
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);

};


#endif // __EFFECT_WARNING_MESSAGE_H__