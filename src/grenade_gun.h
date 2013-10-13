//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: grenade_gun.h
//
// 내용: 그레네이드 건
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __GRENADE_GUN_H__
#define  __GRENADE_GUN_H__

#include "main_weapon.h"

class Grenade_gun: public Main_Weapon
{
	int burst_speed;//총의 발사간격
	int shot_time;
	float damage;
	float range;
	int bunch;
	bool pentan;

public:
	Grenade_gun(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Grenade_gun();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	
	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
};

#endif // __GRENADE_GUN_H__