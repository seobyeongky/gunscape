//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: char_make.cpp
//
// 내용: 캐릭생성
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "char_make.h"
#include "job.h"
#include "texture_list.h"
#include "player.h"
#include "d3dx_class.h"
#include "sound.h"
#include <stdio.h>


#include "job_deserter.h"
#include "job_hunter.h"
#include "job_pyro.h"
#include "job_stalker.h"
#include "job_artillery.h"
#include "job_assassin.h"
#include "job_berserker.h"
#include "job_sniper.h"
#include "job_politician.h"
#include "job_archer.h"
#include "job_teemo.h"
#include "job_mercenary.h"



Character_Maker::Character_Maker():
player(NULL), num(-1)
{
	player = new Player(&tex_player, 0, 0);
	job_list.push_back(new Job_deserter());
	job_list.push_back(new Job_hunter());
	job_list.push_back(new Job_pyro());
	job_list.push_back(new Job_stalker());
	job_list.push_back(new Job_artillery());
	job_list.push_back(new Job_assassin());
	job_list.push_back(new Job_berserker());
	job_list.push_back(new Job_sniper());
	job_list.push_back(new Job_politician());
	job_list.push_back(new Job_archer());
	job_list.push_back(new Job_teemo());
	job_list.push_back(new Job_Mercenary());
}

Character_Maker::~Character_Maker()
{
	if(player)
		delete player;

	if(!job_list.empty())
	{
		for(vector<Job_base*>::iterator it = job_list.begin(); it != job_list.end(); it++)
		{
			delete (*it);
		}
	}
}

void Character_Maker::SetPosition(coord_def pos_)
{
	player->Move(pos_.x, pos_.y);
}
	
bool Character_Maker::SelectDraw(Direct_Manager* direct_)
{	
	int i = 0;
	char temp[256];
	float w_ =direct_->GetWR();
	float h_ =direct_->GetHR();

	RECT rc={(long)(30*w_), (long)(30*h_), (long)(direct_->GetWidth()), (long)(1000*h_)};
	for(vector<Job_base*>::iterator it = job_list.begin(); it != job_list.end(); it++)
	{
		if(i!=num)
			sprintf_s(temp,256,"%c-%s",i+'a',(*it)->GetName());
		else
			sprintf_s(temp,256,"▶%s",(*it)->GetName());

		direct_->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);
		rc.top+=(long)(16*h_);
		i++;
		if(i % 6 == 0)
		{
			rc.top = (long)(30*h_);
			rc.left += (long)(128*w_);
		}
	}
	if(num >= 0)
	{
		rc.top = (long)(150*h_);
		rc.left = (long)(30*w_);
		direct_->GetFont()->DrawTextA(NULL, "▶시작아이템◀", -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);
		rc.top+=(long)(16*h_);
		direct_->GetFont()->DrawTextA(NULL, job_list[num]->GetItemInfor(), -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);

		rc.top = (long)(150*h_);
		rc.left = (long)(164*w_);
		direct_->GetFont()->DrawTextA(NULL, "▶시작능력◀", -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);
		rc.top+=(long)(16*h_);
		direct_->GetFont()->DrawTextA(NULL, job_list[num]->GetAblityInfor(), -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);

		rc.top = (long)(230*h_);
		rc.left = (long)(30*w_);
		direct_->GetFont()->DrawTextA(NULL, job_list[num]->GetInfor(), -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);
		rc.top+=(long)(32*h_);
		direct_->GetFont()->DrawTextA(NULL, "※팁", -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);
		rc.top+=(long)(16*h_);
		direct_->GetFont()->DrawTextA(NULL, job_list[num]->GetTip(), -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);
		rc.top+=(long)(64*h_);
		direct_->GetFont()->DrawTextA(NULL, "엔터를 누를시 게임이 시작됩니다.", -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);
	}
	rc.top=(long)(346*h_);
	rc.left = (long)(300*w_);
	if(soundmanager.bgm_on)
		direct_->GetFont()->DrawTextA(NULL, "(숫자1로 배경음키고끄기) BGM: ON", -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);
	else
		direct_->GetFont()->DrawTextA(NULL, "(숫자1로 배경음키고끄기) BGM: OFF", -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);
	rc.top+=(long)(16*h_);
	if(soundmanager.se_on)
		direct_->GetFont()->DrawTextA(NULL, "(숫자2로 효과음키고끄기) SE: ON", -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);
	else
		direct_->GetFont()->DrawTextA(NULL, "(숫자2로 효과음키고끄기) SE: OFF", -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);



	return false;
}
unsigned int Character_Maker::GetCharNum()
{	
	return job_list.size();
}

bool Character_Maker::Select(unsigned int i)
{
	if(i < job_list.size())
	{
		num = i;
		return true;
	}
	return false;
}
Player* Character_Maker::GetPlayer(Game_Manager* gm_)
{
	if(num != -1)
	{
		job_list[num]->SetPlayer(gm_, player);
		player->Heal(player->GetMaxHp());
		player->Reload();
		PlaySE(se_pistol_reload);
		player->SetDelay(0.0f);
		Player* temp = player;
		player = NULL;
		return temp;
	}
	return NULL;
}