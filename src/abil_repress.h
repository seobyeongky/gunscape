//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_repress.h
//
// ����: �ɷ�-�ʱ�����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_REPRESS_H__
#define  __ABIL_REPRESS_H__

#include "ability.h"

class Abil_repress : public Ability 
{
public:
	Abil_repress(int level_);
	virtual ~Abil_repress();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	
	float Getattack();
	
	virtual bool EnterMap(Game_Manager* gm_, Player* player_, int level_);
};

#endif // __ABIL_REPRESS_H__