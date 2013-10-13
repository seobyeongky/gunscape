//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_sleep.h
//
// 내용: 능력-잠자기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_SLEEP_H__
#define  __ABIL_SLEEP_H__

#include "ability.h"

class Abil_sleep : public Ability 
{
public:
	Abil_sleep(int level_);
	virtual ~Abil_sleep();

	virtual Ability* Clone(int level_);

	int GetPercent();
	virtual const char* GetInfor();

	virtual bool EnterMap(Game_Manager* gm_, Player* player_, int level_);
};

#endif // __ABIL_SLEEP_H__