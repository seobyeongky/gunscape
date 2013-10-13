//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_vaccine.h
//
// ����: �ɷ�-���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_VACCINE_H__
#define  __ABIL_VACCINE_H__

#include "ability.h"

class Abil_vaccine : public Ability 
{

public:
	Abil_vaccine(int level_);
	virtual ~Abil_vaccine();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_VACCINE_H__