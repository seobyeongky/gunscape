//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: portal.cpp
//
// ����: ��Ż!!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "portal.h"
#include "gamemanager.h"
#include "d3dx_class.h"
#include "image.h"
#include "texture_list.h"
#include "main_weapon.h"
#include "melee_weapon.h"
#include "sub_weapon.h"
#include "player.h"
#include "ability.h"
#include "config.h"
#include "sound.h"

extern smap<opznet::ID, cl_t> clients;
extern opznet::ID my_id;

Portal::Portal(Texture* texture_, coord_def pos_, bool last_):
Item(texture_, "��Ż", "���� ������ �Ѿ", pos_, 0),
last(last_), time_for(), next_lv(false)
{

}

bool Portal::InforDraw(Direct_Manager* direct_, coord_def offset_)
{
	offset_.x+=20;
	offset_.y+=50;
	tex_system_gauge_border.Draw(offset_.x+30.0f-600.0f/2,  offset_.y-400.0f/2, 1.0f, 0.0f);
	float pecen_ = time_for[my_id]/300.0f;
	tex_system_gauge.Draw(offset_.x-17.0f + 47*pecen_-600.0f/2,  offset_.y-400.0f/2, pecen_, 1.0f, 0.0f);
	return true;
}
bool Portal::InforNameDraw(Direct_Manager* direct_, coord_def offset_)
{
	RECT rc={(LONG)offset_.x, (LONG)(offset_.y+16*direct_->GetHR()), (LONG)(offset_.x+128*direct_->GetWR()), 1000};
	direct_->GetFont()->DrawTextA(NULL,last?"Ż�� �ϴ� ��...":"���� ������ �ǳʰ��� ��...", -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	return true;
}

bool Portal::Action(Game_Manager* gm_)
{
	for (auto & cl : clients)
	{
		Player * p = cl.element().player;
		int & time_ = time_for[cl.key()];
		if (p->collution(GetPos(), 10) && !p->GetNet())
		{
			time_ += p->GetPortalTime();
			if (p->GetPortalTime() > 1)
			{
				p->AttackApply(p->GetPortalTime()==2?1.5f:2.f, 10, ABK_PORTAL);
			}
			if (time_ >= 300)
			{
				Effect(gm_, p);
				time_ = -9999999;
			}
		}
		else
		{
			time_ = 0;
		}
	}
	
	return false;
}
bool Portal::Effect(Game_Manager* gm_, Player* unit_)
{
	PlaySE(se_portal, false);

	if(!last)
	{
		// �ϴ� ����Ʈ���� ����.
		// ���߿� �ְ�...
		// ��¥�� ���� ������ ���ÿ� ��Ȱ�ϴϱ�
		if (config::gamemode == MULTI_GAME)
			gm_->unit_list.remove(unit_);

		Player * my_player = clients[my_id].player;
		if (unit_ == my_player && !next_lv)
		{
			next_lv = true;
			gm_->NextLevel();
		}
	}
	else
	{
		if (unit_ == gm_->player)
		{
			gm_->SetText("Ż�� ����!!!\n\n����� �� �������� ���� ������ Ż�� �߽��ϴ�.\n\n\n\n");
			char temp[256];
			sprintf_s(temp,256,"����� ���� ����: %s\n\n",gm_->player->GetName());
			gm_->AddText(temp);
			if(gm_->player->main_weapon)
			{
				sprintf_s(temp,256,"�ֹ���:%s\n",gm_->player->main_weapon->GetName()?gm_->player->main_weapon->GetName():"����");
				gm_->AddText(temp);	
			}
			if(gm_->player->sub_weapon[0])
			{
				sprintf_s(temp,256,"��������:%s\n",gm_->player->sub_weapon[0]->GetName()?gm_->player->sub_weapon[0]->GetName():"����");
				gm_->AddText(temp);	
			}
			if(gm_->player->sub_weapon[1])
			{
				sprintf_s(temp,256,"��������:%s\n",gm_->player->sub_weapon[1]->GetName()?gm_->player->sub_weapon[1]->GetName():"����");
				gm_->AddText(temp);	
			}
			if(gm_->player->melee_weapon)
			{
				sprintf_s(temp,256,"��������:%s\n",gm_->player->melee_weapon->GetName()?gm_->player->melee_weapon->GetName():"����");
				gm_->AddText(temp);	
			}


			sprintf_s(temp,256,"\n<��� �ɷµ�>\n");
			gm_->AddText(temp);
			for(vector<Ability*>::iterator it = gm_->player->abil_list.begin(); it != gm_->player->abil_list.end(); it++)
			{
				sprintf_s(temp,256,"%s(%d����):%s\n",(*it)->GetName(),(*it)->GetLevel(),(*it)->GetInfor());
				gm_->AddText(temp);	
			}
			gm_->SetState(3);
		}
	}
	return true;
}