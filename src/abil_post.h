//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_post.h
//
// ����: ����� - ���ҹڱ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_POST_H__
#define  __ABIL_POST_H__

#include "ability.h"

class Abil_post : public Ability 
{
	int count;
	bool post;
public:
	Abil_post(int level_);
	virtual ~Abil_post();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	float GetSpeed();

	virtual bool Action(Game_Manager* gm_, Player* player_);

	virtual bool isUsing(){return post;};
	virtual bool Use(Game_Manager* gm_, Player* player_);
	virtual bool UnUse(Game_Manager* gm_, Player* player_);
};


#endif // __ABIL_POST_H__