//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_immortal.cpp
//
// ����: ����� - �һ��Ǻг�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_immortal.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_piece.h"

Abil_immortal::Abil_immortal(int level_):
Ability("�һ��", level_,3, 100, 1, AT_USE),
immortal(false), count(0)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_immortal::~Abil_immortal()
{

}


Ability* Abil_immortal::Clone(int level_)
{
	return new Abil_immortal(level_);
}


const char* Abil_immortal::GetInfor()
{
	switch(level)
	{
	case 1:
		return "����߿� ü���� 1�Ʒ��� ������������";
	case 2:
		return "����߿� ü���� 1�Ʒ��� ������������";
	case 3:
		return "����߿� ü���� 1�Ʒ��� ������������";
	}
	return "���� ����";
}
float Abil_immortal::GetConsum()
{
	switch(level)
	{
	case 1:
		return 1.0f;
	case 2:
		return 0.7f;
	case 3:
		return 0.4f;
	}
	return false;
}
bool Abil_immortal::Action(Game_Manager* gm_, Player* player_)
{
	if(immortal)
	{
		player_->SetStaminaDelay(100);
		if(count%2 == 0)
		{
			Effect_immortal(gm_, player_->GetPos(), 1, 0.5f);
		}
		count++;
		if(!player_->UseStamina(GetConsum()))
		{
			End(gm_, player_);
			return false;
		}
	}
	return true;
}
bool Abil_immortal::Use(Game_Manager* gm_, Player* player_)
{
	if(!immortal)
	{
		player_->SetImmortal(true);
		immortal = true;
		return true;
	}
	return false;
}
bool Abil_immortal::UnUse(Game_Manager* gm_, Player* player_)
{
	return false;
}


void Abil_immortal::End(Game_Manager* gm_, Player* player_)
{	
	if(immortal)
	{
		player_->SetImmortal(false);
		immortal = false;
	}
}