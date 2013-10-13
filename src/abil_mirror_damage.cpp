//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_mirror_damage.cpp
//
// 내용: 반사데미지
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_mirror_damage.h"
#include "player.h"

Abil_mirror_damage::Abil_mirror_damage(int level_):
Ability("가시갑옷", level_, 3, 100, 1, AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_mirror_damage::~Abil_mirror_damage()
{

}


Ability* Abil_mirror_damage::Clone(int level_)
{
	return new Abil_mirror_damage(level_);
}


const char* Abil_mirror_damage::GetInfor()
{
	switch(level)
	{
	case 1:
		return "적에게 근접데미지를 받았을때 반사데미지를 줌";
	case 2:
		return "적에게 근접데미지를 받았을때 반사데미지를 줌";
	case 3:
		return "적에게 근접데미지를 받았을때 반사데미지를 줌";
	}
	return "레벨 에러";
}

float Abil_mirror_damage::Getdamage()
{
	switch(level)
	{
	case 1:
		return 15.0f;
	case 2:
		return 30.0f;
	case 3:
		return 50.0f;
	}
	return false;
}

bool Abil_mirror_damage::ActivePlayer(Player* player_)
{
	player_->SetMirrorDamage(Getdamage());
	return true;
}
bool Abil_mirror_damage::UnActivePlayer(Player* player_)
{
	player_->SetMirrorDamage(0.0f);
	return false;
}