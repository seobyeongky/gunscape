//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: effect_message.h
//
// ����: ����Ʈ - ����
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
	Game_Manager* gm;//�ǵ��ϴ��ٰ� �ƴ�
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

//�Ʒ��� �� Effect_Message�� �����ִ� ȿ������ ������ �Լ�

void Effect_simple_speak(Game_Manager* gm_, const char* message_, coord_def pos_);

#endif // __EFFECT_MESSAGE_H__
