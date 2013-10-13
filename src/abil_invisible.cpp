//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_invisible.cpp
//
// ����: ����� - ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_invisible.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_piece.h"

Abil_invisible::Abil_invisible(int level_):
Ability("����", level_,3, 100, 1, AT_USE),
is_invi(false), invisible(0)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_invisible::~Abil_invisible()
{

}


Ability* Abil_invisible::Clone(int level_)
{
	return new Abil_invisible(level_);
}


const char* Abil_invisible::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ���Ż���, �̼Ӱ���(źâ 0.5�� �Ҹ�)";
	case 2:
		return "���� ���Ż���, �̼Ӱ���(źâ 0.5�� �Ҹ�)";
	case 3:
		return "���� ���Ż���, �̼Ӱ���(źâ 0.5�� �Ҹ�)";
	}
	return "���� ����";
}
bool Abil_invisible::Action(Game_Manager* gm_, Player* player_)
{
	if(is_invi)
	{
		player_->SetStaminaDelay(100);
		player_->SetInvisible(255);	
		if(!player_->UseStamina(GetConsum()))
		{
			UnUse(gm_, player_);
			return false;
		}
	}
	else
		player_->SetInvisible(0);

	return true;
}
float Abil_invisible::GetConsum()
{
	switch(level)
	{
	case 1:
		return 0.25f;
	case 2:
		return 0.2f;
	case 3:
		return 0.16f;
	}
	return false;
}
float Abil_invisible::GetSpeed()
{
	switch(level)
	{
	case 1:
		return 0.5f;
	case 2:
		return 0.6f;
	case 3:
		return 0.7f;
	}
	return false;
}
bool Abil_invisible::Use(Game_Manager* gm_, Player* player_)
{
	if(!is_invi)
	{
		if(player_->UseBullet(GetUseBullet()))
		{
			player_->ApplySpeed(GetSpeed());
			gm_->InvisibleLost(player_->GetPos());
			is_invi = true;
			Effect_invisible(gm_, player_->GetPos(), 10,  1.0f, 0.5f);
			return true;
		}
		else
			return false;
	}
	return false;
}
bool Abil_invisible::UnUse(Game_Manager* gm_, Player* player_)
{
	if(is_invi)
	{
		player_->ApplySpeed(1/GetSpeed());
		is_invi = false;
		return true;
	}
	return false;
}	
