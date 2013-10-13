//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_bullet.cpp
//
// 내용: 능력 - 예비 탄창
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_bullet.h"
#include "player.h"

Abil_bullet::Abil_bullet(int level_):
Ability("예비탄창", level_,/*최대레벨*/3, /*확률*/100, /*필요레벨*/1, /*능력종류*/AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_bullet::~Abil_bullet()
{

}


Ability* Abil_bullet::Clone(int level_)
{
	return new Abil_bullet(level_);
}


const char* Abil_bullet::GetInfor()
{
	switch(level)
	{
	case 1:
		return "최대 탄창 1개 증가";
	case 2:
		return "최대 탄창 2개 증가";
	case 3:
		return "최대 탄창 3개 증가";
	}
	return "레벨 에러";
}
bool Abil_bullet::ActivePlayer(Player* player_)
{
	player_->UpDownMaxBullet(level);
	return true;
}

bool Abil_bullet::UnActivePlayer(Player* player_)
{
	player_->UpDownMaxBullet(-level);
	return false;
}