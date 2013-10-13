//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_marathoner.h
//
// ����: �ɷ�-�ִ�ü������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_MARATHONER_H__
#define  __ABIL_MARATHONER_H__

#include "ability.h"

class Abil_marathoner : public Ability 
{

public:
	Abil_marathoner(int level_);
	virtual ~Abil_marathoner();

	virtual Ability* Clone(int level_);

	float GetSp();

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_MARATHONER_H__