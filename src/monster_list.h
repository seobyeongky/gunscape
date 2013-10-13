//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: monster_list.h
//
// 내용: 몬스터 종류와 생성함수
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MONSTER_LIST_H__
#define  __MONSTER_LIST_H__

#include "monster.h"
#include "main_weapon_list.h"

//몬스터 리스트는 monster.h에 있다.

class Texture;






Unit* New_Monster(Monster_Index kind_, coord_def pos_, int team_, int flag_, int time_ = 0);
Unit* New_Named(Monster_Index kind_, coord_def pos_, int team_, int flag_, int time_ = 0);

#endif // __MONSTER_LIST_H__