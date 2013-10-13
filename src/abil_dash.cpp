//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_dash.cpp
//
// ����: ����� - �뽬
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_dash.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_piece.h"

Abil_dash::Abil_dash(int level_):
Ability("�뽬", level_,3, 100, 1, AT_USE),
delay(0)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_dash::~Abil_dash()
{

}


Ability* Abil_dash::Clone(int level_)
{
	return new Abil_dash(level_);
}


const char* Abil_dash::GetInfor()
{
	switch(level)
	{
	case 1:
		return "ª�� ���� ������ �뽬";
	case 2:
		return "�뽬���� ��� ���¹̳� �Ҹ𰨼�.";/* ���������*/
	case 3:
		return "�뽬���� ��� ���¹̳� �Ҹ��߰�����.";/* �뽬�� ��������*/
	}
	return "���� ����";
}
float Abil_dash::GetSp()
{
	switch(level)
	{
	case 1:
		return 30.0f;
	case 2:
		return 25.0f;
	case 3:
		return 15.0f;
	}
	return false;
}
bool Abil_dash::Action(Game_Manager* gm_, Player* player_)
{
	if(delay)
		delay--;
	return true;
}


bool Abil_dash::Use(Game_Manager* gm_, Player* player_)
{
	if(!delay)
	{
		if(player_->UseStamina(GetSp()))
		{
			player_->SetStaminaDelay(100);
			//player_->SlowApply(1.5f, 100);
			player_->SetKnockback(5.0f, 5.0f, player_->GetAngle());
			delay = 30;
			return true;
		}
	}
	return false;
}