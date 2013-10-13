//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: water.h
//
// ����: ���Ѹ��� �����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __WATER_H__
#define  __WATER_H__

#include "main_weapon.h"

class Water: public Main_Weapon
{
	int burst_speed;//���� �߻簣��
	int shot_speed;
	float damage;
	float power;
	float max_power;
	float size_inc;
	//�߻�ð��� distance�� �ñ��. ��� �����ð� �޸� ������ ���̰� �ƴ� �ð��̴�.

public:
	Water(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Water();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);

	virtual void PlayReloadSE();

	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
};



#endif // __WATER_H__