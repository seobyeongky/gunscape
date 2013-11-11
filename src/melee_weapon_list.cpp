//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: melee_weapon_list.cpp
//
// ����: �и���������
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "melee_weapon_list.h"
#include "texture_list.h"
#include "hammer.h"
#include "gamemanager.h"
#include "sound.h"
#include "unit.h"
#include "shot_melee.h"

melee_weapon_infor melee__knife = 
{
	MK_KNIFE,/*����*/
	&tex_item_unknown,/*���� ������ �̹���*/
	&tex_inter_knife,/*������ �̹���*/
	&tex_melee,/*�ֵθ��� �̹���*/
	"������",/*�̸�*/
	"�ϻ� ������ ��������",
	1.0f,/*�̼Ӱ��Һ���*/
	1.0f,/*���ӵ�*/
	1.0f, /*����ӵ� ����*/
	1.0f, /*������ ����*/
	8.0f, /*��Ÿ�*/
	0.1f, //���� ��ġ������
	3.0f, //���� ��ġ�� �ְ�ġ
	//-----
	15,/*����*/
	5.0f,/*���ݷ�*/
	0.5f,/*����*/
	8.0f,/*�齺��*/
	1.0f/*������ �г�Ƽ*/
};


melee_weapon_infor melee__club = 
{
	MK_CLUB,/*����*/
	&tex_item_unknown,/*���� ������ �̹���*/
	&tex_inter_club,/*������ �̹���*/
	&tex_melee,/*�ֵθ��� �̹���*/
	"���",/*�̸�*/
	"�˹��� ���� ��������",
	1.0f,/*�̼Ӱ��Һ���*/
	1.0f,/*���ӵ�*/
	1.0f, /*����ӵ� ����*/
	1.0f, /*������ ����*/
	10.0f, /*��Ÿ�*/
	3.0f, //���� ��ġ������
	5.0f, //���� ��ġ�� �ְ�ġ
	//-----
	30,/*����*/
	15.0f,/*���ݷ�*/
	0.7f,/*����*/
	0.0f,/*�齺��*/
	1.0f/*������ �г�Ƽ*/
};

melee_weapon_infor melee__axe = 
{
	MK_AXE,/*����*/
	&tex_item_unknown,/*���� ������ �̹���*/
	&tex_inter_axe,/*������ �̹���*/
	&tex_melee,/*�ֵθ��� �̹���*/
	"�ҹ浵��",/*�̸�*/
	"������ ���� ��������",
	0.95f,/*�̼Ӱ��Һ���*/
	1.0f,/*���ӵ�*/
	1.0f, /*����ӵ� ����*/
	1.0f, /*������ ����*/
	10.0f, /*��Ÿ�*/
	0.5f, //���� ��ġ������
	5.0f, //���� ��ġ�� �ְ�ġ
	//-----
	50,/*����*/
	25.0f,/*���ݷ�*/
	0.8f,/*����*/
	0.0f,/*�齺��*/
	1.0f/*������ �г�Ƽ*/
};
melee_weapon_infor melee__spear = 
{
	MK_SPEAR,/*����*/
	&tex_item_unknown,/*���� ������ �̹���*/
	&tex_inter_spear,/*������ �̹���*/
	&tex_melee3,/*�ֵθ��� �̹���*/
	"â",/*�̸�*/
	"��Ÿ��� �� ����",
	0.9f,/*�̼Ӱ��Һ���*/
	1.0f,/*���ӵ�*/
	1.0f, /*����ӵ� ����*/
	1.0f, /*������ ����*/
	25.0f, /*��Ÿ�*/
	0.1f, //���� ��ġ������
	3.0f, //���� ��ġ�� �ְ�ġ
	//-----
	60,/*����*/
	20.0f,/*���ݷ�*/
	0.5f,/*����*/
	0.0f,/*�齺��*/
	1.42f/*������ �г�Ƽ*/
};

melee_weapon_infor melee__hammer = 
{
	MK_HAMMER,/*����*/
	&tex_item_unknown,/*���� ������ �̹���*/
	&tex_inter_hammer,/*������ �̹���*/
	&tex_melee,/*�ֵθ��� �̹���*/
	"�ظ�",/*�̸�*/
	"���� ��븦 ����������\n",
	1.0f,/*�̼Ӱ��Һ���*/
	1.0f,/*���ӵ�*/
	1.0f, /*����ӵ� ����*/
	1.0f, /*������ ����*/
	10.0f, /*��Ÿ�*/
	3.0f, //���� ��ġ������
	5.0f, //���� ��ġ�� �ְ�ġ
	//-----
	40,/*����*/
	20.0f,/*���ݷ�*/
	0.9f,/*����*/
	0.0f,/*�齺��*/
	1.0f/*������ �г�Ƽ*/
};

melee_weapon_infor melee__assasin_knife = 
{
	MK_ASSASIN_KNIFE,/*����*/
	&tex_item_unknown,/*���� ������ �̹���*/
	&tex_inter_knife,/*������ �̹���*/
	&tex_melee,/*�ֵθ��� �̹���*/
	"���",/*�̸�*/
	"�ϻ������� �ܰ�",
	1.0f,/*�̼Ӱ��Һ���*/
	1.0f,/*���ӵ�*/
	1.0f, /*����ӵ� ����*/
	1.0f, /*������ ����*/
	8.0f, /*��Ÿ�*/
	0.1f, //���� ��ġ������
	3.0f, //���� ��ġ�� �ְ�ġ
	//-----
	30,/*����*/
	3.0f,/*���ݷ�*/
	0.5f,/*����*/
	18.0f,/*�齺��*/
	0.0f/*������ �г�Ƽ*/
};

class Melee_Knife : public Melee_Weapon
{
public:
	Melee_Knife::Melee_Knife(const melee_weapon_infor& infor_, coord_def pos_, int time_):
	Melee_Weapon(infor_, pos_, time_)
	{
	}
	float Melee_Knife::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
	{
		if (gm_->isPlayerCanHear(GetPos()))
		{
			PlaySE(se_knife);
		}
		float angle_ = GetAngleToTarget(start_, pos_);
		float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
		gm_->shot_list.push_back(new Shot_knife(width<3.0f?effect_texture:&tex_melee2, User_, damage_, GetPower(), GetMaxPower(), burst_speed, team_, start_, angle_, GetDistance(), width, back_stab));
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
};

class Melee_Axe : public Melee_Weapon
{
public:
	Melee_Axe::Melee_Axe(const melee_weapon_infor& infor_, coord_def pos_, int time_):
	Melee_Weapon(infor_, pos_, time_)
	{
	}
	float Melee_Axe::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
	{
		if (gm_->isPlayerCanHear(GetPos()))
		{
			PlaySE(se_axe);
		}
		float angle_ = GetAngleToTarget(start_, pos_);
		float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
		gm_->shot_list.push_back(new Shot_axe(width<3.0f?effect_texture:&tex_melee2, User_, damage_, GetPower(), GetMaxPower(), burst_speed, team_, start_, angle_, GetDistance(), width, back_stab));
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
};


class Melee_Club : public Melee_Weapon
{
public:
	Melee_Club::Melee_Club(const melee_weapon_infor& infor_, coord_def pos_, int time_):
	Melee_Weapon(infor_, pos_, time_)
	{
	}
	float Melee_Club::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
	{
		if (gm_->isPlayerCanHear(GetPos()))
		{
			PlaySE(se_knife);
		}
		float angle_ = GetAngleToTarget(start_, pos_);
		float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
		gm_->shot_list.push_back(new Shot_club(width<3.0f?effect_texture:&tex_melee2, User_, damage_, GetPower(), GetMaxPower(), burst_speed, team_, start_, angle_, GetDistance(), width, back_stab));
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
};

class Melee_Spear : public Melee_Weapon
{
public:
	Melee_Spear::Melee_Spear(const melee_weapon_infor& infor_, coord_def pos_, int time_):
	Melee_Weapon(infor_, pos_, time_)
	{
	}
	float Melee_Spear::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
	{
		if (gm_->isPlayerCanHear(GetPos()))
		{
			PlaySE(se_knife);
		}
		float angle_ = GetAngleToTarget(start_, pos_);
		float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
		gm_->shot_list.push_back(new Shot_spear(width<3.0f?effect_texture:&tex_melee2, User_, damage_, GetPower(), GetMaxPower(), burst_speed, team_, start_, angle_, GetDistance(), width, back_stab));
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
};


class Melee_AssasinKnife : public Melee_Weapon
{
public:
	Melee_AssasinKnife::Melee_AssasinKnife(const melee_weapon_infor& infor_, coord_def pos_, int time_):
	Melee_Weapon(infor_, pos_, time_)
	{
	}
	float Melee_AssasinKnife::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
	{
		if (gm_->isPlayerCanHear(GetPos()))
		{
			PlaySE(se_assknife);
		}
		float angle_ = GetAngleToTarget(start_, pos_);
		float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
		gm_->shot_list.push_back(new Shot_assasinknife(width<3.0f?effect_texture:&tex_melee2, User_, damage_, GetPower(), GetMaxPower(), burst_speed, team_, start_, angle_, GetDistance(), width, back_stab));
		return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
	}
};

Melee_Weapon* New_Melee_Weapon(Melee_Kind kind_, coord_def pos_, int time_)
{
	Melee_Weapon* temp = NULL;
	switch(kind_)
	{
	case MK_NONE:
	case MK_KNIFE:
	default:
		temp = new Melee_Knife(melee__knife, pos_, time_);
	break;
	case MK_AXE:
		temp = new Melee_Axe(melee__axe, pos_, time_);
	break;
	case MK_CLUB:
		temp = new Melee_Club(melee__club, pos_, time_);
	break;
	case MK_SPEAR:
		temp = new Melee_Spear(melee__spear, pos_, time_);
	break;	
	case MK_HAMMER:
		temp = new Melee_Hammer(melee__hammer, pos_, time_);
	break;	
	case MK_ASSASIN_KNIFE:
		temp = new Melee_AssasinKnife(melee__assasin_knife, pos_, time_);
	break;
	}
	return temp;
}