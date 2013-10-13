//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: named_assasin.h
//
// ����: ��ڸ� �����ض�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_ASSASIN_H__
#define  __MON_ASSASIN_H__


#include "monster.h"


class Named_Assasin: public Monster
{
	int count;//��� ����� ���̴� �ð�

public:
	Named_Assasin(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Named_Assasin();
	
	virtual bool Special_Action(Game_Manager* gm_);


	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
	
	virtual bool isNamed(){return true;};

	virtual void MeleeDamage(Game_Manager* gm_, Unit* target_);
};

#endif // __MON_ASSASIN_H__