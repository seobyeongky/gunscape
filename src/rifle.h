//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: rifle.h
//
// ����: �����÷� �����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __RIFLE_H__
#define  __RIFLE_H__

#include "main_weapon.h"

class Rifle: public Main_Weapon
{
protected:
	int start_speed;//��ŸƮ �߻簣��
	int speed_up;//���� ��� �ӵ��� ������
	int burst_speed;//���� �߻簣��(����)
	int current_speed;
	int delay;
	int shot_speed;
	float damage;
	float sniper;
	float sniper_static;
	float slow_ratio;
	int slow_turn;
	int bunch;

public:
	Rifle(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Rifle();
	

	virtual void UpDownBunch(int value_){bunch+=value_;};

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	
	virtual void Passive(Game_Manager* gm_, Player* unit_, bool current_);


	
	virtual void PlayReloadSE();
	
	virtual int GetBackStabDamage(Unit* User_);
	virtual float GetSniper(){return sniper;};
	virtual void ApplySniper(float ratio_){sniper*=ratio_;};
	

	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
	virtual const char* GetSniperStr();
};

#endif // __RIFLE_H__