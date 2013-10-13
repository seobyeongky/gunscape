//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_live.h
//
// 내용: 능력-생존전문가
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_LIVE_H__
#define  __ABIL_LIVE_H__

#include "ability.h"

class Abil_live : public Ability 
{
public:
	Abil_live(int level_);
	virtual ~Abil_live();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();
	
	virtual bool EnterMap(Game_Manager* gm_, Player* player_, int level_);
};

#endif // __ABIL_LIVE_H__