//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_state_view.cpp
//
// ����: ���º���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_state_view.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_warning_message.h"

Abil_state_view::Abil_state_view(int level_):
Ability("����", level_, 1, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_state_view::~Abil_state_view()
{

}


Ability* Abil_state_view::Clone(int level_)
{
	return new Abil_state_view(level_);
}


const char* Abil_state_view::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ���¿� �����Ҹ� �˾�ç �� �ִ�";
	}
	return "���� ����";
}

bool Abil_state_view::ActivePlayer(Player* player_)
{
	player_->SetStateView(true);
	player_->SetMonSightView(true);
	return true;
}

bool Abil_state_view::UnActivePlayer(Player* player_)
{
	player_->SetStateView(false);
	player_->SetMonSightView(false);
	return false;
}	

bool Abil_state_view::EnterMap(Game_Manager* gm_, Player* player_, int level_)
{
	char temp[256];
	Monster_Index index_ = MON_NONE;
	for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
	{
		if((*it)->Getindex() >= NAMED_START)
		{
			if(index_ == MON_NONE)
			{
				index_ = (*it)->Getindex();
			}
			else if(index_ != (*it)->Getindex())
			{
				index_ = NAMED_MAX;
			}
		}
	}
	if(index_ == MON_NONE)
		return false;


	switch(index_)
	{
	case NAMED_JACK:
		sprintf_s(temp,256,"�� ������ ���ѼҸ��� ��� ���� �����Ҹ��� �鸰��...");
		break;
	case NAMED_LOOTER:
		sprintf_s(temp,256,"�԰ɽ����� ������ �����Ҹ��� ���ǲ�� �鸮�� �ִ�...");
		break;
	case NAMED_ROBOT:
		sprintf_s(temp,256,"�ò����� ����Ҹ��� ���Ҹ��� ��濡�� �鸮�� �ִ�...");
		break;
	case NAMED_DRILL:
		sprintf_s(temp,256,"�� ����� ������ �̾��� �Ҹ��� ������ ���������ִ�...");
		break;
	case NAMED_FLY_BOSS:
		sprintf_s(temp,256,"�� ���� ���� ������ ������ �������Ҹ��� �︮�� �ִ�...");
		break;
	case NAMED_ASSASIN:
		sprintf_s(temp,256,"������ �߼Ҹ��� �������� ��Ҹ��� ��������...");
		break;
	case NAMED_SNIPER:
		sprintf_s(temp,256,"������ ���� �Ӹ��� �����ϰ� �ִ� ������ �޴´�...");
		break;
	case NAMED_VIRUS:
		sprintf_s(temp,256,"�� ������ ����� ���� ���� �Ǻο� ������ ���Ⱑ ��������...");
		break;
	case NAMED_BERSERKER:
		sprintf_s(temp,256,"�췷�� ������ ������ ����� ������ �鸰��...");
		break;
	case NAMED_SCREAM:
		sprintf_s(temp,256,"�Ҹ���ġ�� ���Ҹ��� �︮�� �ִ�...");
		break;
	case NAMED_MAX:
		sprintf_s(temp,256,"���� ������ ���� �鸮�� �ִ�. �� ���� �ص��� �����غ��δ�.");
		break;
	default:
		sprintf_s(temp,256,"���װ���.");
		break;
	}


	gm_->shot_list.push_back(new Effect_warning_message(gm_, temp, 300));
	return true;
}

