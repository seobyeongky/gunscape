//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: named_jack.h
//
// ����: �ʺ������� ��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NAME_JACK_H__
#define  __NAME_JACK_H__


#include "monster.h"


class Named_jack: public Monster
{
public:
	Named_jack(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Named_jack();

	virtual bool isNamed(){return true;};	
};

#endif // __NAME_JACK_H__