//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_state_view.cpp
//
// 내용: 상태보기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_state_view.h"
#include "gamemanager.h"
#include "player.h"
#include "effect_warning_message.h"

Abil_state_view::Abil_state_view(int level_):
Ability("직감", level_, 1, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
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
		return "적의 상태와 위험요소를 알아챌 수 있다";
	}
	return "레벨 에러";
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
		sprintf_s(temp,256,"귀 따가운 권총소리와 기분 나쁜 웃음소리가 들린다...");
		break;
	case NAMED_LOOTER:
		sprintf_s(temp,256,"게걸스러운 좀비의 울음소리가 어렴풋이 들리고 있다...");
		break;
	case NAMED_ROBOT:
		sprintf_s(temp,256,"시끄러운 공장소리와 기계소리가 사방에서 들리고 있다...");
		break;
	case NAMED_DRILL:
		sprintf_s(temp,256,"땅 깊숙한 곳에서 미약한 소리와 진동이 느껴지고있다...");
		break;
	case NAMED_FLY_BOSS:
		sprintf_s(temp,256,"얼마 멀지 않은 곳에서 벌레의 날개짓소리가 울리고 있다...");
		break;
	case NAMED_ASSASIN:
		sprintf_s(temp,256,"숨죽인 발소리와 나이프의 쇳소리가 느껴진다...");
		break;
	case NAMED_SNIPER:
		sprintf_s(temp,256,"누군가 나의 머리를 조준하고 있는 느낌을 받는다...");
		break;
	case NAMED_VIRUS:
		sprintf_s(temp,256,"이 곳에선 고약한 썩은 내와 피부에 따가운 공기가 느껴진다...");
		break;
	case NAMED_BERSERKER:
		sprintf_s(temp,256,"우렁찬 남성의 괴성이 가까운 곳에서 들린다...");
		break;
	case NAMED_SCREAM:
		sprintf_s(temp,256,"소름끼치는 비명소리가 울리고 있다...");
		break;
	case NAMED_MAX:
		sprintf_s(temp,256,"여러 소음이 겹쳐 들리고 있다. 이 층은 극도로 위험해보인다.");
		break;
	default:
		sprintf_s(temp,256,"버그같다.");
		break;
	}


	gm_->shot_list.push_back(new Effect_warning_message(gm_, temp, 300));
	return true;
}

