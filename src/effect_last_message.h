//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_last_message.h
//
// 내용: 마지막층에서의 목적이다
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __EFFECT_LAST_MESSAGE_H__
#define  __EFFECT_LAST_MESSAGE_H__

#include "Shot_base.h"


class Effect_last_message: public Shot_base
{
	Game_Manager* gm;//의도하던바가 아님

	int left_num;
	int count;
	int clear;
	
public:
	Effect_last_message(Game_Manager* gm_);
	virtual ~Effect_last_message();
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);

};


#endif // __EFFECT_LAST_MESSAGE_H__