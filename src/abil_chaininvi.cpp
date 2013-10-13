//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_chaininvi.cpp
//
// ����: ����Ͻ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_chaininvi.h"
#include "player.h"
#include "gamemanager.h"
#include "effect_piece.h"

Abil_chaininvi::Abil_chaininvi(int level_):
Ability("����Ͻ�", level_, 3, 50, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_chaininvi::~Abil_chaininvi()
{

}


Ability* Abil_chaininvi::Clone(int level_)
{
	return new Abil_chaininvi(level_);
}


const char* Abil_chaininvi::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ���̸� 3�ʰ� ����";
	case 2:
		return "���� ���̸� 5�ʰ� ����";
	case 3:
		return "���� ���̸� 7�ʰ� ����";
	}
	return "���� ����";
}

int Abil_chaininvi::Getsecond()
{
	switch(level)
	{
	case 1:
		return 180;
	case 2:
		return 300;
	case 3:
		return 420;
	}
	return false;
}

bool Abil_chaininvi::KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_)
{
	gm_->InvisibleLost(player_->GetPos());		
	Effect_invisible(gm_, player_->GetPos(), 5,  1.0f, 0.5f);
	player_->SetInvisibleturn(Getsecond());
	player_->StateApply("����Ͻ�",Getsecond());

	return true;
}

