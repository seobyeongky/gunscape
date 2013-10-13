//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: mon_zombie_small.cpp
//
// ����: �������� �þ߿� ������ ������ �ɾ������ ����� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_zombie_small.h"

#include "gamemanager.h"

Mon_zombie_small::Mon_zombie_small(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_)
{

}
Mon_zombie_small::~Mon_zombie_small()
{

}

void Mon_zombie_small::MeleeDamage(Game_Manager* gm_, Unit* target_)
{
	target_->SetDamage(gm_, GetPos(), DT_MELEE, GetDamage(), GetTeam());
	target_->SetBlind(100);
	target_->StateApply("�þ߹���",100);
	target_->SetSlow(100);
}