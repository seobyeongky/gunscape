//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: box.h
//
// ����: ���޻��� Ŭ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __BOX_H__
#define  __BOX_H__

#include "unit.h"


class Box: public Unit
{
	int level; //�� ���ڰ� ���� ��

public:
	Box(Texture* texture_, coord_def pos_, int level_);
	virtual ~Box();

	virtual bool Action_in(Game_Manager* gm_);
	virtual bool isPlayer(){return false;};
	virtual bool isNonLife(){return true;};
	virtual bool TargetLost(){return false;};
	virtual bool TargetBlinding(){return false;};
	virtual bool InvisibleLost(coord_def c){return false;};

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0){return false;};

	virtual bool DropItem(Game_Manager* gm_);
};


#endif // __BOX_H__


