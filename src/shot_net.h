//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: Shot_net.h
//
// ����: �׹���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_NET_H__
#define  __SHOT_NET_H__

#include "Shot_base.h"



class Shot_net: public Shot_base
{
	int net_time;
	float distance;
	bool valid;
	const float angle;
	const float const_speed;
public:
	Shot_net(Texture* texture_, Unit* unit_, int net_time_, int team_, coord_def pos_, float angle_, float speed_, float distance_);
	virtual ~Shot_net();
	virtual char* GetName(){return "�׹�";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
};

#endif // __SHOT_NET_H__
