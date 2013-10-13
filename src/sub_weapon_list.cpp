//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sub_weapon_list.cpp
//
// 내용: 서브웨폰 리턴
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "sub_weapon_list.h"

#include "grenade.h"
#include "smoke_grenade.h"
#include "kevlar.h"
#include "net.h"
#include "dark_cloak.h"
#include "running_shoes.h"
#include "barricade.h"
#include "shield.h"
#include "throw_knife.h"
#include "bullet_pack.h"
#include "fire_cloth.h"
#include "adrenalin.h"
#include "silencer.h"
#include "trap.h"






Sub_Weapon* New_Sub_Weapon(Sub_Weapon_Kind kind_, Player* player_, coord_def pos_, int time_)
{
	Sub_Weapon* temp = NULL;
	
	switch(kind_)
	{
	case SWK_NONE:
	case SWK_GRENADE:
	default:
		temp = new Sub_Grenade(player_, pos_, time_);
	break;
	case SWK_KEVLAR:
		temp = new Sub_Kevlar(player_, pos_, time_);
	break;
	case SWK_NET:
		temp = new Sub_Net(player_, pos_, time_);
	break;
	case SWK_SMOKE_BOMB:
		temp = new Sub_Smoke_Grenade(player_, pos_, time_);
	break;
	case SWK_CLOAK:
		temp = new Sub_Cloak(player_, pos_, time_);
	break;
	case SWK_RUNNING_SHOES:
		temp = new Sub_Running_Shoes(player_, pos_, time_);
	break;
	case SWK_BARRICADE:
		temp = new Sub_Barricade(player_, pos_, time_);
	break;
	case SWK_SHIELD:
		temp = new Sub_Shield(player_, pos_, time_);
	break;
	case SWK_THROW_KNIFE:
		temp = new Sub_Throw_knife(player_, pos_, time_);
	break;
	case SWK_BULLET_PACK:
		temp = new Sub_Bullet_pack(player_, pos_, time_);
	break;
	case SWK_FIRE_CLOTH:
		temp = new Sub_Fire_Cloth(player_, pos_, time_);
	break;
	case SWK_ADRENALIN:
		temp = new Sub_Adrenalin(player_, pos_, time_);
	break;
	case SWK_SILENCER:
		temp = new Sub_Silencer(player_, pos_, time_);
	break;
	case SWK_TRAP:
		temp = new Sub_Trap(player_, pos_, time_);
	break;
	
	}
	return temp;
}
