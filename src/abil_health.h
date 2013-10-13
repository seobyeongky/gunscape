//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_health.h
//
// ����: �ɷ�-�ִ�ü������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_HEALTH_H__
#define  __ABIL_HEALTH_H__

#include "ability.h"

class Abil_health : public Ability 
{

public:
	Abil_health(int level_);
	virtual ~Abil_health();

	virtual Ability* Clone(int level_);

	int GetHp();

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_HEALTH_H__