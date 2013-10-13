//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_last_message.cpp
//
// 내용: 최종 목적
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "effect_last_message.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "d3dx_class.h"
#include "unit.h"
#include "image.h"
#include "player.h"
#include "map.h"
#include "effect_piece.h"
#include "monster_list.h"
#include "shot_base.h"
#include "random.h"
#include "portal.h"


Effect_last_message::Effect_last_message(Game_Manager* gm_):
Shot_base(NULL, NULL, 0, coord_def(), coord_def(), STP_TEXT),
gm(gm_), left_num(0), count(0), clear(false)
{


}
Effect_last_message::~Effect_last_message()
{


}


bool Effect_last_message::Action(Game_Manager* gm_)
{
	if(gm_)
	{
		count++;
		left_num = 0;
		for(list<Item*>::iterator it = gm_->item_list.begin();it != gm_->item_list.end();it++)
		{
			if(!strcmp((*it)->GetName(),"스위치"))
			{
				if((*it)->is_On())
				{
					left_num++;
				}
			}
		}
		if(!clear && left_num >= gm->player->GetSwitch())
		{
			while(1)
			{
				coord_def c_ = gm_->GetRandomPos();
				if(!gm_->player->collution(c_,300))
				{		
					Item* portal_ = new Portal(&tex_item_portal1, c_,true);
					gm_->item_list.push_back(portal_);
					gm_->next_portal = portal_;
					gm_->map->UpdateSight(c_, 50.0f);
					break;
				}
			}
			clear = true;
		}


		//if(count % 600 == 0)
		//{
		//	for(int i = 0 ; i < 10; i++)
		//	{
		//		if(gm_->GetMonsterNum()<=10)
		//		{
		//			while(1)
		//			{
		//				coord_def c_ = gm_->GetRandomPos();
		//				if(!gm_->player->collution(c_,gm_->player->GetView()*2.0f) && gm_->player->collution(c_,gm_->player->GetView()*2.0f+300))
		//				{
		//					gm_->unit_list.push_back(New_Monster(GetStageMonster(15,MPT_LAST), c_, -1, 0));
		//					break;
		//				}
		//			}
		//		}
		//		else
		//		{
		//			for(list<Unit*>::iterator it = gm_->unit_list.begin() ; it != gm_->unit_list.end() ; it++)
		//			{
		//				if(!gm_->player->collution((*it)->GetPos(),gm_->player->GetView()*2.0f))
		//				{
		//					if(!(*it)->isNamed() && !(*it)->isPlayer() && !(*it)->isNonLife())
		//					{
		//						(*it)->SetHp(0);
		//						(*it)->SetItemDrop(false);
		//						break;
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
	}
	return false;
}

bool Effect_last_message::Draw(coord_def offset_, float size_)
{
	char text_[256];
	if(!clear)
		sprintf_s(text_,256,"탈출하기 위해 작동한 스위치 %d / %d",left_num,gm->player->GetSwitch());
	else
		sprintf_s(text_,256,"모든 스위치를 작동시켰습니다. 탈출하세요!");


	LONG x_ = (LONG)(gm->direct->GetWidth()-5*gm->direct->GetWR());
	LONG y_ = (LONG)(gm->direct->GetHeight()/2-40*gm->direct->GetHR());
	RECT rc = {x_,y_,x_,y_};
	gm->direct->GetFont()->DrawTextA(NULL, text_, -1, &rc, DT_RIGHT | DT_NOCLIP, D3DCOLOR_ARGB(255,255,0,0));
	return false;
}
