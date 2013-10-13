//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_antiexplosion.cpp
//
// 내용: 폭발에 의한 자폭데미지 감소
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_antiexplosion.h"
#include "player.h"

Abil_antiexplosion::Abil_antiexplosion(int level_):
Ability("성형작약", level_, 3, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_antiexplosion::~Abil_antiexplosion()
{

}


Ability* Abil_antiexplosion::Clone(int level_)
{
	return new Abil_antiexplosion(level_);
}


const char* Abil_antiexplosion::GetInfor()
{
	switch(level)
	{
	case 1:
		return "폭발데미지 15% 감소. 자폭시 15% 추가감소";
	case 2:
		return "폭발데미지 40% 감소. 자폭시 40% 추가감소";
	case 3:
		return "폭발데미지 70% 감소. 자폭데미지에 면역";
	}
	return "레벨 에러";
}


bool Abil_antiexplosion::ActivePlayer(Player* player_)
{
	player_->ApplyDefense(DT_EXPLOSION, level==1?0.85f:(level==2?0.6f:0.3f));
	player_->ApplyDefense(DT_SELF_EXPLOSION, level==1?0.85f:0.6f);
	if(level == 3)
		player_->SetDefResist(DT_SELF_EXPLOSION, true);
	return true;
}
bool Abil_antiexplosion::UnActivePlayer(Player* player_)
{
	player_->ApplyDefense(DT_EXPLOSION, level==1?1/0.85f:(level==2?1/0.6f:1/0.3f));
	player_->ApplyDefense(DT_SELF_EXPLOSION, level==1?1/0.85f:1/0.6f);
	if(level == 3)
		player_->SetDefResist(DT_SELF_EXPLOSION, false);
	return false;
}