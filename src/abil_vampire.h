//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_vampire.h
//
// ����: �ɷ�-�ΰ��� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_VAMPIRE_H__
#define  __ABIL_VAMPIRE_H__

#include "ability.h"

class Abil_vampire : public Ability 
{

public:
	Abil_vampire(int level_);
	virtual ~Abil_vampire();

	virtual Ability* Clone(int level_);

	float GetVamp();

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_VAMPIRE_H__