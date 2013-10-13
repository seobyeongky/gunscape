//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: bow.h
//
// 내용: 활이야
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __BOW_H__
#define  __BOW_H__

#include "main_weapon.h"

class Bow: public Main_Weapon
{
	int burst_speed;//총의 발사간격
	int shot_speed;

	int count;
	bool cur_click;
	bool pre_click;
	struct state
	{
		Unit* User;
		int team;
		coord_def start;
		coord_def pos;
		float focus;
		state():User(NULL),team(0),start(),pos(),focus(0.0f){};
	}bow_state;


	float damage;
	float sniper_static;
	float sniper;
	float slow_ratio;
	int slow_turn;
	int bunch;

public:
	Bow(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Bow();

	virtual void UpDownBunch(int value_){bunch+=value_;};

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	
	virtual void Passive(Game_Manager* gm_, Player* unit_, bool current_);

	virtual int GetBackStabDamage(Unit* User_);
	virtual float GetSniper(){return sniper;};
	virtual void ApplySniper(float ratio_){sniper*=ratio_;};
	
	virtual void PlayReloadSE();


	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
	virtual const char* GetSniperStr();
};

#endif // __BOW_H__