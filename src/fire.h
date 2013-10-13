//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: fire.h
//
// 내용: 화염방사기류 무기들
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __FIRE_H__
#define  __FIRE_H__

#include "main_weapon.h"

class Fire: public Main_Weapon
{
	int burst_speed;//총의 발사간격
	int shot_speed;
	float damage;
	float fire_damage;
	float size_inc;
	//화염의 발사시간은 distance에 맡긴다. 대신 라이플과 달리 단위는 길이가 아닌 시간이다.

public:
	Fire(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Fire();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);

	virtual void PlayReloadSE();

	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
};



#endif // __FIRE_H__