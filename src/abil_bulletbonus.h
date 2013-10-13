//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_bulletbonus.h
//
// 내용: 능력-탄창얻기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_BULLETBONUS_H__
#define  __ABIL_BULLETBONUS_H__

#include "ability.h"

class Abil_bulletbonus : public Ability 
{
public:
	Abil_bulletbonus(int level_);
	virtual ~Abil_bulletbonus();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	virtual bool EnterMap(Game_Manager* gm_, Player* player_, int level_);
};

#endif // __ABIL_BULLETBONUS_H__