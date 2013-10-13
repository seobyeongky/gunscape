//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: effect_last_message.h
//
// ����: �������������� �����̴�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __EFFECT_LAST_MESSAGE_H__
#define  __EFFECT_LAST_MESSAGE_H__

#include "Shot_base.h"


class Effect_last_message: public Shot_base
{
	Game_Manager* gm;//�ǵ��ϴ��ٰ� �ƴ�

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