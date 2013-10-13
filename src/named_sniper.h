//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_sniper.h
//
// 내용: 스나이퍼
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NAMED_SNIPER_H__
#define  __NAMED_SNIPER_H__


#include "monster.h"


class Named_Sniper: public Monster
{
	int count;//잠시 모습이 보이는 시간
	int sniper; //조준
	Unit* target;
	coord_def sniper_pos;

public:
	Named_Sniper(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Named_Sniper();
	virtual bool charDraw(Game_Manager* gm_, coord_def offset, float size_);

	void SetAi(monster_state state_, Unit* head_, int level_ = 0);

	virtual bool Action_in(Game_Manager* gm_);

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
	virtual bool Special_Action(Game_Manager* gm_);
	virtual bool TargetLost();

	
	virtual bool isNamed(){return true;};	
	virtual int GetCritical(){return 100;};
	
};

#endif // __NAMED_SNIPER_H__