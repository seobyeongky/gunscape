//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: melee_weapon_list.h
//
// ����: �и���������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MELEE_WEAPON_LIST_H__
#define  __MELEE_WEAPON_LIST_H__

#include "melee_weapon.h"



extern melee_weapon_infor melee__knife;
extern melee_weapon_infor melee__club;
extern melee_weapon_infor melee__axe;

//�и����� ������ melee_weapon.h�� �Ű��.

Melee_Weapon* New_Melee_Weapon(Melee_Kind kind_, coord_def pos_, int time_);

#endif // __MELEE_WEAPON_LIST_H__