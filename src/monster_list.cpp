//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: monster_list.cpp
//
// ����: ���� ������ �����Լ�
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
	MON_WEAK_ZOMBIE,			/*�ε���*/
	&tex_mon_zombie_weak,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���� ����",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	10.0f,							/*��������*/

	30,							/*ü��*/
	3.0f,						/*������*/
	0.8f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	5,							/*����ġ*/
	0,							/*�ΰ�����*/

	MF_ZOMBIE,							/*�÷���*/
};
monster_infor monster__pistol_redneck = 
{
	MON_PISTOL_REDNECK,			/*�ε���*/
	&tex_mon_red_man,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���ġ",					/*�̸�*/
	&rifle__pistol,				/*����*/
	50.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	20,							/*ü��*/
	3.0f,						/*������*/
	0.7f,						/*�ӵ�*/
	90.0f,						/*�þ�*/
	10,							/*����ġ*/
	0,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};

monster_infor monster__big_zombie = 
{
	MON_BIG_ZOMBIE,			/*�ε���*/
	&tex_mon_zombie_big,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"�Ŵ��� ����",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	20.0f,							/*��������*/

	100,							/*ü��*/
	6.0f,						/*������*/
	0.6f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	20,							/*����ġ*/
	0,							/*�ΰ�����*/

	MF_ZOMBIE,							/*�÷���*/
};
monster_infor monster__bug_weak = 
{
	MON_BUG_WEAK,			/*�ε���*/
	&tex_mon_bug_weak,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���� ����",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	6.0f,							/*��������*/

	15,							/*ü��*/
	2.0f,						/*������*/
	1.5f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	10,							/*����ġ*/
	0,							/*�ΰ�����*/

	MF_BUG,							/*�÷���*/
};
monster_infor monster__pyro = 
{
	MON_PYRO,			/*�ε���*/
	&tex_mon_pyro,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���̷�",					/*�̸�*/
	&rifle__flame_thrower,				/*����*/
	20.0f,						/*�ּҰŸ�*/
	50.0f,							/*�ִ�Ÿ�*/
	2.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	60,							/*ü��*/
	3.0f,						/*������*/
	0.8f,						/*�ӵ�*/
	90.0f,						/*�þ�*/
	25,							/*����ġ*/
	1,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};


monster_infor monster__hunter = 
{
	MON_HUNTER,			/*�ε���*/
	&tex_mon_hunter,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"��ɲ�",					/*�̸�*/
	&rifle__shot_gun,				/*����*/
	30.0f,						/*�ּҰŸ�*/
	110.0f,							/*�ִ�Ÿ�*/
	2.5f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	35,							/*ü��*/
	3.0f,						/*������*/
	0.8f,						/*�ӵ�*/
	100.0f,						/*�þ�*/
	25,							/*����ġ*/
	1,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};
monster_infor monster__bug_bomb = 
{
	MON_BUG_BOMB,			/*�ε���*/
	&tex_mon_bug_bomb,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"��ź��",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	35.0f,							/*��������*/

	5,							/*ü��*/
	2.0f,						/*������*/
	1.2f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	10,							/*����ġ*/
	1,							/*�ΰ�����*/

	MF_BUG,							/*�÷���*/
};
monster_infor monster__bug_fly = 
{
	MON_BUG_FLY,			/*�ε���*/
	&tex_mon_bug_fly,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"ų���޶ѱ�",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	6.0f,							/*��������*/

	30,							/*ü��*/
	2.0f,						/*������*/
	1.1f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	15,							/*����ġ*/
	1,							/*�ΰ�����*/

	MF_BUG,							/*�÷���*/
};
monster_infor monster__virus_zombie = 
{
	MON_ZOMBIE_VIRUS,			/*�ε���*/
	&tex_mon_zombie_virus,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���̷��� ����",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	15.0f,							/*��������*/

	40,							/*ü��*/
	3.0f,						/*������*/
	1.0f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	15,							/*����ġ*/
	1,							/*�ΰ�����*/

	MF_ZOMBIE,							/*�÷���*/
};
monster_infor monster__rocket_man = 
{
	MON_ROCKET_MAN,			/*�ε���*/
	&tex_mon_rocket_man,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"����",					/*�̸�*/
	&rifle__mon_bazooka,				/*����*/
	70.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	50,							/*ü��*/
	3.0f,						/*������*/
	0.5f,						/*�ӵ�*/
	100.0f,						/*�þ�*/
	40,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};
monster_infor monster__blue_man = 
{
	MON_BLUE_MAN,			/*�ε���*/
	&tex_mon_blue_man,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"�뺴",					/*�̸�*/
	&rifle__mon_assault_rifle,				/*����*/
	50.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	1.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	20,							/*ü��*/
	3.0f,						/*������*/
	0.7f,						/*�ӵ�*/
	100.0f,						/*�þ�*/
	30,							/*����ġ*/
	3,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};

monster_infor monster__zombie_boomer = 
{
	MON_ZOMBIE_BOOMER,			/*�ε���*/
	&tex_mon_zombie_boomer,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���� ����",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	80.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	15.0f,							/*��������*/

	60,							/*ü��*/
	5.0f,						/*������*/
	0.6f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	30,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_ZOMBIE,							/*�÷���*/
};

monster_infor monster__zombie_ghost = 
{
	MON_ZOMBIE_GHOST,			/*�ε���*/
	&tex_mon_zombie_ghost,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"��Ʈ ����",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	15.0f,							/*��������*/

	40,							/*ü��*/
	3.0f,						/*������*/
	0.8f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	20,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_ZOMBIE,							/*�÷���*/
};
monster_infor monster__sf_man = 
{
	MON_SF_MAN,			/*�ε���*/
	&tex_mon_sf_man,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"Ư���δ�",					/*�̸�*/
	&rifle__mon_assault_rifle,				/*����*/
	70.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	1.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	35,							/*ü��*/
	3.0f,						/*������*/
	0.9f,						/*�ӵ�*/
	110.0f,						/*�þ�*/
	30,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};

monster_infor monster__water_man = 
{
	MON_WATER_MAN,			/*�ε���*/
	&tex_mon_water_man,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"�ҹ��",					/*�̸�*/
	&rifle__mon_water_gun,				/*����*/
	40.0f,						/*�ּҰŸ�*/
	80.0f,							/*�ִ�Ÿ�*/
	2.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	60,							/*ü��*/
	3.0f,						/*������*/
	0.8f,						/*�ӵ�*/
	90.0f,						/*�þ�*/
	25,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};


monster_infor monster__spy = 
{
	MON_SPY,			/*�ε���*/
	&tex_mon_spy,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"������",					/*�̸�*/
	&rifle__pistol,				/*����*/
	30.0f,						/*�ּҰŸ�*/
	40.0f,							/*�ִ�Ÿ�*/
	1.5f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	35,							/*ü��*/
	3.0f,						/*������*/
	0.6f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	20,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};

monster_infor monster__pyro2 = 
{
	MON_PYRO2,			/*�ε���*/
	&tex_mon_pyro2,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���̷�2",					/*�̸�*/
	&rifle__mon_bounce_fire,				/*����*/
	50.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	2.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	50,							/*ü��*/
	3.0f,						/*������*/
	0.8f,						/*�ӵ�*/
	90.0f,						/*�þ�*/
	30,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};
monster_infor monster__alert_robot = 
{
	MON_ALERT_ROBOT,			/*�ε���*/
	&tex_mon_alert_robot,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"�溸�κ�",					/*�̸�*/
	&rifle__mon_silence_gun,				/*����*/
	50.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	1.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	30,							/*ü��*/
	3.0f,						/*������*/
	0.8f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	20,							/*����ġ*/
	0,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_INVISIBLE_RESIST | MF_ROBOT,				/*�÷���*/
};

monster_infor monster__bug_fly2 = 
{
	MON_BUG_FLY2,			/*�ε���*/
	&tex_mon_bug_fly2,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"������",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	15.0f,							/*��������*/

	20,							/*ü��*/
	3.0f,						/*������*/
	2.0f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	20,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_TRUE_SIGHT | MF_BUG,							/*�÷���*/
};
monster_infor monster__bug_child_fly = 
{
	MON_BUG_CHILD_FLY,			/*�ε���*/
	&tex_mon_bug_fly2,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"������",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	12.0f,							/*��������*/

	20,							/*ü��*/
	3.0f,						/*������*/
	2.0f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	0,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_TRUE_SIGHT | MF_BUG,							/*�÷���*/
};

monster_infor monster__bug_ant_lion = 
{
	MON_BUG_ANT_LION,			/*�ε���*/
	&tex_mon_bug_ant_lion,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"��������",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	70.0f,							/*�ִ�Ÿ�*/
	1.0f,						/*�г�Ƽ ����*/
	20.0f,							/*��������*/

	40,							/*ü��*/
	4.0f,						/*������*/
	0.6f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	40,							/*����ġ*/
	3,							/*�ΰ�����*/

	MF_BUG,							/*�÷���*/
};



monster_infor monster__bug_beetle = 
{
	MON_BUG_BEETLE,			/*�ε���*/
	&tex_mon_bug_beetle,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"ǳ����",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	70.0f,							/*�ִ�Ÿ�*/
	1.0f,						/*�г�Ƽ ����*/
	20.0f,							/*��������*/

	80,							/*ü��*/
	5.0f,						/*������*/
	0.7f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	35,							/*����ġ*/
	3,							/*�ΰ�����*/

	MF_BUG,							/*�÷���*/
};
monster_infor monster__zombie_small = 
{
	MON_ZOMBIE_SMALL,			/*�ε���*/
	&tex_mon_zombie_small,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"����Ŀ",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	1.0f,						/*�г�Ƽ ����*/
	3.0f,							/*��������*/

	20,							/*ü��*/
	1.0f,						/*������*/
	1.6f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	15,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_ZOMBIE,							/*�÷���*/
};
monster_infor monster__zombie_noise = 
{
	MON_ZOMBIE_NOISE,			/*�ε���*/
	&tex_mon_zombie_noise,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���� ����",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	10.0f,							/*��������*/

	35,							/*ü��*/
	3.0f,						/*������*/
	0.8f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	10,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_ZOMBIE,							/*�÷���*/
};

monster_infor monster__stalker = 
{
	MON_STALKER,			/*�ε���*/
	&tex_mon_red_man,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"������",					/*�̸�*/
	&rifle__pistol,				/*����*/
	30.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	20,							/*ü��*/
	3.0f,						/*������*/
	1.0f,						/*�ӵ�*/
	100.0f,						/*�þ�*/
	15,							/*����ġ*/
	0,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};
monster_infor monster__bug_spider = 
{
	MON_SPIDER,			/*�ε���*/
	&tex_mon_spider,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"�Ź�",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	12.0f,							/*��������*/

	40,							/*ü��*/
	3.0f,						/*������*/
	0.8f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	20,							/*����ġ*/
	0,							/*�ΰ�����*/

	MF_BUG,							/*�÷���*/
};
monster_infor monster__bug_spider_baby = 
{
	MON_SPIDER_BABY,			/*�ε���*/
	&tex_mon_spider2,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"�����Ź�",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	5.0f,							/*��������*/

	5,							/*ü��*/
	2.0f,						/*������*/
	1.4f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	0,							/*����ġ*/
	0,							/*�ΰ�����*/

	MF_BUG,							/*�÷���*/
};
monster_infor monster__bug_fling = 
{
	MON_BUG_FLING,			/*�ε���*/
	&tex_mon_bug_fling,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"������",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	8.0f,							/*��������*/

	20,							/*ü��*/
	2.0f,						/*������*/
	1.6f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	20,							/*����ġ*/
	0,							/*�ΰ�����*/

	MF_BUG,							/*�÷���*/
};


monster_infor named__robot2 = 
{
	NAMED_ROBOT,			/*�ε���*/
	&tex_mon_robot,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���κ�",					/*�̸�*/
	&rifle__mon_robot_minigun,				/*����*/
	50.0f,						/*�ּҰŸ�*/
	120.0f,							/*�ִ�Ÿ�*/
	1.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	150/*200*/,							/*ü��*/
	5.0f,						/*������*/
	0.7f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	200,							/*����ġ*/
	3,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_ROBOT,				/*�÷���*/
};

monster_infor monster__zombie_stone = 
{
	MON_ZOMBIE_STONE,			/*�ε���*/
	&tex_mon_rock_giant,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���� ����",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	150.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	15.0f,							/*��������*/

	100,							/*ü��*/
	5.0f,						/*������*/
	0.6f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	30,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_ZOMBIE,							/*�÷���*/
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