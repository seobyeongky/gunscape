//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: mon_bug_spider.h
//
// ����: ���� - �Ź̾�!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_BUG_SPIDER_H__
#define  __MON_BUG_SPIDER_H__


#include "monster.h"


class Mon_bug_spider: public Monster
{
public:
	Mon_bug_spider(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_bug_spider();
	virtual void Death(Game_Manager* gm_); 

};

#endif  // __MON_BUG_SPIDER_H__