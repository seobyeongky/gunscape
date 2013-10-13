//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sniper.h
//
// 내용: 저격총
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SNIPER_H__
#define  __SNIPER_H__

#include "main_weapon.h"

class Sniper: public Main_Weapon
{
	int burst_speed;//총의 발사간격
	int shot_speed;
	float damage;
	float sniper_static;
	float sniper;
	int bunch;

public:
	Sniper(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Sniper();

	virtual void UpDownBunch(int value_){bunch+=value_;};

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);

	virtual float special(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	
	virtual char* is_Special(){return "저격모드";};

	virtual int GetBackStabDamage(Unit* User_);	
	virtual float GetSniper(){return sniper;};
	virtual void ApplySniper(float ratio_){sniper*=ratio_;};

	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
	virtual const char* GetSniperStr();
};

#endif // __SNIPER_H__