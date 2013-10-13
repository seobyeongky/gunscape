//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: bazooka.h
//
// 내용: 바주카류 무기들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __BAZOOKA_H__
#define  __BAZOOKA_H__

#include "main_weapon.h"

class Bazooka: public Main_Weapon
{
	int burst_speed;//총의 발사간격
	int shot_speed;
	float damage;
	float range;
	int guided_range;
	float guided_power;
	int bunch;

public:
	Bazooka(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Bazooka();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	
	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
};

#endif // __BAZOOKA_H__