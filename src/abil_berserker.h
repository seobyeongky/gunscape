//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_berserker.h
//
// 내용: 사용형 - 광폭화
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABIL_BERSERKER_H__
#define  __ABIL_BERSERKER_H__

#include "ability.h"

class Abil_berserker : public Ability 
{
	int count;
	bool bsk;
public:
	Abil_berserker(int level_);
	virtual ~Abil_berserker();

	virtual Ability* Clone(int level_);

	virtual const char* GetInfor();

	float GetSpeed();
	float GetAtkSpeed();
	float GetDef();
	float GetVamp();

	void End(Game_Manager* gm_, Player* player_);

	virtual bool Action(Game_Manager* gm_, Player* player_);

	virtual bool isUsing(){return bsk;};
	virtual bool Use(Game_Manager* gm_, Player* player_);
	virtual bool UnUse(Game_Manager* gm_, Player* player_);

	virtual float GetUseBullet(){return 0.5f;};
};

#endif // __ABIL_BERSERKER_H__