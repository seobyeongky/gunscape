//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: mon_stalker.h
//
// ����: ������ ��(ai�� �ٸ� ���̴�.)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_STALKER_H__
#define  __MON_STALKER_H__


#include "monster.h"


class Mon_stalker: public Monster
{
	bool run;
	int stamina;
	int run_delay;

public:
	Mon_stalker(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_stalker();
	
	virtual void SetAi(monster_state state_, Unit* head_ = NULL, int level_ = 0);
	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
	virtual bool Special_Action(Game_Manager* gm_);
};

#endif // __MON_STALKER_H__