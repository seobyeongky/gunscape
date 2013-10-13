//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: melee_weapon_list.h
//
// 내용: 밀리웨폰종류
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MELEE_WEAPON_LIST_H__
#define  __MELEE_WEAPON_LIST_H__

#include "melee_weapon.h"



extern melee_weapon_infor melee__knife;
extern melee_weapon_infor melee__club;
extern melee_weapon_infor melee__axe;

//밀리웨폰 종류는 melee_weapon.h로 옮겼다.

Melee_Weapon* New_Melee_Weapon(Melee_Kind kind_, coord_def pos_, int time_);

#endif // __MELEE_WEAPON_LIST_H__