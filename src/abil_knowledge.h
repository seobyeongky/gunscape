//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_knowledge.h
//
// 내용: 능력-선택 능력 1업
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_KNOWLEDGE_H__
#define  __ABIL_KNOWLEDGE_H__

#include "ability.h"

class Abil_knowledge : public Ability 
{
public:
	Abil_knowledge(int level_);
	virtual ~Abil_knowledge();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool ActivePlayer(Player* player_);

	virtual bool UnActivePlayer(Player* player_);
};

#endif // __ABIL_KNOWLEDGE_H__