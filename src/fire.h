//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: fire.h
//
// ����: ȭ������� �����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __FIRE_H__
#define  __FIRE_H__

#include "main_weapon.h"

class Fire: public Main_Weapon
{
	int burst_speed;//���� �߻簣��
	int shot_speed;
	float damage;
	float fire_damage;
	float size_inc;
	//ȭ���� �߻�ð��� distance�� �ñ��. ��� �����ð� �޸� ������ ���̰� �ƴ� �ð��̴�.

public:
	Fire(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Fire();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);

	virtual void PlayReloadSE();

	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
};



#endif // __FIRE_H__