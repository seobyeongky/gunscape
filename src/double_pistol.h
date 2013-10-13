//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: double_pistol.h
//
// ����: �ֱ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __DOUBLE_PISTOL_H__
#define  __DOUBLE_PISTOL_H__

#include "main_weapon.h"

class Double_pistol: public Main_Weapon
{
	int start_speed;//��ŸƮ �߻簣��
	int speed_up;//���� ��� �ӵ��� ������
	int burst_speed;//���� �߻簣��(����)
	int current_speed;
	int delay;
	int shot_speed;
	float damage;
	float sniper;
	int distant;//�߽ɺ��� ���� ��� �Ÿ�

public:
	Double_pistol(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Double_pistol();

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	
	virtual void Passive(Game_Manager* gm_, Player* unit_, bool current_);
	virtual float GetSniper(){return sniper;};

	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
};

#endif // __DOUBLE_PISTOL_H__