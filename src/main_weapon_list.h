//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: main_weapon_list.h
//
// 내용: 메인웨폰종류
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MAIN_WEAPON_LIST_H__
#define  __MAIN_WEAPON_LIST_H__

#include "main_weapon.h"

//enum Main_Weapon_Kind
//{
//	MWK_ASSAUL_RIFLE,
//	MWK_RIFLE_PISTOL,
//};
//이것은 main_weapon.h로 옮겼다.

extern main_weapon_infor rifle__assault_rifle;
extern main_weapon_infor rifle__pistol;
extern main_weapon_infor rifle__shot_gun;
extern main_weapon_infor rifle__flame_thrower;
extern main_weapon_infor rifle__bazooka;
extern main_weapon_infor rifle__mon_assault_rifle;
extern main_weapon_infor rifle__mon_pistol_big;
extern main_weapon_infor rifle__mon_silence_gun;
extern main_weapon_infor rifle__mon_bazooka;
extern main_weapon_infor rifle__mon_water_gun;
extern main_weapon_infor rifle__mon_bounce_fire;
extern main_weapon_infor rifle__mon_sniper;
extern main_weapon_infor rifle__mon_robot_minigun;
extern main_weapon_infor rifle__mon_robot_bazooka;
extern main_weapon_infor rifle__mon_robot_grenade;

Main_Weapon* New_Main_Weapon(Main_Weapon_Kind kind_, coord_def pos_, int time_, float bullet_ = 0.0f);

#endif // __MAIN_WEAPON_LIST_H__