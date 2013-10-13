//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: no_weapon.h
//
// 내용: 무기가 없음
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __NO_WEAPON_H__
#define  __NO_WEAPON_H__

#include "main_weapon.h"

class No_Weapon: public Main_Weapon
{

public:
	No_Weapon(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~No_Weapon();
	
	virtual bool InterfaceDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InterfaceNameDraw(Direct_Manager* direct_, coord_def offset_){return false;};

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);

};

#endif // __NO_WEAPON_H__