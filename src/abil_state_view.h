//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_state_view.h
//
// ����: �ɷ�-����Ȯ��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_STATE_VIEW_H__
#define  __ABIL_STATE_VIEW_H__

#include "ability.h"

class Abil_state_view : public Ability 
{
public:
	Abil_state_view(int level_);
	virtual ~Abil_state_view();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);

	virtual bool EnterMap(Game_Manager* gm_, Player* player_, int level_);
};

#endif // __ABIL_STATE_VIEW_H__