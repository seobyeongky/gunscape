//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_bare.cpp
//
// ����: �Ǽհ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_bare.h"
#include "player.h"

Abil_bare::Abil_bare(int level_):
Ability("�Ǽ�����", level_, 3, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_bare::~Abil_bare()
{

}


Ability* Abil_bare::Clone(int level_)
{
	return new Abil_bare(level_);
}


const char* Abil_bare::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���������� ���� �̼Ӱ��� ����. ���������� ������ �˹��� ��";
	case 2:
		return "���������� ������ �̼Ӱ��Ҿ��� �˹�. �������� 20%����";
	case 3:
		return "���������� ������ �̼Ӱ��Ҿ��� �˹�. �������� 50%����";
	}
	return "���� ����";
}

bool Abil_bare::ActivePlayer(Player* player_)
{
	player_->ApplyMeleeKnockBack(level==1?0.5f:0);
	player_->SetMirrorKnockback(2.0f);
	if(level>1)		
	{
		player_->ApplyDefense(DT_MELEE, level==2?0.8f:0.5f);
		player_->SetMirrorKnockback(4.0f);
	}
	return true;
}

bool Abil_bare::UnActivePlayer(Player* player_)
{
	if(level>1)		
		player_->ApplyDefense(DT_MELEE, level==2?1/0.8f:1/0.5f);
	player_->SetMirrorKnockback(0.0f);
	return false;
}