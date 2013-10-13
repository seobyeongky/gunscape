//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_instant_bullet.h
//
// ����: �ɷ�-�ν��Ͻ�-���ȸ��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_INSTANT_BULLET_H__
#define  __ABIL_INSTANT_BULLET_H__

#include "ability.h"

class Abil_Instant_bullet : public Ability 
{
public:
	Abil_Instant_bullet(int level_);
	virtual ~Abil_Instant_bullet();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool InstanceActive(Player* player_);
};

#endif // __ABIL_INSTANT_BULLET_H__