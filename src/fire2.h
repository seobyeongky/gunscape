//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: fire2.h
//
// 내용: 발사형 화염방사기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __FIRE2_H__
#define  __FIRE2_H__

#include "main_weapon.h"

class Fire2: public Main_Weapon
{
	int burst_speed;//총의 발사간격
	int shot_speed;
	float damage;
	int fire_time;
	float fire_damage;
	int bounce;

public:
	Fire2(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Fire2();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	
	void PlayReloadSE();
	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
};

#endif // __FIRE2_H__