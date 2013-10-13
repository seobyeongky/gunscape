//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_bare.cpp
//
// 내용: 맨손격투
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_bare.h"
#include "player.h"

Abil_bare::Abil_bare(int level_):
Ability("맨손전투", level_, 3, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
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
		return "근접전투에 의한 이속감소 절반. 근접데미지 받으면 넉백을 줌";
	case 2:
		return "근접데미지 받을때 이속감소없고 넉백. 근접방어력 20%증가";
	case 3:
		return "근접데미지 받을때 이속감소없고 넉백. 근접방어력 50%증가";
	}
	return "레벨 에러";
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