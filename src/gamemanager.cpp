//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: gamemanager.cpp
//
// 내용: 게임클래스 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "networkmanager.h"
#include <math.h>
#include <d3dx9.h>

#include "texture_list.h"
#include "gamemanager.h"
#include "d3dx_class.h"
#include "player.h"
#include "map.h"
#include "keyinput.h"
#include "bitrect.h"
#include "image.h"
#include "profiler.h"
#include "shot_base.h"
#include "main_weapon_list.h"
#include "melee_weapon_list.h"
#include "Monster.h"
#include "item.h"
#include "rifle.h"
#include "fire.h"
#include "ai.h"
#include "monster_list.h"
#include "random.h"
#include "ability.h"
#include "char_make.h"
#include "sound.h"
#include "debug.h"



Game_Manager* Game_Manager::pInstance = NULL;
HWND Game_Manager::handle = 0;

int death_dump_ = 0;


Game_Manager::Game_Manager():
count(0),level(0), state(0), scale(1.0f), heal_stack(0), sniper_mode(false), focus(0,0), player(NULL), next_portal(NULL), char_maker(NULL), Network_host(NULL), Network_client(NULL), map(NULL), key(NULL), direct(NULL),
next_floor(false), full_text() 
{
	for(int i = 0; i<SS_MAX_FLOOR; i++)
		stage_kind[i] = SS_NORMAL;

	GameMenu();

}

Game_Manager::~Game_Manager()
{
	if(!item_list.empty())
	{
		for(list<Item*>::iterator it = item_list.begin(); it != item_list.end(); it++)
		{
			delete (*it);
		}
	}	
	if(!shot_list.empty())
	{
		for(list<Shot_base*>::iterator it = shot_list.begin(); it != shot_list.end(); it++)
		{
			delete (*it);
		}
	}
	if(!unit_list.empty())
	{
		for(list<Unit*>::iterator it = unit_list.begin(); it != unit_list.end(); it++)
		{
			delete (*it);
		}
	}	
	//if(player)
	//	delete player; 이제 유닛리스트에서 해제를 관리한다
	if(map)
		delete map;
	if(char_maker)
		delete char_maker;
	if(Network_host)
		NetworkManager::DestroyInstance(Network_host);
	if(Network_client)
		NetworkClient::DestroyInstance(Network_client);

	Ability::ReleaseAbility();
}



Game_Manager* Game_Manager::CreateInstance()
{
	if(pInstance == NULL)
		pInstance = new Game_Manager();
	init_state();
	Ai_Manager::SetGameManager(pInstance);
	Ability::InitAbility(pInstance);
	return pInstance;
}





void Game_Manager::DestroyInstance(Game_Manager* pInstance_)
{
	if(pInstance_ == pInstance)
		delete pInstance;
}
void Game_Manager::SetHandle(HWND handle_)
{
	handle = handle_;
}
coord_def Game_Manager::GetPlayerPos()
{
	return player->GetPos();
};
bool Game_Manager::GetStateView()
{
	return player->GetStateView();
}
bool Game_Manager::GetMonSightView()
{
	return !!(player->GetInvisible());
}
bool Game_Manager::isPlayerLive()
{
	return player && player->isLive();
};
void Game_Manager::SetDirectClass(Direct_Manager* direct_)
{
	direct = direct_;	
}

void Game_Manager::GameMenu()
{

	if(!item_list.empty())
	{
		for(list<Item*>::iterator it = item_list.begin(); it != item_list.end(); it++)
		{
			delete (*it);
		}
	}	
	item_list.clear();
	if(!shot_list.empty())
	{
		for(list<Shot_base*>::iterator it = shot_list.begin(); it != shot_list.end(); it++)
		{
			delete (*it);
		}
	}
	shot_list.clear();
	if(!unit_list.empty())
	{
		for(list<Unit*>::iterator it = unit_list.begin(); it != unit_list.end(); it++)
		{
			delete (*it);
		}
	}
	unit_list.clear();	
	if(char_maker)
		delete char_maker;
	char_maker = new Character_Maker();
	
	StopBGM(bgm_dungeon_3);
	StopBGM(bgm_dungeon_2);
	StopBGM(bgm_dungeon_1);
	StopBGM(bgm_dungeon_0);
	level = 0;
	state = 0;
}

void Game_Manager::TargetLost()
{
	for(list<Unit*>::iterator it = unit_list.begin();it != unit_list.end();it++)
	{
		if((*it)->isLive())
		{
			(*it)->TargetLost_unit();
		}
	}
	
	for(list<Shot_base*>::iterator it = shot_list.begin();it != shot_list.end(); it++)
	{
		(*it)->TargetLost();
	}

}
void Game_Manager::InvisibleLost(coord_def c)
{
	for(list<Unit*>::iterator it = unit_list.begin();it != unit_list.end();it++)
	{
		if((*it)->isLive())
		{
			(*it)->InvisibleLost(c);
		}
	}
}
void Game_Manager::GiveExp(int team_, int value_)
{
	for(list<Unit*>::iterator it = unit_list.begin();it != unit_list.end();it++)
	{
		if((*it)->isPlayer() && (*it)->isLive() && (*it)->GetTeam() == team_)
		{			
			(*it)->GiveExp(this, value_);
		}
	}
}
void Game_Manager::KillMonster(int team_, Monster* monster_, Damage_Type type_, float damage_, bool back_stab_)
{
	for(list<Unit*>::iterator it = unit_list.begin();it != unit_list.end();it++)
	{
		if((*it)->isPlayer() && (*it)->isLive() && (*it)->GetTeam() == team_)
		{		
			(*it)->KillMonster(this, team_, monster_, type_, damage_, back_stab_);
		}
	}
}
void Game_Manager::Noise(int team_, coord_def pos_, float size_)
{
	for(list<Unit*>::iterator it = unit_list.begin();it != unit_list.end();it++)
	{
		if((*it)->isLive() && distan_coord(pos_, (*it)->GetPos()) <= size_)
		{			
			(*it)->SetNoise(this, team_, pos_);
		}
	}
}
coord_def Game_Manager::GetRandomPos()
{
	while(1)
	{
		int x_ = rand_int(0,map->GetWidth()-1);
		int y_ = rand_int(0,map->GetHeight()-1);
		int i=-1;
		int j=-1;
		for(i=-1;i<=1;i++){
			for(j=-1;j<=1;j++){
				if(!i || !j){
					if(map->CollutionPos(x_+i*3,y_+j*3))
					{
						i=3;
						j=3;
					}
				}
			}
		}
		if(i == 2 && j == 2)
			return coord_def((float)x_, (float)y_);
	}
}
int Game_Manager::GetMonsterNum()
{
	//return unit_list.size();
	int i = 0;
	for(list<Unit*>::iterator it = unit_list.begin() ; it != unit_list.end() ; it++)
	{
		if(!(*it)->isNamed() && !(*it)->isPlayer() && !(*it)->isNonLife())
			i++;
	}
	return i;
}
bool Game_Manager::SetSniperMode(bool ok_, coord_def pos_, float scale_, bool mouse_)
{
	sniper_mode = ok_;
	if(ok_)
	{
		scale = scale_;
		if(player->GetSniperSight()<distan_coord(player->GetPos(), pos_)) //저격의 사거리p
		{
			float angle_ = GetAngleToTarget(player->GetPos(), pos_);
			pos_ = coord_def(player->GetPos().x+player->GetSniperSight()*cos(angle_),player->GetPos().y+player->GetSniperSight()*sin(angle_));
		}
		focus = pos_;
		if(mouse_){
			RECT rect_;
			GetWindowRect(handle,&rect_);
			SetCursorPos(rect_.left+3+ direct->GetWidth()/2,rect_.top+25+direct->GetHeight()/2);
		}
	}
	else
	{
		coord_def center_((float)direct->GetWidth()/2,(float)direct->GetHeight()/2);
		coord_def temp_ = (key->GetMousePos()+focus)-player->GetPos();
		float x1_ = temp_.x;
		float y1_ = temp_.y;
		if(mouse_){
			RECT rect_;
			
			GetWindowRect(handle,&rect_);
			float w = direct->GetWidth()/2.0f;
			float h = direct->GetHeight()/2.0f;
			SetCursorPos((int)((rect_.left+3+temp_.x*direct->GetWR()+w)),(int)((rect_.top+25+temp_.y*direct->GetHR()+h)));
		}
		scale = 1.0f;
	}
	return true;
}
bool Game_Manager::Heal_percent(bool box_)
{
	if(heal_stack<30)
		heal_stack++;
	else
		heal_stack = 30;

	int rand_ = rand_int(1,100);
	int percent_ = max(0,heal_stack-25)*10+(box_?10:1);

	if(rand_<=percent_){
		if(box_)
			heal_stack /= 2;
		else
			heal_stack = 0;

		return true;
	}
	else{
		return false;
	}

}
void Game_Manager::Loop() //staic함수
{
	if(pInstance)
	{
		switch(pInstance->state)
		{
		case 0:
			pInstance->SelectLoop();
			break;
		case 1:
			pInstance->GameLoop();
			break;
		case 2:
			pInstance->NetworkLoop();
			break;
		case 3:
			pInstance->TextLoop();
			break;
		}
	}
	return;
}
void Game_Manager::SelectLoop()
{
	{
		if(key->GeyKeyState(DIK_A, KEY_DOWN))
			char_maker->Select(0);
		if(key->GeyKeyState(DIK_B, KEY_DOWN))
			char_maker->Select(1);
		if(key->GeyKeyState(DIK_C, KEY_DOWN))
			char_maker->Select(2);
		if(key->GeyKeyState(DIK_D, KEY_DOWN))
			char_maker->Select(3);
		if(key->GeyKeyState(DIK_E, KEY_DOWN))
			char_maker->Select(4);
		if(key->GeyKeyState(DIK_F, KEY_DOWN))
			char_maker->Select(5);
		if(key->GeyKeyState(DIK_G, KEY_DOWN))
			char_maker->Select(6);
		if(key->GeyKeyState(DIK_H, KEY_DOWN))
			char_maker->Select(7);
		if(key->GeyKeyState(DIK_I, KEY_DOWN))
			char_maker->Select(8);
		if(key->GeyKeyState(DIK_J, KEY_DOWN))
			char_maker->Select(9);
		if(key->GeyKeyState(DIK_K, KEY_DOWN))
			char_maker->Select(10);
		if(key->GeyKeyState(DIK_L, KEY_DOWN))
			char_maker->Select(11);

		if(key->GeyKeyState(DIK_1, KEY_DOWN))
		{
			soundmanager.SetBgmOnOff();
		}
		if(key->GeyKeyState(DIK_2, KEY_DOWN))
		{
			soundmanager.SetSeOnOff();
		}
	}
	if(key->GeyKeyState(DIK_RETURN, KEY_DOWN))
	{
		player = char_maker->GetPlayer(this);
		if(player)
		{
			delete char_maker;
			char_maker = NULL;
			if(!map)
				map = new Map(&tex_map);

			unit_list.push_back(player);
			state = 1;

			InitNamed();
			StageMake();
			StageInit(0,MPT_NOMAL,rand_int(1,3),12);
		}
	}
	/*if(key->GeyKeyState(DIK_1, KEY_DOWN))
	{
		if(!Network_host)
			Network_host = NetworkManager::CreateInstance();
		Network_host->init();
		state = 2;
	}
	if(key->GeyKeyState(DIK_2, KEY_DOWN))
	{
		if(!Network_client)
			Network_client = NetworkClient::CreateInstance();
		Network_client->init();
		state = 2;
	}*/
}
void Game_Manager::GameLoop()
{
#ifdef __PROFILE__
	ProfileBegin("Game_Manager::GameLoop()");
#endif
	

	
	if(player->GetAbilitySelect())
	{ //능력 셀렉창인경우
		for(int i = 0; i < player->GetSelectAbilityNum(); i++)
		{
			if(key->GeyKeyState(DIK_1+i, KEY_DOWN))
				player->SelectAbilityBefore(1+i);
		}
		player->SelectAction(this);
	}
	else
	{
		static int i = 0;

		if(!sniper_mode)
			focus = player->GetPos();
		else
		{
			//coord_def center_((float)direct->GetWidth()/2,(float)direct->GetHeight()/2);
			POINT new_, old_;
			GetCursorPos(&new_);
			RECT rect_;
			GetWindowRect(handle,&rect_);
			SetCursorPos(rect_.left+3+ direct->GetWidth()/2,rect_.top+25+direct->GetHeight()/2);
			GetCursorPos(&old_);
			coord_def dif_ = coord_def((float)(new_.x-old_.x),(float)(new_.y-old_.y))/scale;
			focus = focus+dif_;
			if(player->GetSniperSight()<distan_coord(player->GetPos(), focus)) //저격의 사거리p
			{
				float angle_ = GetAngleToTarget(player->GetPos(), focus);
				focus = coord_def(player->GetPos().x+player->GetSniperSight()*cos(angle_),player->GetPos().y+player->GetSniperSight()*sin(angle_));
			}
		}

		player->SetAngle(GetAngleToTarget(player->GetPos(), key->GetMousePos()+focus));

		player->SetFocusPos(key->GetMousePos()+focus);


		//아이템 처리
		for(list<Item*>::iterator it = item_list.begin();it != item_list.end(); )
		{
			if((*it)->Action(this))
			{
				delete (*it);
				list<Item*>::iterator temp = it++;
				item_list.erase(temp);
			}
			else
				it++;
		}

		//총알 처리
		for(list<Shot_base*>::iterator it = shot_list.begin();it != shot_list.end(); )
		{
			if((*it)->Action(this))
			{
				delete (*it);
				list<Shot_base*>::iterator temp = it++;
				shot_list.erase(temp);
			}
			else
				it++;
		} 
		if(death_dump_)
		{
			death_dump_--;
		}
		else
		{
		}

		//유닛 처리
		for(list<Unit*>::iterator it = unit_list.begin();it != unit_list.end(); )
		{
			if((*it)->Action(this))
			{			
				death_dump_= 3;
				TargetLost();
				delete (*it);
				list<Unit*>::iterator temp = it++;
				unit_list.erase(temp);
			}
			else
				it++;
		}
		//if(key->GeyKeyState(DIK_Q, KEY_DOWN))
		//	player->StartAbility();
		if(key->GeyKeyState(DIK_M, KEY_DOWN))
			map->SwapSize();
		if(key->GeyKeyState(DIK_F, KEY_DOWN))
			player->StartQuickStart();

		if(isPlayerLive())
		{//플레이어가 살아있을때...
			float angle_=0;
			int wh_=11;
			if(!player->GetSniper()){
				if(key->GeyKeyState(DIK_W, KEY_HOLD))
					wh_--;
				if(key->GeyKeyState(DIK_S, KEY_HOLD))
					wh_++;
				if(key->GeyKeyState(DIK_A, KEY_HOLD))
					wh_-=10;
				if(key->GeyKeyState(DIK_D, KEY_HOLD))
					wh_+=10;
			}
			if(key->GeyKeyState(DIK_R, KEY_DOWN))
				player->Reload();
			if(!player->GetSniper() && key->GeyKeyState(DIK_LSHIFT, KEY_DOWN) || key->GeyKeyState(DIK_RSHIFT, KEY_DOWN))
				player->PickUp(this);

			if(player->GetQuickSelect())
			{
				if(key->GeyKeyState(DIK_Z, KEY_DOWN))
					player->SetQuickmenu(5);
				if(key->GeyKeyState(DIK_X, KEY_DOWN))
					player->SetQuickmenu(6);
			}
			else{
				if(key->GeyKeyState(DIK_Z, KEY_DOWN))
					player->UseAbility(this, 0);
				if(key->GeyKeyState(DIK_X, KEY_DOWN))
					player->UseAbility(this, 1);
			}
			/*if(key->GeyKeyState(DIK_M, KEY_DOWN))
			map->map_hack();*/
			//if(key->GeyKeyState(DIK_C, KEY_DOWN))
			//	player->SetHp(100);


			if(player->GetQuickSelect())
			{
				if(key->GeyKeyState(DIK_1, KEY_DOWN))
					player->SetQuickmenu(1);
				else if(key->GeyKeyState(DIK_2, KEY_DOWN))
					player->SetQuickmenu(2);
				else if(key->GeyKeyState(DIK_3, KEY_DOWN))
					player->SetQuickmenu(3);
				else if(key->GeyKeyState(DIK_4, KEY_DOWN))
					player->SetQuickmenu(4);
			}
			else if(!player->GetSniper())
			{ //무기교체하기

				if(key->GeyKeyState(DIK_1, KEY_DOWN))
					player->Swap(1);
				else if(key->GeyKeyState(DIK_2, KEY_DOWN))
					player->Swap(2);
				else if(key->GeyKeyState(DIK_3, KEY_DOWN))
					player->Swap(3);
				else if(key->GeyKeyState(DIK_4, KEY_DOWN))
					player->Swap(4);
			}

			bool left_click = false;
			if(player->is_Click_Hold())
			{
				if(key->GetMouseState(MOUSE_LEFT_HOLD))
				{
					player->Shot(this, key->GetMousePos()+focus, 0.0f);
					left_click = true;
				}
			}
			else
			{
				if(key->GetMouseState(MOUSE_LEFT_DOWN))
				{
					player->Shot(this, key->GetMousePos()+focus, 0.0f);
					left_click = true;
				}
			}
			if(!left_click && key->GetMouseState(MOUSE_RIGHT_DOWN))
			{
				player->Quick(this, key->GetMousePos()+focus, 0.0f);
			}

#ifdef __PROFILE__
			if(key->GeyKeyState(DIK_P, KEY_DOWN))
			{
				ProfileSaveBuffer();
			}
#endif

			if(wh_ != 11 && !player->GetFly())
			{
				switch(wh_)
				{
				case 21:angle_ =0.0f;break;
				case 22:angle_ =D3DX_PI/4;break;
				case 12:angle_ =D3DX_PI/2;break;
				case 02:angle_ =D3DX_PI*3/4;break;
				case 01:angle_ =D3DX_PI;break;
				case 00:angle_ =D3DX_PI*5/4;break;
				case 10:angle_ =D3DX_PI*3/2;break;
				case 20:angle_ =D3DX_PI*7/4;break;
				}

				player->UnitMove(this, player->GetSpeed(angle_), angle_);
				if(count%10 == 0)
					map->UpdateSight(player);

			}
		}
		else
		{
			if(key->GeyKeyState(DIK_RETURN, KEY_HOLD))
			{
				GameMenu();			
			}
		}
		if(next_floor && isPlayerLive())
		{
			NextStage();
			next_floor = false;
		}
		count++;
#ifdef __PROFILE__
		ProfileEnd("Game_Manager::GameLoop()");
#endif
	}
}

void Game_Manager::NetworkLoop()
{
#ifdef __PROFILE__
	ProfileBegin("Game_Manager::NetworkLoop()");
#endif
	
	if(Network_client)
	{
		if(key->GeyKeyState(DIK_Q, KEY_DOWN))
			Network_client->sendtest("Q");
		if(key->GeyKeyState(DIK_W, KEY_DOWN))
			Network_client->sendtest("W");
		if(key->GeyKeyState(DIK_E, KEY_DOWN))
			Network_client->sendtest("E");
		if(key->GeyKeyState(DIK_R, KEY_DOWN))
			Network_client->sendtest("R");
	}
	
#ifdef __PROFILE__
	ProfileEnd("Game_Manager::NetworkLoop()");
#endif
}
void Game_Manager::TextLoop()
{
#ifdef __PROFILE__
	ProfileBegin("Game_Manager::NetworkLoop()");
#endif	
	if(key->GeyKeyState(DIK_RETURN, KEY_DOWN))
	{
		GameMenu();
	}
#ifdef __PROFILE__
	ProfileEnd("Game_Manager::NetworkLoop()");
#endif
}

bool Game_Manager::Draw() //staic함수
{
	if(pInstance)
	{
		switch(pInstance->state)
		{
		case 0:
			return pInstance->SelectDraw();
		case 1:
			return pInstance->GameDraw();
		case 2:
			return pInstance->NetworkDraw();
		case 3:
			return pInstance->TextDraw();
		}
	}
	return false;
	
}
bool Game_Manager::SelectDraw()
{
	return char_maker->SelectDraw(direct);
}



bool Game_Manager::GameDraw()
{
#ifdef __PROFILE__
	ProfileBegin("Game_Manager::GameDraw()");
#endif
	
	tex_tile.Draw(-(float)((int)focus.x%32)*scale, -(float)((int)focus.y%32)*scale, scale, 0.0f);
	map->Draw(focus, scale);

	for(list<Item*>::iterator it = item_list.begin();it != item_list.end(); it++)
	{
		(*it)->Draw(focus, scale);
	}
	for(list<Unit*>::iterator it = unit_list.begin();it != unit_list.end(); it++)
	{
		(*it)->Draw(this, focus, scale);
		(*it)->NameDraw(this, focus, scale);
	}
	for(int i=0; i<STP_FOG_END; i++)
	{
		for(list<Shot_base*>::iterator it = shot_list.begin();it != shot_list.end(); it++)
		{
			if((*it)->GetPriority() == (SHOT_PRIORITY)i)
				(*it)->Draw(focus, scale);
		}
	}

	if(sniper_mode)
		player->SniperDraw(coord_def(),coord_def(600.0f,400.0f));
	else
		player->FogDraw(coord_def(),coord_def((float)direct->GetWidth(),(float)direct->GetHeight()));

	for(int i=STP_FOG_END; i<STP_MAX; i++)
	{
		for(list<Shot_base*>::iterator it = shot_list.begin();it != shot_list.end(); it++)
		{
			if((*it)->GetPriority() == (SHOT_PRIORITY)i)
				(*it)->Draw(focus, scale);
		}
	}
	

	map->DrawMinimap(this ,coord_def(20.0f+600.0f/2.0f,160.0f-400.0f/2.0f));

	player->PickUpDraw(this, coord_def(12.0f,(400.0f-64)));
	player->PickUpNameDraw(this, coord_def(12.0f*direct->GetWR(),(400.0f-64)*direct->GetHR()));//글자
	
	if(key->GeyKeyState(DIK_LCONTROL, KEY_HOLD))//글자
		player->DetailInforDraw(this, coord_def((160.0f)*direct->GetWR(),(400.0f-112)*direct->GetHR()), coord_def((600.0f-232)*direct->GetWR(),(400.0f-112)*direct->GetHR()));
	


	player->HpDraw(coord_def(20.0f-600.0f/2.0f,20.0f-400.0f/2.0f));
	player->StaminaDraw(coord_def(20.0f-600.0f/2.0f,50.0f-400.0f/2.0f));
	player->ExpDraw(coord_def(20.0f-600.0f/2.0f,70.0f-400.0f/2.0f));

	player->AbilityUpDraw(this,coord_def((-5.0f+600.0f)*direct->GetWR(),(5.0f)*direct->GetHR()));//글자
	
	//player->TestDraw(this,coord_def(direct->GetWidth()/2.0f,direct->GetHeight()/2.0f));

	
	player->StateDraw(this, coord_def((20.0f-600.0f/2.0f)*direct->GetWR(),-110.0f*direct->GetHR()));//글자
	
	player->StateGaugeDraw(this, coord_def((20.0f-600.0f/2.0f),-110.0f));//글자


	player->UseAbilityDraw(this, coord_def((20.0f-600.0f/2.0f)*direct->GetWR(),50.0f*direct->GetHR()));//글자
	
	if(key->GeyKeyState(DIK_TAB, KEY_HOLD))
		player->AbilityDraw(this, coord_def(-150.0f*direct->GetWR(),-50.0f*direct->GetHR()));//글자
	else
		player->AbilitySelectDraw(this,coord_def(-200.0f*direct->GetWR(),-50.0f*direct->GetHR()));//글자
	
	player->QuickMenuDraw(this, coord_def(-150.0f*direct->GetWR(),-50.0f*direct->GetHR()));//글자
	
	player->DelayDraw(coord_def(0,-10), scale);

	player->BulletDraw( coord_def(600.0f/2-100,400.0f/2-96));
	if(player->GetCurrentWeapon()){
		player->GetCurrentWeapon()->InterfaceDraw(direct, coord_def(600.0f-128,400.0f-64));
		player->GetCurrentWeapon()->InterfaceNameDraw(direct, coord_def((600.0f-128)*direct->GetWR(),(400.0f-64)*direct->GetHR()));		
	}
	else{
		if(player->GetEmptyWeapon())
			player->GetEmptyWeapon()->InterfaceDraw(direct, coord_def(600.0f-128,400.0f-64));
	}
	if(!isPlayerLive())
	{
		char temp[128];
		RECT rc={0, 0, direct->GetWidth(), direct->GetHeight()};
		sprintf_s(temp,128,"당신은 %d층에서 죽었습니다...\n재도전하려면 엔터키",level+1);
		direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_CENTER | DT_NOCLIP, 0xffff0000);
	}
	else
	{
		char temp[128];
		RECT rc={0, 0, direct->GetWidth(), direct->GetHeight()};
		sprintf_s(temp,128,"현재 %d층",level+1);
		direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_CENTER | DT_NOCLIP, 0xffff0000);

	}
	

	{
		float scale_ = distan_coord(coord_def(0,0), key->GetMousePos())*sin(player->GetFocusSum())/16.0f;
		if(!sniper_mode)
		{
			tex_target.Draw(key->GetMouseX(), key->GetMouseY(), 1.0f, 0.0f);
			tex_focus.Draw(key->GetMouseX(), key->GetMouseY(), scale_, scale_, 0.0f, D3DCOLOR_ARGB(255,0,128,255));
		}
		else
		{
			if(map->CollutionPosToPos(player->GetPos(), key->GetMousePos()+focus))
			{				
				char temp[16];
				//RECT rc={0, 0, direct->GetWidth(), direct->GetHeight()};
				RECT rc={0, direct->GetHeight()/2-30, direct->GetWidth(), direct->GetHeight()};
				sprintf_s(temp,16,"조준불가");
				direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_CENTER | DT_NOCLIP, 0xffff0000);

			}
			//tex_focus.Draw(0, 0, scale_, 0.0f);
			//tex_target.Draw(0,0, 1.0f, 0.0f);
		}
	}
	
#ifdef __PROFILE__
	ProfileEnd("Game_Manager::GameDraw()");
#endif
	return true;
}



bool Game_Manager::NetworkDraw()
{
	
#ifdef __PROFILE__
	ProfileBegin("Game_Manager::NetworkDraw()");
#endif
	
	if(Network_host)
	{
		char temp[1024];
		RECT rc={0, 0, direct->GetWidth(), direct->GetHeight()};
		sprintf_s(temp,1024,"%s",Network_host->GetString());
		direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_CENTER | DT_NOCLIP, 0xffff0000);
	}

#ifdef __PROFILE__
	ProfileEnd("Game_Manager::NetworkDraw()");
#endif
	return false;
}

bool Game_Manager::TextDraw()
{
#ifdef __PROFILE__
	ProfileBegin("Game_Manager::NetworkDraw()");
#endif
	char temp[1024];
	RECT rc={0, 0, direct->GetWidth(), direct->GetHeight()};
	sprintf_s(temp,1024,"%s",full_text.c_str());
	direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_CENTER | DT_NOCLIP, 0xffffffff);


#ifdef __PROFILE__
	ProfileEnd("Game_Manager::NetworkDraw()");
#endif
	return true;
}