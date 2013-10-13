//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: bazooka_ap.h
//
// 내용: 관통 바주카
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __BAZOOKA_AP_H__
#define  __BAZOOKA_AP_H__

#include "main_weapon.h"

class Bazooka_ap: public Main_Weapon
{
	int burst_speed;//총의 발사간격
	int shot_speed;
	float damage;

public:
	Bazooka_ap(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Bazooka_ap();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	
	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
};

#endif // __BAZOOKA_AP_H__