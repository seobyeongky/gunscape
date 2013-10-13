//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_list.cpp
//
// 내용: 몬스터 종류와 생성함수
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "monster_list.h"
#include "texture_list.h"
#include "named_jack.h"
#include "named_looter.h"
#include "named_robot.h"
#include "named_bug_drill.h"
#include "named_fly_boss.h"
#include "named_assasin.h"
#include "named_sniper.h"
#include "named_virus.h"
#include "named_berserker.h"
#include "named_scream.h"
#include "rifle.h"
#include "sniper.h"
#include "double_pistol.h"
#include "bazooka.h"
#include "grenade_gun.h"


monster_infor named__jack = 
{
	NAMED_JACK,			/*인덱스*/
	&tex_mon_sf_man,			/*그림*/
	&tex_player,				/*임시그림*/
	"잭",					/*이름*/
	&rifle__pistol,				/*무기*/
	50.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	1.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	50,							/*체력*/
	3.0f,						/*사이즈*/
	1.0f,						/*속도*/
	100.0f,						/*시야*/
	30,							/*경험치*/
	3,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};

monster_infor named__looter = 
{
	NAMED_LOOTER,			/*인덱스*/
	&tex_mon_zombie_weak,		/*그림*/
	&tex_player,				/*임시그림*/
	"약탈자",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	15.0f,							/*근접공격*/

	60,							/*체력*/
	3.0f,						/*사이즈*/
	1.1f,						/*속도*/
	180.0f,						/*시야*/
	25,							/*경험치*/
	0,							/*인공지능*/

	MF_ZOMBIE,							/*플래그*/
};
monster_infor named__robot = 
{
	NAMED_ROBOT,			/*인덱스*/
	&tex_mon_robot,			/*그림*/
	&tex_player,				/*임시그림*/
	"경비로봇",					/*이름*/
	&rifle__mon_robot_minigun,				/*무기*/
	50.0f,						/*최소거리*/
	120.0f,							/*최대거리*/
	1.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	150/*200*/,							/*체력*/
	5.0f,						/*사이즈*/
	0.7f,						/*속도*/
	150.0f,						/*시야*/
	200,							/*경험치*/
	3,							/*인공지능*/

	MF_DROP_BULLET,				/*플래그*/
};
monster_infor named__bug_drill = 
{
	NAMED_DRILL,			/*인덱스*/
	&tex_mon_bug_drill_head,		/*그림*/
	&tex_player,				/*임시그림*/
	"땅굴벌레",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	15.0f,							/*근접공격*/

	100,							/*체력*/
	8.0f,						/*사이즈*/
	1.0f,						/*속도*/
	100.0f,						/*시야*/
	70,							/*경험치*/
	2,							/*인공지능*/

	MF_TRUE_SIGHT | MF_BUG,							/*플래그*/
};
monster_infor named__bug_fly_boss = 
{
	NAMED_FLY_BOSS,			/*인덱스*/
	&tex_mon_bug_fly_boss,		/*그림*/
	&tex_player,				/*임시그림*/
	"여왕벌레",				/*이름*/
	NULL,						/*무기*/
	50.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	120,							/*체력*/
	8.0f,						/*사이즈*/
	0.5f,						/*속도*/
	150.0f,						/*시야*/
	80,							/*경험치*/
	2,							/*인공지능*/

	MF_TRUE_SIGHT | MF_BUG,							/*플래그*/
};
monster_infor named__assasin = 
{
	NAMED_ASSASIN,			/*인덱스*/
	&tex_mon_spy,			/*그림*/
	&tex_player,				/*임시그림*/
	"스닉",					/*이름*/
	&rifle__mon_pistol_big,				/*무기*/
	30.0f,						/*최소거리*/
	35.0f,							/*최대거리*/
	1.5f,						/*패널티 배율*/
	5.0f,							/*근접공격*/

	40,							/*체력*/
	3.0f,						/*사이즈*/
	1.0f,						/*속도*/
	150.0f,						/*시야*/
	50,							/*경험치*/
	2,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};
monster_infor named__sniper = 
{
	NAMED_SNIPER,			/*인덱스*/
	&tex_mon_hunter,			/*그림*/
	&tex_player,				/*임시그림*/
	"호크헌츠",					/*이름*/
	&rifle__mon_sniper,				/*무기*/
	120.0f,						/*최소거리*/
	250.0f,							/*최대거리*/
	1.5f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	30,							/*체력*/
	3.0f,						/*사이즈*/
	1.0f,						/*속도*/
	150.0f,						/*시야*/
	60,							/*경험치*/
	5,							/*인공지능*/

	MF_TRUE_SIGHT | MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};

monster_infor named__zombie_virus = 
{
	NAMED_VIRUS,			/*인덱스*/
	&tex_mon_zombie_boomer,		/*그림*/
	&tex_player,				/*임시그림*/
	"도살자",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	20.0f,							/*근접공격*/

	120,							/*체력*/
	6.0f,						/*사이즈*/
	0.9f,						/*속도*/
	120.0f,						/*시야*/
	45,							/*경험치*/
	2,							/*인공지능*/

	MF_ZOMBIE,							/*플래그*/
};
monster_infor named__berserker = 
{
	NAMED_BERSERKER,			/*인덱스*/
	&tex_mon_berserker,			/*그림*/
	&tex_player,				/*임시그림*/
	"배이런",					/*이름*/
	NULL,				/*무기*/
	-10.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	1.0f,						/*패널티 배율*/
	12.0f,							/*근접공격*/

	45,							/*체력*/
	4.0f,						/*사이즈*/
	1.0f,						/*속도*/
	100.0f,						/*시야*/
	40,							/*경험치*/
	2,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};
monster_infor named__scream = 
{
	NAMED_SCREAM,			/*인덱스*/
	&tex_mon_zombie_noise,		/*그림*/
	&tex_player,				/*임시그림*/
	"비명",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	15.0f,							/*근접공격*/

	70,							/*체력*/
	4.0f,						/*사이즈*/
	0.8f,						/*속도*/
	120.0f,						/*시야*/
	30,							/*경험치*/
	2,							/*인공지능*/

	MF_ZOMBIE,							/*플래그*/
};

Unit* New_Named(Monster_Index kind_, coord_def pos_, int team_, int flag_, int time_)
{	
	monster_infor* p_monster = &named__jack;
	Unit* temp = NULL;
	switch(kind_)
	{
	case NAMED_JACK:
	default:
		p_monster = &named__jack;
		temp = new Named_jack(*p_monster, pos_.x, pos_.y, team_, time_);
		temp->SetWeapon(new Rifle((*p_monster->weapon), coord_def(), -1));
	break;
	case NAMED_LOOTER:
		p_monster = &named__looter;
		temp = new Named_jack(*p_monster, pos_.x, pos_.y, team_, time_);
		temp->SetDefResist(DT_VIRUS, true);
		temp->ApplyDefense(DT_POISON,0.5f);
	break;
	case NAMED_ROBOT:
		p_monster = &named__robot;
		temp = new Named_robot(*p_monster, pos_.x, pos_.y, team_, time_);
		temp->SetWeapon(new Double_pistol((*p_monster->weapon), coord_def(), -1));
		temp->SetWeapon(new Bazooka(rifle__mon_robot_bazooka, coord_def(), -1), new Grenade_gun(rifle__mon_robot_grenade, coord_def(), -1));
		temp->ApplyDefense(DT_SELF_EXPLOSION,0);
	break;
	case NAMED_DRILL:
		p_monster = &named__bug_drill;
		temp = new Named_bug_drill(*p_monster, pos_.x, pos_.y, team_, time_);
		temp->ApplyDefense(DT_FIRE,0.5f);
		temp->ApplyDefense(DT_EXPLOSION,0.5f);
	break;
	case NAMED_FLY_BOSS:
		p_monster = &named__bug_fly_boss;
		temp = new Named_fly_boss(*p_monster, pos_.x, pos_.y, team_, time_);
	break;
	case NAMED_ASSASIN:
		p_monster = &named__assasin;
		temp = new Named_Assasin(*p_monster, pos_.x, pos_.y, team_, time_);
		temp->SetWeapon(new Rifle((*p_monster->weapon), coord_def(), -1));
	break;
	case NAMED_SNIPER:
		p_monster = &named__sniper;
		temp = new Named_Sniper(*p_monster, pos_.x, pos_.y, team_, time_);
		temp->SetWeapon(new Sniper((*p_monster->weapon), coord_def(), -1));
	break;
	case NAMED_VIRUS:
		p_monster = &named__zombie_virus;
		temp = new Named_virus(*p_monster, pos_.x, pos_.y, team_, time_);
		temp->SetDefResist(DT_VIRUS, true);
		temp->ApplyDefense(DT_POISON,0.5f);
		break;
	case NAMED_BERSERKER:
		p_monster = &named__berserker;
		temp = new Named_Berserker(*p_monster, pos_.x, pos_.y, team_, time_);
		break;	
	case NAMED_SCREAM:
		p_monster = &named__scream;
		temp = new Named_Scream(*p_monster, pos_.x, pos_.y, team_, time_);
		temp->SetDefResist(DT_VIRUS, true);
		temp->ApplyDefense(DT_POISON,0.5f);
		break;	
	}
	temp->PlusFlag(flag_);
	temp->SetAi(MS_NORMAL, NULL, p_monster->level);
	return temp;
}