//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_shadow.h
//
// ����: �ɷ�-�׸��ڰȱ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_SHADOW_H__
#define  __ABIL_SHADOW_H__

#include "ability.h"

class Abil_shadow : public Ability 
{
public:
	Abil_shadow(int level_);
	virtual ~Abil_shadow();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	float GetValue();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_SHADOW_H__