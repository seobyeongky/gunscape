//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: melee_weapon_list.cpp
//
// 내용: 밀리웨폰종류
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "melee_weapon_list.h"
#include "texture_list.h"
#include "hammer.h"


melee_weapon_infor melee__knife = 
{
	MK_KNIFE,/*종류*/
	&tex_item_unknown,/*땅에 떨어진 이미지*/
	&tex_inter_knife,/*장착시 이미지*/
	&tex_melee,/*휘두르는 이미지*/
	"나이프",/*이름*/
	"암살 가능한 근접무기",
	1.0f,/*이속감소비율*/
	1.0f,/*장비속도*/
	1.0f, /*연사속도 비율*/
	1.0f, /*데미지 비율*/
	8.0f, /*사거리*/
	0.1f, //적을 밀치는정도
	3.0f, //적을 밀치는 최고치
	//-----
	15,/*공속*/
	5.0f,/*공격력*/
	0.5f,/*범위*/
	8.0f,/*백스탭*/
	1.0f/*휠윈드 패널티*/
};


melee_weapon_infor melee__club = 
{
	MK_CLUB,/*종류*/
	&tex_item_unknown,/*땅에 떨어진 이미지*/
	&tex_inter_club,/*장착시 이미지*/
	&tex_melee,/*휘두르는 이미지*/
	"곤봉",/*이름*/
	"넉백이 좋은 근접무기",
	1.0f,/*이속감소비율*/
	1.0f,/*장비속도*/
	1.0f, /*연사속도 비율*/
	1.0f, /*데미지 비율*/
	10.0f, /*사거리*/
	3.0f, //적을 밀치는정도
	5.0f, //적을 밀치는 최고치
	//-----
	30,/*공속*/
	15.0f,/*공격력*/
	0.7f,/*범위*/
	0.0f,/*백스탭*/
	1.0f/*휠윈드 패널티*/
};

melee_weapon_infor melee__axe = 
{
	MK_AXE,/*종류*/
	&tex_item_unknown,/*땅에 떨어진 이미지*/
	&tex_inter_axe,/*장착시 이미지*/
	&tex_melee,/*휘두르는 이미지*/
	"소방도끼",/*이름*/
	"위력이 높은 근접무기",
	0.95f,/*이속감소비율*/
	1.0f,/*장비속도*/
	1.0f, /*연사속도 비율*/
	1.0f, /*데미지 비율*/
	10.0f, /*사거리*/
	0.5f, //적을 밀치는정도
	5.0f, //적을 밀치는 최고치
	//-----
	50,/*공속*/
	25.0f,/*공격력*/
	0.8f,/*범위*/
	0.0f,/*백스탭*/
	1.0f/*휠윈드 패널티*/
};
melee_weapon_infor melee__spear = 
{
	MK_SPEAR,/*종류*/
	&tex_item_unknown,/*땅에 떨어진 이미지*/
	&tex_inter_spear,/*장착시 이미지*/
	&tex_melee3,/*휘두르는 이미지*/
	"창",/*이름*/
	"사거리가 긴 무기",
	0.9f,/*이속감소비율*/
	1.0f,/*장비속도*/
	1.0f, /*연사속도 비율*/
	1.0f, /*데미지 비율*/
	25.0f, /*사거리*/
	0.1f, //적을 밀치는정도
	3.0f, //적을 밀치는 최고치
	//-----
	60,/*공속*/
	20.0f,/*공격력*/
	0.5f,/*범위*/
	0.0f,/*백스탭*/
	1.42f/*휠윈드 패널티*/
};

melee_weapon_infor melee__hammer = 
{
	MK_HAMMER,/*종류*/
	&tex_item_unknown,/*땅에 떨어진 이미지*/
	&tex_inter_hammer,/*장착시 이미지*/
	&tex_melee,/*휘두르는 이미지*/
	"해머",/*이름*/
	"맞춘 상대를 날려보낸다\n",
	1.0f,/*이속감소비율*/
	1.0f,/*장비속도*/
	1.0f, /*연사속도 비율*/
	1.0f, /*데미지 비율*/
	10.0f, /*사거리*/
	3.0f, //적을 밀치는정도
	5.0f, //적을 밀치는 최고치
	//-----
	40,/*공속*/
	20.0f,/*공격력*/
	0.9f,/*범위*/
	0.0f,/*백스탭*/
	1.0f/*휠윈드 패널티*/
};

melee_weapon_infor melee__assasin_knife = 
{
	MK_ASSASIN_KNIFE,/*종류*/
	&tex_item_unknown,/*땅에 떨어진 이미지*/
	&tex_inter_knife,/*장착시 이미지*/
	&tex_melee,/*휘두르는 이미지*/
	"비수",/*이름*/
	"암살전용의 단검",
	1.0f,/*이속감소비율*/
	1.0f,/*장비속도*/
	1.0f, /*연사속도 비율*/
	1.0f, /*데미지 비율*/
	8.0f, /*사거리*/
	0.1f, //적을 밀치는정도
	3.0f, //적을 밀치는 최고치
	//-----
	30,/*공속*/
	3.0f,/*공격력*/
	0.5f,/*범위*/
	18.0f,/*백스탭*/
	0.0f/*휠윈드 패널티*/
};


Melee_Weapon* New_Melee_Weapon(Melee_Kind kind_, coord_def pos_, int time_)
{
	Melee_Weapon* temp = NULL;
	switch(kind_)
	{
	case MK_NONE:
	case MK_KNIFE:
	default:
		temp = new Melee_Weapon(melee__knife, pos_, time_);
	break;
	case MK_AXE:
		temp = new Melee_Weapon(melee__axe, pos_, time_);
	break;
	case MK_CLUB:
		temp = new Melee_Weapon(melee__club, pos_, time_);
	break;
	case MK_SPEAR:
		temp = new Melee_Weapon(melee__spear, pos_, time_);
	break;	
	case MK_HAMMER:
		temp = new Melee_Hammer(melee__hammer, pos_, time_);
	break;	
	case MK_ASSASIN_KNIFE:
		temp = new Melee_Weapon(melee__assasin_knife, pos_, time_);
	break;
	}
	return temp;
}