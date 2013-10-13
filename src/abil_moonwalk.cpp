//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_moonwalk.cpp
//
// 내용: 뒷걸음질 패널티 감소
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_moonwalk.h"
#include "player.h"

Abil_moonwalk::Abil_moonwalk(int level_):
Ability("문워크", level_, 2, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_moonwalk::~Abil_moonwalk()
{

}


Ability* Abil_moonwalk::Clone(int level_)
{
	return new Abil_moonwalk(level_);
}


const char* Abil_moonwalk::GetInfor()
{
	switch(level)
	{
	case 1:
		return "뒷걸음 속도 패널티 50%감소";
	case 2:
		return "뒷걸음 속도 패널티 없음";
	}
	return "레벨 에러";
}


bool Abil_moonwalk::ActivePlayer(Player* player_)
{
	player_->ApplyBackPanalty(level==1?0.5f:0.0f);
	return true;
}

bool Abil_moonwalk::UnActivePlayer(Player* player_)
{
	if(level == 1)
		player_->ApplyBackPanalty(2.0f);
	else
		player_->SetBackPanalty(1.0f);
	return false;
}