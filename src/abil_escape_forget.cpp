//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_escape_forget.cpp
//
// 내용: 따돌리기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_escape_forget.h"
#include "player.h"

Abil_Escape_Forget::Abil_Escape_Forget(int level_):
Ability("따돌리기", level_, 2, 100, /*필요레벨*/1, /*능력종류*/AT_PASSIVE)
{
}


Abil_Escape_Forget::~Abil_Escape_Forget()
{

}


Ability* Abil_Escape_Forget::Clone(int level_)
{
	return new Abil_Escape_Forget(level_);
}


const char* Abil_Escape_Forget::GetInfor()
{
	switch(level)
	{
	case 1:
		return "도망칠때 적을 따돌리는데 필요한 시간이 절반이 된다.";
	case 2:
		return "도망칠때 적을 곧바로 따돌리게 된다.";
	}
	return "레벨 에러";
}


bool Abil_Escape_Forget::ActivePlayer(Player* player_)
{
	if(level == 1)
		player_->SetForgetCount(300);
	else if(level == 2)
		player_->SetForgetCount(50);
	return true;
}

bool Abil_Escape_Forget::UnActivePlayer(Player* player_)
{
	if(level == 1)
		player_->SetForgetCount(600);
	else if(level == 2)
		player_->SetForgetCount(600);

	return false;
}