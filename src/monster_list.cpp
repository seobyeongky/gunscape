//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: monster_list.cpp
//
// 내용: 몬스터 종류와 생성함수
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "monster_list.h"
#include "texture_list.h"
#include "rifle.h"
#include "fire.h"
#include "fire2.h"
#include "water.h"
#include "burrow.h"
#include "burrow2.h"
#include "mon_hunter.h"
#include "mon_bug_bomb.h"
#include "mon_bug_fly.h"
#include "mon_bug_fly2.h"
#include "mon_zombie_boomer.h"
#include "mon_zombie_virus.h"
#include "mon_zombie_ghost.h"
#include "mon_sf_man.h"
#include "mon_spy.h"
#include "mon_bug_ant_lion.h"
#include "mon_bug_beetle.h"
#include "mon_zombie_small.h"
#include "mon_zombie_noise.h"
#include "mon_stalker.h"
#include "mon_bug_spider.h"
#include "mon_big_zombie.h"
#include "mon_alert_robot.h"
#include "mon_bug_fling.h"
#include "named_robot.h"
#include "grenade_gun.h"
#include "double_pistol.h"
#include "bazooka.h"
#include "random.h"


monster_infor monster__weak_zombie = 
{
	MON_WEAK_ZOMBIE,			/*인덱스*/
	&tex_mon_zombie_weak,		/*그림*/
	&tex_player,				/*임시그림*/
	"약한 좀비",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	10.0f,							/*근접공격*/

	30,							/*체력*/
	3.0f,						/*사이즈*/
	0.8f,						/*속도*/
	120.0f,						/*시야*/
	5,							/*경험치*/
	0,							/*인공지능*/

	MF_ZOMBIE,							/*플래그*/
};
monster_infor monster__pistol_redneck = 
{
	MON_PISTOL_REDNECK,			/*인덱스*/
	&tex_mon_red_man,			/*그림*/
	&tex_player,				/*임시그림*/
	"양아치",					/*이름*/
	&rifle__pistol,				/*무기*/
	50.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	20,							/*체력*/
	3.0f,						/*사이즈*/
	0.7f,						/*속도*/
	90.0f,						/*시야*/
	10,							/*경험치*/
	0,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};

monster_infor monster__big_zombie = 
{
	MON_BIG_ZOMBIE,			/*인덱스*/
	&tex_mon_zombie_big,		/*그림*/
	&tex_player,				/*임시그림*/
	"거대한 좀비",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	20.0f,							/*근접공격*/

	100,							/*체력*/
	6.0f,						/*사이즈*/
	0.6f,						/*속도*/
	120.0f,						/*시야*/
	20,							/*경험치*/
	0,							/*인공지능*/

	MF_ZOMBIE,							/*플래그*/
};
monster_infor monster__bug_weak = 
{
	MON_BUG_WEAK,			/*인덱스*/
	&tex_mon_bug_weak,		/*그림*/
	&tex_player,				/*임시그림*/
	"작은 벌레",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	6.0f,							/*근접공격*/

	15,							/*체력*/
	2.0f,						/*사이즈*/
	1.5f,						/*속도*/
	150.0f,						/*시야*/
	10,							/*경험치*/
	0,							/*인공지능*/

	MF_BUG,							/*플래그*/
};
monster_infor monster__pyro = 
{
	MON_PYRO,			/*인덱스*/
	&tex_mon_pyro,			/*그림*/
	&tex_player,				/*임시그림*/
	"파이로",					/*이름*/
	&rifle__flame_thrower,				/*무기*/
	20.0f,						/*최소거리*/
	50.0f,							/*최대거리*/
	2.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	60,							/*체력*/
	3.0f,						/*사이즈*/
	0.8f,						/*속도*/
	90.0f,						/*시야*/
	25,							/*경험치*/
	1,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};


monster_infor monster__hunter = 
{
	MON_HUNTER,			/*인덱스*/
	&tex_mon_hunter,			/*그림*/
	&tex_player,				/*임시그림*/
	"사냥꾼",					/*이름*/
	&rifle__shot_gun,				/*무기*/
	30.0f,						/*최소거리*/
	110.0f,							/*최대거리*/
	2.5f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	35,							/*체력*/
	3.0f,						/*사이즈*/
	0.8f,						/*속도*/
	100.0f,						/*시야*/
	25,							/*경험치*/
	1,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};
monster_infor monster__bug_bomb = 
{
	MON_BUG_BOMB,			/*인덱스*/
	&tex_mon_bug_bomb,		/*그림*/
	&tex_player,				/*임시그림*/
	"폭탄충",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	35.0f,							/*근접공격*/

	5,							/*체력*/
	2.0f,						/*사이즈*/
	1.2f,						/*속도*/
	150.0f,						/*시야*/
	10,							/*경험치*/
	1,							/*인공지능*/

	MF_BUG,							/*플래그*/
};
monster_infor monster__bug_fly = 
{
	MON_BUG_FLY,			/*인덱스*/
	&tex_mon_bug_fly,		/*그림*/
	&tex_player,				/*임시그림*/
	"킬러메뚜기",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	6.0f,							/*근접공격*/

	30,							/*체력*/
	2.0f,						/*사이즈*/
	1.1f,						/*속도*/
	150.0f,						/*시야*/
	15,							/*경험치*/
	1,							/*인공지능*/

	MF_BUG,							/*플래그*/
};
monster_infor monster__virus_zombie = 
{
	MON_ZOMBIE_VIRUS,			/*인덱스*/
	&tex_mon_zombie_virus,		/*그림*/
	&tex_player,				/*임시그림*/
	"바이러스 좀비",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	15.0f,							/*근접공격*/

	40,							/*체력*/
	3.0f,						/*사이즈*/
	1.0f,						/*속도*/
	120.0f,						/*시야*/
	15,							/*경험치*/
	1,							/*인공지능*/

	MF_ZOMBIE,							/*플래그*/
};
monster_infor monster__rocket_man = 
{
	MON_ROCKET_MAN,			/*인덱스*/
	&tex_mon_rocket_man,			/*그림*/
	&tex_player,				/*임시그림*/
	"포병",					/*이름*/
	&rifle__mon_bazooka,				/*무기*/
	70.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	50,							/*체력*/
	3.0f,						/*사이즈*/
	0.5f,						/*속도*/
	100.0f,						/*시야*/
	40,							/*경험치*/
	2,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};
monster_infor monster__blue_man = 
{
	MON_BLUE_MAN,			/*인덱스*/
	&tex_mon_blue_man,			/*그림*/
	&tex_player,				/*임시그림*/
	"용병",					/*이름*/
	&rifle__mon_assault_rifle,				/*무기*/
	50.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	1.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	20,							/*체력*/
	3.0f,						/*사이즈*/
	0.7f,						/*속도*/
	100.0f,						/*시야*/
	30,							/*경험치*/
	3,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};

monster_infor monster__zombie_boomer = 
{
	MON_ZOMBIE_BOOMER,			/*인덱스*/
	&tex_mon_zombie_boomer,		/*그림*/
	&tex_player,				/*임시그림*/
	"구토 좀비",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	80.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	15.0f,							/*근접공격*/

	60,							/*체력*/
	5.0f,						/*사이즈*/
	0.6f,						/*속도*/
	120.0f,						/*시야*/
	30,							/*경험치*/
	2,							/*인공지능*/

	MF_ZOMBIE,							/*플래그*/
};

monster_infor monster__zombie_ghost = 
{
	MON_ZOMBIE_GHOST,			/*인덱스*/
	&tex_mon_zombie_ghost,		/*그림*/
	&tex_player,				/*임시그림*/
	"고스트 좀비",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	15.0f,							/*근접공격*/

	40,							/*체력*/
	3.0f,						/*사이즈*/
	0.8f,						/*속도*/
	120.0f,						/*시야*/
	20,							/*경험치*/
	2,							/*인공지능*/

	MF_ZOMBIE,							/*플래그*/
};
monster_infor monster__sf_man = 
{
	MON_SF_MAN,			/*인덱스*/
	&tex_mon_sf_man,			/*그림*/
	&tex_player,				/*임시그림*/
	"특수부대",					/*이름*/
	&rifle__mon_assault_rifle,				/*무기*/
	70.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	1.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	35,							/*체력*/
	3.0f,						/*사이즈*/
	0.9f,						/*속도*/
	110.0f,						/*시야*/
	30,							/*경험치*/
	2,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};

monster_infor monster__water_man = 
{
	MON_WATER_MAN,			/*인덱스*/
	&tex_mon_water_man,			/*그림*/
	&tex_player,				/*임시그림*/
	"소방수",					/*이름*/
	&rifle__mon_water_gun,				/*무기*/
	40.0f,						/*최소거리*/
	80.0f,							/*최대거리*/
	2.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	60,							/*체력*/
	3.0f,						/*사이즈*/
	0.8f,						/*속도*/
	90.0f,						/*시야*/
	25,							/*경험치*/
	2,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};


monster_infor monster__spy = 
{
	MON_SPY,			/*인덱스*/
	&tex_mon_spy,			/*그림*/
	&tex_player,				/*임시그림*/
	"스파이",					/*이름*/
	&rifle__pistol,				/*무기*/
	30.0f,						/*최소거리*/
	40.0f,							/*최대거리*/
	1.5f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	35,							/*체력*/
	3.0f,						/*사이즈*/
	0.6f,						/*속도*/
	150.0f,						/*시야*/
	20,							/*경험치*/
	2,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};

monster_infor monster__pyro2 = 
{
	MON_PYRO2,			/*인덱스*/
	&tex_mon_pyro2,			/*그림*/
	&tex_player,				/*임시그림*/
	"파이로2",					/*이름*/
	&rifle__mon_bounce_fire,				/*무기*/
	50.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	2.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	50,							/*체력*/
	3.0f,						/*사이즈*/
	0.8f,						/*속도*/
	90.0f,						/*시야*/
	30,							/*경험치*/
	2,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};
monster_infor monster__alert_robot = 
{
	MON_ALERT_ROBOT,			/*인덱스*/
	&tex_mon_alert_robot,			/*그림*/
	&tex_player,				/*임시그림*/
	"경보로봇",					/*이름*/
	&rifle__mon_silence_gun,				/*무기*/
	50.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	1.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	30,							/*체력*/
	3.0f,						/*사이즈*/
	0.8f,						/*속도*/
	120.0f,						/*시야*/
	20,							/*경험치*/
	0,							/*인공지능*/

	MF_DROP_BULLET | MF_INVISIBLE_RESIST | MF_ROBOT,				/*플래그*/
};

monster_infor monster__bug_fly2 = 
{
	MON_BUG_FLY2,			/*인덱스*/
	&tex_mon_bug_fly2,		/*그림*/
	&tex_player,				/*임시그림*/
	"비행충",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	15.0f,							/*근접공격*/

	20,							/*체력*/
	3.0f,						/*사이즈*/
	2.0f,						/*속도*/
	120.0f,						/*시야*/
	20,							/*경험치*/
	2,							/*인공지능*/

	MF_TRUE_SIGHT | MF_BUG,							/*플래그*/
};
monster_infor monster__bug_child_fly = 
{
	MON_BUG_CHILD_FLY,			/*인덱스*/
	&tex_mon_bug_fly2,		/*그림*/
	&tex_player,				/*임시그림*/
	"비행충",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	12.0f,							/*근접공격*/

	20,							/*체력*/
	3.0f,						/*사이즈*/
	2.0f,						/*속도*/
	120.0f,						/*시야*/
	0,							/*경험치*/
	2,							/*인공지능*/

	MF_TRUE_SIGHT | MF_BUG,							/*플래그*/
};

monster_infor monster__bug_ant_lion = 
{
	MON_BUG_ANT_LION,			/*인덱스*/
	&tex_mon_bug_ant_lion,		/*그림*/
	&tex_player,				/*임시그림*/
	"개미지옥",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	70.0f,							/*최대거리*/
	1.0f,						/*패널티 배율*/
	20.0f,							/*근접공격*/

	40,							/*체력*/
	4.0f,						/*사이즈*/
	0.6f,						/*속도*/
	150.0f,						/*시야*/
	40,							/*경험치*/
	3,							/*인공지능*/

	MF_BUG,							/*플래그*/
};



monster_infor monster__bug_beetle = 
{
	MON_BUG_BEETLE,			/*인덱스*/
	&tex_mon_bug_beetle,		/*그림*/
	&tex_player,				/*임시그림*/
	"풍뎅이",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	70.0f,							/*최대거리*/
	1.0f,						/*패널티 배율*/
	20.0f,							/*근접공격*/

	80,							/*체력*/
	5.0f,						/*사이즈*/
	0.7f,						/*속도*/
	150.0f,						/*시야*/
	35,							/*경험치*/
	3,							/*인공지능*/

	MF_BUG,							/*플래그*/
};
monster_infor monster__zombie_small = 
{
	MON_ZOMBIE_SMALL,			/*인덱스*/
	&tex_mon_zombie_small,		/*그림*/
	&tex_player,				/*임시그림*/
	"스토커",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	1.0f,						/*패널티 배율*/
	3.0f,							/*근접공격*/

	20,							/*체력*/
	1.0f,						/*사이즈*/
	1.6f,						/*속도*/
	120.0f,						/*시야*/
	15,							/*경험치*/
	2,							/*인공지능*/

	MF_ZOMBIE,							/*플래그*/
};
monster_infor monster__zombie_noise = 
{
	MON_ZOMBIE_NOISE,			/*인덱스*/
	&tex_mon_zombie_noise,		/*그림*/
	&tex_player,				/*임시그림*/
	"소음 좀비",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	10.0f,							/*근접공격*/

	35,							/*체력*/
	3.0f,						/*사이즈*/
	0.8f,						/*속도*/
	120.0f,						/*시야*/
	10,							/*경험치*/
	2,							/*인공지능*/

	MF_ZOMBIE,							/*플래그*/
};

monster_infor monster__stalker = 
{
	MON_STALKER,			/*인덱스*/
	&tex_mon_red_man,			/*그림*/
	&tex_player,				/*임시그림*/
	"추적자",					/*이름*/
	&rifle__pistol,				/*무기*/
	30.0f,						/*최소거리*/
	100.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	0.0f,							/*근접공격*/

	20,							/*체력*/
	3.0f,						/*사이즈*/
	1.0f,						/*속도*/
	100.0f,						/*시야*/
	15,							/*경험치*/
	0,							/*인공지능*/

	MF_DROP_BULLET | MF_HUMAN,				/*플래그*/
};
monster_infor monster__bug_spider = 
{
	MON_SPIDER,			/*인덱스*/
	&tex_mon_spider,		/*그림*/
	&tex_player,				/*임시그림*/
	"거미",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	12.0f,							/*근접공격*/

	40,							/*체력*/
	3.0f,						/*사이즈*/
	0.8f,						/*속도*/
	150.0f,						/*시야*/
	20,							/*경험치*/
	0,							/*인공지능*/

	MF_BUG,							/*플래그*/
};
monster_infor monster__bug_spider_baby = 
{
	MON_SPIDER_BABY,			/*인덱스*/
	&tex_mon_spider2,		/*그림*/
	&tex_player,				/*임시그림*/
	"새끼거미",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	5.0f,							/*근접공격*/

	5,							/*체력*/
	2.0f,						/*사이즈*/
	1.4f,						/*속도*/
	150.0f,						/*시야*/
	0,							/*경험치*/
	0,							/*인공지능*/

	MF_BUG,							/*플래그*/
};
monster_infor monster__bug_fling = 
{
	MON_BUG_FLING,			/*인덱스*/
	&tex_mon_bug_fling,		/*그림*/
	&tex_player,				/*임시그림*/
	"뒤집개",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	10.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	8.0f,							/*근접공격*/

	20,							/*체력*/
	2.0f,						/*사이즈*/
	1.6f,						/*속도*/
	150.0f,						/*시야*/
	20,							/*경험치*/
	0,							/*인공지능*/

	MF_BUG,							/*플래그*/
};


monster_infor named__robot2 = 
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

	MF_DROP_BULLET | MF_ROBOT,				/*플래그*/
};

monster_infor monster__zombie_stone = 
{
	MON_ZOMBIE_STONE,			/*인덱스*/
	&tex_mon_rock_giant,		/*그림*/
	&tex_player,				/*임시그림*/
	"바위 좀비",				/*이름*/
	NULL,						/*무기*/
	-20.0f,						/*최소거리*/
	150.0f,							/*최대거리*/
	3.0f,						/*패널티 배율*/
	15.0f,							/*근접공격*/

	100,							/*체력*/
	5.0f,						/*사이즈*/
	0.6f,						/*속도*/
	120.0f,						/*시야*/
	30,							/*경험치*/
	2,							/*인공지능*/

	MF_ZOMBIE,							/*플래그*/
};




Unit* New_Monster(Monster_Index kind_, coord_def pos_, int team_, int flag_, int time_)
{
	Unit* temp = NULL;
	monster_infor* p_monster = &monster__weak_zombie;
	bool no_ai = false;

	if(flag_ & MF_BURROW)
	{		
		temp = new Burrow2(pos_, 60,kind_);
		no_ai = true;
	}
	else
	{
		switch(kind_)
		{
		case MON_WEAK_ZOMBIE:
		default:
			p_monster = &monster__weak_zombie;
			temp = new Monster(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetDefResist(DT_VIRUS, true);
			temp->ApplyDefense(DT_POISON,0.5f);
			break;
		case MON_PISTOL_REDNECK:
			p_monster = &monster__pistol_redneck;
			temp = new Monster(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Rifle((*p_monster->weapon), coord_def(), -1));
			break;
		case MON_BIG_ZOMBIE:
			p_monster = &monster__big_zombie;
			temp = new Monster(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetDefResist(DT_VIRUS, true);
			temp->ApplyDefense(DT_POISON,0.5f);
			break;
		case MON_BUG_WEAK:
			p_monster = &monster__bug_weak;
			temp = new Monster(*p_monster, pos_.x, pos_.y, team_, time_);
			break;
		case MON_PYRO:
			p_monster = &monster__pyro;
			temp = new Monster(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Fire((*p_monster->weapon), coord_def(), -1));
			break;
		case MON_ZOMBIE_GROUP_1:
			temp = new Burrow(pos_, 80, 100.0f, BT_SMALL_ZOMBIE);
			no_ai = true;
			break;
		case MON_ZOMBIE_GROUP_2:
			temp = new Burrow(pos_, 80, 100.0f, BT_ZOMBIE_VIRUS);
			no_ai = true;
			break;
		case MON_ZOMBIE_GROUP_3:
			temp = new Burrow(pos_, 80, 100.0f, BT_ZOMBIE_VIRUS_SMALL);
			no_ai = true;
			break;
		case MON_HUNTER:
			p_monster = &monster__hunter;
			temp = new Mon_hunter(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Rifle((*p_monster->weapon), coord_def(), -1));
			break;
		case MON_BUG_BOMB:
			p_monster = &monster__bug_bomb;
			temp = new Mon_bug_bomb(*p_monster, pos_.x, pos_.y, team_, time_);
			break;
		case MON_BUG_FLY:
			p_monster = &monster__bug_fly;
			temp = new Mon_bug_fly(*p_monster, pos_.x, pos_.y, team_, time_);
			break;
		case MON_ZOMBIE_VIRUS:
			p_monster = &monster__virus_zombie;
			temp = new Mon_zombie_virus(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetDefResist(DT_VIRUS, true);
			temp->ApplyDefense(DT_POISON,0.5f);
			break;
		case MON_ROCKET_MAN:
			p_monster = &monster__rocket_man;
			temp = new Monster(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Bazooka((*p_monster->weapon), coord_def(), -1));
			break;
		case MON_BLUE_MAN:
			p_monster = &monster__blue_man;
			temp = new Monster(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Rifle((*p_monster->weapon), coord_def(), -1));
			break;
		case MON_ZOMBIE_BOOMER:
			p_monster = &monster__zombie_boomer;
			temp = new Mon_zombie_boomer(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetDefResist(DT_VIRUS, true);
			temp->ApplyDefense(DT_POISON,0.5f);
			break;
		case MON_ZOMBIE_GHOST:
			p_monster = &monster__zombie_ghost;
			temp = new Mon_zombie_ghost(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetDefResist(DT_VIRUS, true);
			temp->ApplyDefense(DT_POISON,0.5f);
			break;
		case MON_SF_MAN:
			p_monster = &monster__sf_man;
			temp = new Mon_sf_man(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Rifle((*p_monster->weapon), coord_def(), -1));
			temp->SeFogResist(true);
			break;
		case MON_WATER_MAN:
			p_monster = &monster__water_man;
			temp = new Monster(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Water((*p_monster->weapon), coord_def(), -1));
			break;
		case MON_SPY:
			p_monster = &monster__spy;
			temp = new Mon_spy(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Rifle((*p_monster->weapon), coord_def(), -1));
			break;
		case MON_PYRO2:
			p_monster = &monster__pyro2;
			temp = new Monster(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Fire2((*p_monster->weapon), coord_def(), -1));
			break;
		case MON_ALERT_ROBOT:
			p_monster = &monster__alert_robot;
			temp = new Mon_alert_robot(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Rifle((*p_monster->weapon), coord_def(), -1));
			temp->SetDefResist(DT_VIRUS, true);
			temp->ApplyDefense(DT_POISON,0.5f);
			break;
		case MON_BUG_FLY2:
			p_monster = &monster__bug_fly2;
			temp = new Mon_bug_fly2(*p_monster, pos_.x, pos_.y, team_, time_);
			break;
		case MON_BUG_ANT_LION:
			p_monster = &monster__bug_ant_lion;
			temp = new Mon_bug_ant_lion(*p_monster, pos_.x, pos_.y, team_, time_);
			break;
		case MON_BUG_BEETLE:
			p_monster = &monster__bug_beetle;
			temp = new Mon_bug_beetle(*p_monster, pos_.x, pos_.y, team_, time_);
			break;
		case MON_ZOMBIE_SMALL:
			p_monster = &monster__zombie_small;
			temp = new Mon_zombie_small(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetDefResist(DT_VIRUS, true);
			temp->ApplyDefense(DT_POISON,0.5f);
			break;
		case MON_ZOMBIE_NOISE:
			p_monster = &monster__zombie_noise;
			temp = new Mon_zombie_noise(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetDefResist(DT_VIRUS, true);
			temp->ApplyDefense(DT_POISON,0.5f);
			break;
		case MON_STALKER:
			p_monster = &monster__stalker;
			temp = new Mon_stalker(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Rifle((*p_monster->weapon), coord_def(), -1));
			break;
		case MON_SPIDER:
			p_monster = &monster__bug_spider;
			temp = new Mon_bug_spider(*p_monster, pos_.x, pos_.y, team_, time_);
			break;
		case MON_SPIDER_BABY:
			p_monster = &monster__bug_spider_baby;
			temp = new Monster(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetInvincible(1);
			temp->SetKnockback(4.0f, 4.0f, rand_float(0,D3DX_PI*2));
			break;
		case MON_BUG_FLING:
			p_monster = &monster__bug_fling;
			temp = new Mon_bug_filng(*p_monster, pos_.x, pos_.y, team_, time_);
			break;
		case NAMED_ROBOT:
			p_monster = &named__robot2;
			temp = new Named_robot(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetWeapon(new Double_pistol((*p_monster->weapon), coord_def(), -1));
			temp->SetWeapon(new Bazooka(rifle__mon_robot_bazooka, coord_def(), -1), new Grenade_gun(rifle__mon_robot_grenade, coord_def(), -1));
			temp->ApplyDefense(DT_SELF_EXPLOSION,0);
			temp->SetDefResist(DT_VIRUS, true);
			temp->ApplyDefense(DT_POISON,0.5f);
			break;
		case MON_ZOMBIE_STONE:
			p_monster = &monster__zombie_stone;
			temp = new Mon_big_zombie(*p_monster, pos_.x, pos_.y, team_, time_);
			temp->SetDefResist(DT_VIRUS, true);
			temp->ApplyDefense(DT_POISON,0.5f);
			break;
		}
	}
	temp->PlusFlag(flag_);
	if(!no_ai)
		temp->SetAi(MS_NORMAL, NULL, p_monster->level);
	return temp;
}