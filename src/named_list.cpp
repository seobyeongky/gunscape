//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: named_list.cpp
//
// ����: ���� ������ �����Լ�
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
	NAMED_JACK,			/*�ε���*/
	&tex_mon_sf_man,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"��",					/*�̸�*/
	&rifle__pistol,				/*����*/
	50.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	1.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	50,							/*ü��*/
	3.0f,						/*������*/
	1.0f,						/*�ӵ�*/
	100.0f,						/*�þ�*/
	30,							/*����ġ*/
	3,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};

monster_infor named__looter = 
{
	NAMED_LOOTER,			/*�ε���*/
	&tex_mon_zombie_weak,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"��Ż��",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	15.0f,							/*��������*/

	60,							/*ü��*/
	3.0f,						/*������*/
	1.1f,						/*�ӵ�*/
	180.0f,						/*�þ�*/
	25,							/*����ġ*/
	0,							/*�ΰ�����*/

	MF_ZOMBIE,							/*�÷���*/
};
monster_infor named__robot = 
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

	MF_DROP_BULLET,				/*�÷���*/
};
monster_infor named__bug_drill = 
{
	NAMED_DRILL,			/*�ε���*/
	&tex_mon_bug_drill_head,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"��������",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	10.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	15.0f,							/*��������*/

	100,							/*ü��*/
	8.0f,						/*������*/
	1.0f,						/*�ӵ�*/
	100.0f,						/*�þ�*/
	70,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_TRUE_SIGHT | MF_BUG,							/*�÷���*/
};
monster_infor named__bug_fly_boss = 
{
	NAMED_FLY_BOSS,			/*�ε���*/
	&tex_mon_bug_fly_boss,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���չ���",				/*�̸�*/
	NULL,						/*����*/
	50.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	120,							/*ü��*/
	8.0f,						/*������*/
	0.5f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	80,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_TRUE_SIGHT | MF_BUG,							/*�÷���*/
};
monster_infor named__assasin = 
{
	NAMED_ASSASIN,			/*�ε���*/
	&tex_mon_spy,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"����",					/*�̸�*/
	&rifle__mon_pistol_big,				/*����*/
	30.0f,						/*�ּҰŸ�*/
	35.0f,							/*�ִ�Ÿ�*/
	1.5f,						/*�г�Ƽ ����*/
	5.0f,							/*��������*/

	40,							/*ü��*/
	3.0f,						/*������*/
	1.0f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	50,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};
monster_infor named__sniper = 
{
	NAMED_SNIPER,			/*�ε���*/
	&tex_mon_hunter,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"ȣũ����",					/*�̸�*/
	&rifle__mon_sniper,				/*����*/
	120.0f,						/*�ּҰŸ�*/
	250.0f,							/*�ִ�Ÿ�*/
	1.5f,						/*�г�Ƽ ����*/
	0.0f,							/*��������*/

	30,							/*ü��*/
	3.0f,						/*������*/
	1.0f,						/*�ӵ�*/
	150.0f,						/*�þ�*/
	60,							/*����ġ*/
	5,							/*�ΰ�����*/

	MF_TRUE_SIGHT | MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};

monster_infor named__zombie_virus = 
{
	NAMED_VIRUS,			/*�ε���*/
	&tex_mon_zombie_boomer,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"������",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	20.0f,							/*��������*/

	120,							/*ü��*/
	6.0f,						/*������*/
	0.9f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	45,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_ZOMBIE,							/*�÷���*/
};
monster_infor named__berserker = 
{
	NAMED_BERSERKER,			/*�ε���*/
	&tex_mon_berserker,			/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���̷�",					/*�̸�*/
	NULL,				/*����*/
	-10.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	1.0f,						/*�г�Ƽ ����*/
	12.0f,							/*��������*/

	45,							/*ü��*/
	4.0f,						/*������*/
	1.0f,						/*�ӵ�*/
	100.0f,						/*�þ�*/
	40,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_DROP_BULLET | MF_HUMAN,				/*�÷���*/
};
monster_infor named__scream = 
{
	NAMED_SCREAM,			/*�ε���*/
	&tex_mon_zombie_noise,		/*�׸�*/
	&tex_player,				/*�ӽñ׸�*/
	"���",				/*�̸�*/
	NULL,						/*����*/
	-20.0f,						/*�ּҰŸ�*/
	100.0f,							/*�ִ�Ÿ�*/
	3.0f,						/*�г�Ƽ ����*/
	15.0f,							/*��������*/

	70,							/*ü��*/
	4.0f,						/*������*/
	0.8f,						/*�ӵ�*/
	120.0f,						/*�þ�*/
	30,							/*����ġ*/
	2,							/*�ΰ�����*/

	MF_ZOMBIE,							/*�÷���*/
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