//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_bloodreload.h
//
// ����: �ɷ�-��������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_BLOODRELOAD_H__
#define  __ABIL_BLOODRELOAD_H__

#include "ability.h"

class Abil_bloodreload : public Ability 
{

public:
	Abil_bloodreload(int level_);
	virtual ~Abil_bloodreload();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	int GetCost();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_BLOODRELOAD_H__