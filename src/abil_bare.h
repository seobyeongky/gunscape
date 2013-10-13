//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_bare.h
//
// ����: �ɷ�-�Ǽ�����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_BARE_H__
#define  __ABIL_BARE_H__

#include "ability.h"

class Abil_bare : public Ability 
{
public:
	Abil_bare(int level_);
	virtual ~Abil_bare();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_BARE_H__