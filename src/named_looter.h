//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: named_looter.h
//
// ����: �ɷ� ������ӵ� ��Ż��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NAME_LOOTER_H__
#define  __NAME_LOOTER_H__


#include "monster.h"


class Named_looter: public Monster
{
public:
	Named_looter(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Named_looter();

	virtual bool isNamed(){return true;};	
};

#endif // __NAME_JACK_H__