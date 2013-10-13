//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_fling.h
//
// 내용: 플링버그!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_BUG_FLING_H__
#define  __MON_BUG_FLING_H__


#include "monster.h"


class Mon_bug_filng: public Monster
{
	bool fling;
public:
	Mon_bug_filng(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_bug_filng();
	
	virtual void MeleeDamage(Game_Manager* gm_, Unit* target_);
};

#endif // __MON_BUG_FLING_H__