//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: mon_bug_beetle.h
//
// ����: ǳ����. ������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MON_BUG_BEETLE_H__
#define  __MON_BUG_BEETLE_H__


#include <list>
#include <d3dx9.h>
#include "monster.h"

using namespace std;


class Mon_bug_beetle: public Monster
{
	int rush_delay;

	int rush; //1�̻��� ���� �غ����(���ڰ� ���� �ð�). 0�� ����. -1�� �Ϲݻ��´�.(�����ϱ�)

	float rush_speed;

	int count;

	typedef struct Unit_Infor
	{
		Unit* pointer;
		coord_def pos_dif;
		Unit_Infor(Unit* pointer_, coord_def pos_dif_):pointer(pointer_),pos_dif(pos_dif_){}
	}Unit_Infor;


	list<Unit_Infor> hit_unit;
public:
	Mon_bug_beetle(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Mon_bug_beetle();

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
	virtual bool TargetLost();

	virtual bool Special_Action(Game_Manager* gm_);
};

#endif // __MON_BUG_BEETLE_H__