//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_ant_lion.h
//
// 내용: 개미지옥. 플레이어를 빨아들인다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_BUG_ANT_LION_H__
#define  __MON_BUG_ANT_LION_H__


#include "monster.h"


class Mon_bug_ant_lion: public Monster
{
	int tongue_delay;

	typedef struct Tongue
	{
		int state; //0은 안내밈. 1은 발사. 2는 돌아옴. 3은 걸침
		float speed;
		float angle;
		coord_def pos;
		int count;
		Unit* target;
		Tongue():state(0),speed(2),angle(0),pos(),count(0),target(NULL)
		{}
	}Tongue;
	Tongue tongue;
public:
	Mon_bug_ant_lion(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_bug_ant_lion();
	
	virtual bool charDraw(Game_Manager* gm_, coord_def offset, float size_);

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num=0);
	virtual bool TargetLost();

	virtual bool Special_Action(Game_Manager* gm_);
};

#endif // __MON_BUG_ANT_LION_H__