//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_post.cpp
//
// ����: ����� - ���ҹڱ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_post.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_piece.h"

Abil_post::Abil_post(int level_):
Ability("���ҹڱ�", level_,3, 100, 1, AT_USE),
post(false), count(0)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_post::~Abil_post()
{

}


Ability* Abil_post::Clone(int level_)
{
	return new Abil_post(level_);
}


const char* Abil_post::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ��ġ ������ ���ݼӵ� 30%����";
	case 2:
		return "���� ��ġ ������ ���ݼӵ� 45%����";
	case 3:
		return "���� ��ġ ������ ���ݼӵ� 60%����";
	case 4:
		return "���� ��ġ ������ ���ݼӵ� 75%����";
	case 5:
		return "���� ��ġ ������ ���ݼӵ� 100%����";
	}
	return "���� ����";
}
float Abil_post::GetSpeed()
{
	switch(level)
	{
	case 1:
		return 1.3f;
	case 2:
		return 1.45f;
	case 3:
		return 1.6f;
	case 4:
		return 1.75f;
	case 5:
		return 2.0f;
	}
	return false;
}
bool Abil_post::Action(Game_Manager* gm_, Player* player_)
{
	if(post)
	{
		player_->SetStaminaDelay(100);
		count++;
		if(!player_->UseStamina(0.5f))
		{
			UnUse(gm_, player_);
			return false;
		}
	}
	return true;
}
bool Abil_post::Use(Game_Manager* gm_, Player* player_)
{
	if(!post)
	{
		player_->SetFixed(true);
		player_->ApplyAtkSpd(GetSpeed());
		player_->SetDelay(20);
		post = true;
		return true;
	}
	return false;
}
bool Abil_post::UnUse(Game_Manager* gm_, Player* player_)
{
	if(post)
	{
		player_->SetFixed(false);
		player_->ApplyAtkSpd(1/GetSpeed());
		player_->SetDelay(60);
		post = false;
		return true;
	}
	return false;
}