//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_message.h
//
// 내용: 이펙트 - 글자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __EFFECT_MESSAGE_H__
#define  __EFFECT_MESSAGE_H__

#include <vector>
#include <d3dx9.h>
#include "Shot_base.h"

using namespace std;

class Effect_Message: public Shot_base
{
	Game_Manager* gm;//의도하던바가 아님
	string message;
	int time;
	bool valid;
	D3DCOLOR color;

public:
	Effect_Message(Game_Manager* gm_, const char* message_, coord_def pos_);
	Effect_Message(Game_Manager* gm_, const char* message_, coord_def pos_, D3DCOLOR color_);
	virtual ~Effect_Message();
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
};

//아래는 이 Effect_Message로 낼수있는 효과들의 간략한 함수

void Effect_simple_speak(Game_Manager* gm_, const char* message_, coord_def pos_);

#endif // __EFFECT_MESSAGE_H__
