//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: water.h
//
// 내용: 물뿌리개 무기들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __WATER_H__
#define  __WATER_H__

#include "main_weapon.h"

class Water: public Main_Weapon
{
	int burst_speed;//총의 발사간격
	int shot_speed;
	float damage;
	float power;
	float max_power;
	float size_inc;
	//발사시간은 distance에 맡긴다. 대신 라이플과 달리 단위는 길이가 아닌 시간이다.

public:
	Water(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Water();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);

	virtual void PlayReloadSE();

	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
};



#endif // __WATER_H__