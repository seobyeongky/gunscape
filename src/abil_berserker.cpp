//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_run.cpp
//
// ����: ����� - �޸���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_berserker.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_piece.h"
#include "effect_message.h"

Abil_berserker::Abil_berserker(int level_):
Ability("����ȭ", level_,3, 100, 1, AT_USE),
bsk(false), count(0)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_berserker::~Abil_berserker()
{

}


Ability* Abil_berserker::Clone(int level_)
{
	return new Abil_berserker(level_);
}


const char* Abil_berserker::GetInfor()
{
	switch(level)
	{
	case 1:
		return "������ ���� ����ȭ. ������������ �鿪(źâ 0.5�� �Ҹ�)";
	case 2:
		return "������ ���� ����ȭ. ������������ �鿪(źâ 0.5�� �Ҹ�)";
	case 3:
		return "������ ���� ����ȭ. ������������ �鿪(źâ 0.5�� �Ҹ�)";
	}
	return "���� ����";
}

float Abil_berserker::GetSpeed()
{
	switch(level)
	{
	case 1:
		return 1.2f;
	case 2:
		return 1.35f;
	case 3:
		return 1.5f;
	}
	return false;
}

float Abil_berserker::GetAtkSpeed()
{
	switch(level)
	{
	case 1:
		return 1.5f;
	case 2:
		return 1.7f;
	case 3:
		return 2.0f;
	}
	return false;
}

float Abil_berserker::GetDef()
{
	switch(level)
	{
	case 1:
		return 0.5f;
	case 2:
		return 0.4f;
	case 3:
		return 0.3f;
	}
	return false;
}

bool Abil_berserker::Action(Game_Manager* gm_, Player* player_)
{
	if(bsk)
	{
		player_->SetStaminaDelay(100);

		if(!player_->UseStamina(0.4f))
		{
			End(gm_, player_);
			return false;
		}
	}
	return true;
}
bool Abil_berserker::Use(Game_Manager* gm_, Player* player_)
{
	if(!bsk  && player_->GetStamina() > 1.0f && !player_->GetSniper())
	{
		if(player_->UseBullet(GetUseBullet()))
		{
			Effect_simple_speak(gm_,"����ȭ!",player_->GetPos());
			player_->Swap(4);
			player_->ApplyAtkSpd(GetAtkSpeed());		
			player_->ApplyDefense(DT_ALL,GetDef());
			player_->SetDefResist(DT_MELEE,true);
			player_->ApplySpeed(GetSpeed());
			player_->SetBerserker(true);
			
			player_->SetDelay(0);
			
			//player_->Applyad(GetSpeed());
			bsk = true;
			return true;
		}
		return false;
	}
	return false;
}
bool Abil_berserker::UnUse(Game_Manager* gm_, Player* player_)
{
	return false;
}


void Abil_berserker::End(Game_Manager* gm_, Player* player_)
{	
	if(bsk)
	{
		player_->ApplyAtkSpd(1/GetAtkSpeed());		
		player_->ApplyDefense(DT_ALL,1/GetDef());
		player_->SetDefResist(DT_MELEE,false);
		player_->ApplySpeed(1/GetSpeed());
		player_->SetBerserker(false);
		player_->SetBskSlow(100);

		bsk = false;
	}
}