//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_dex.h
//
// ����: �ɷ�-������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_DEX_H__
#define  __ABIL_DEX_H__

#include "ability.h"

class Abil_dex : public Ability 
{


	float GetSpeed();
public:
	Abil_dex(int level_);
	virtual ~Abil_dex();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_DEX_H__