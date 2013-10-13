//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_instant_bullet.cpp
//
// 내용: 능력-인스턴스-탄창회복
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_instant_bullet.h"
#include "player.h"

Abil_Instant_bullet::Abil_Instant_bullet(int level_):
Ability("탄창보충", level_, 1, 30, 1, AT_INSTANCE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_Instant_bullet::~Abil_Instant_bullet()
{

}


Ability* Abil_Instant_bullet::Clone(int level_)
{
	return new Abil_Instant_bullet(level_);
}


const char* Abil_Instant_bullet::GetInfor()
{
	switch(level)
	{
	case 1:
		return "배우는 즉시 탄창이 가득 참";
	}
	return "레벨 에러";
}

bool Abil_Instant_bullet::InstanceActive(Player* player_)
{	
	player_->SuppleBullet((float)player_->GetMaxBullet());
	return true;
}