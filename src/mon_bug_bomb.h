//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_bomb.h
//
// 내용: 몬스터 - 폭탄충
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_BUG_BOMB_H__
#define  __MON_BUG_BOMB_H__


#include "monster.h"


class Mon_bug_bomb: public Monster
{
public:
	Mon_bug_bomb(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_bug_bomb();
	virtual void Death(Game_Manager* gm_); 

	virtual bool Melee(Game_Manager* gm_);

	void Bomb(Game_Manager* gm_);
};

#endif // __MON_BUG_BOMB_H__