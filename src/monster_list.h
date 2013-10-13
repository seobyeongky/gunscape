//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: monster_list.h
//
// ����: ���� ������ �����Լ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MONSTER_LIST_H__
#define  __MONSTER_LIST_H__

#include "monster.h"
#include "main_weapon_list.h"

//���� ����Ʈ�� monster.h�� �ִ�.

class Texture;






Unit* New_Monster(Monster_Index kind_, coord_def pos_, int team_, int flag_, int time_ = 0);
Unit* New_Named(Monster_Index kind_, coord_def pos_, int team_, int flag_, int time_ = 0);

#endif // __MONSTER_LIST_H__