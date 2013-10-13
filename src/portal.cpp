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

Portal::Portal(Texture* texture_, coord_def pos_, bool last_):
Item(texture_, "��Ż", "���� ������ �Ѿ", pos_, 0),
last(last_)
{

}

bool Portal::InforDraw(Direct_Manager* direct_, coord_def offset_)
{
	offset_.x+=20;
	offset_.y+=50;
	tex_system_gauge_border.Draw(offset_.x+30.0f-600.0f/2,  offset_.y-400.0f/2, 1.0f, 0.0f);
	float pecen_ = time/300.0f;
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
	if(gm_->isPlayerLive())
	{
		coord_def temp = gm_->GetPlayerPos();
		if(gm_->player->collution(GetPos(), 10) && !gm_->player->GetNet())
		{
			time+=gm_->player->GetPortalTime();
			if(gm_->player->GetPortalTime()>1)
			{
				gm_->player->AttackApply(gm_->player->GetPortalTime()==2?1.5f:2.0f,10,ABK_PORTAL);
			}
			if(time >= 300)
				Effect(gm_, gm_->player);
		}
		else
		{
			time = 0;
		}
	}
	return false;
}
bool Portal::Effect(Game_Manager* gm_, Player* unit_)
{
	if(!last)
	{
		gm_->NextLevel();
	}
	else
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
	return true;
}