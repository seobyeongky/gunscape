//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_fire.cpp
//
// ����: ȭ�������� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_fire.h"
#include "player.h"
#include "main_weapon.h"

Abil_fire::Abil_fire(int level_):
Ability("������", level_, 3, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_fire::~Abil_fire()
{

}


Ability* Abil_fire::Clone(int level_)
{
	return new Abil_fire(level_);
}

const char* Abil_fire::GetInfor()
{
	switch(level)
	{
	case 1:
		return "ȭ������ 25%����";
	case 2:
		return "ȭ������ 50%����. ������ݷ� 10%����";
	case 3:
		return "ȭ������ 50%����. ������ݷ� 30%����.";
	}
	return "���� ����";
}


bool Abil_fire::ActivePlayer(Player* player_)
{
	player_->ApplyDefense(DT_FIRE, level==1?0.75f:0.5f);
	return true;
}
bool Abil_fire::ActiveMainWeapon(Main_Weapon* weapon_)
{
	if(level>1 && weapon_->GetType() == WT_FLAME_THROWER)
	{	
		weapon_->ApplyDamegeApply(level==1?1.10f:1.30f);
		return true;
	}
	return false;
}

bool Abil_fire::UnActivePlayer(Player* player_)
{
	player_->ApplyDefense(DT_FIRE, level==1?1/0.75f:2.0f);
	return false;
}
bool Abil_fire::UnActiveMainWeapon(Main_Weapon* weapon_)
{
	if(level>1 && weapon_->GetType() == WT_FLAME_THROWER)
	{
		weapon_->ApplyDamegeApply(level==1?1/1.10f:1/1.30f);
		return true;
	}
	return false;
}