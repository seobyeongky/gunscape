//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: stage.cpp
//
// 내용: 스테이지 제작
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include <math.h>
#include <d3dx9.h>

#include "gamemanager.h"

#include "texture_list.h"
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
#include "portal.h"
#include "button.h"
#include "box.h"
#include "burrow.h"
#include "sound.h"
#include "effect_last_message.h"

#include "kevlar.h"

#include "effect_fog.h"




struct mon_struct
{
	Monster_Index id; //몬스터
	int percent; //확률
	mon_struct(Monster_Index id_, int percent_):id(id_),percent(percent_){}
};

Monster_Index GetStageMonster(int level, MAP_TYPE type_)
{
	vector<mon_struct> group;



	if(type_ == MPT_LAST){
		group.push_back(mon_struct(MON_ZOMBIE_GROUP_3,10)); //이걸 2로 바꿈
		group.push_back(mon_struct(MON_ZOMBIE_STONE,10));
		group.push_back(mon_struct(MON_ZOMBIE_NOISE,10));
		group.push_back(mon_struct(MON_ZOMBIE_SMALL,10));
		
		group.push_back(mon_struct(MON_BUG_FLY2,5));
		group.push_back(mon_struct(MON_BUG_BEETLE,10));
		group.push_back(mon_struct(MON_BUG_ANT_LION,10));
		group.push_back(mon_struct(MON_BUG_FLING,10));

		group.push_back(mon_struct(MON_SF_MAN,5));
		group.push_back(mon_struct(MON_WATER_MAN,5));
		group.push_back(mon_struct(MON_SPY,10));
		group.push_back(mon_struct(MON_PYRO2,10));
		
		group.push_back(mon_struct(MON_ALERT_ROBOT,8));
	}
	else if(type_ == MPT_ZOMBIE){		
		switch(level)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			group.push_back(mon_struct(MON_WEAK_ZOMBIE,20));
			group.push_back(mon_struct(MON_BIG_ZOMBIE,2));
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_1,2));
			group.push_back(mon_struct(MON_ZOMBIE_VIRUS,4));
			//첫번쨰로 나오는 좀비마을
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			group.push_back(mon_struct(MON_WEAK_ZOMBIE,12));
			group.push_back(mon_struct(MON_BIG_ZOMBIE,2));
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_1,2));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,2));
			group.push_back(mon_struct(MON_ZOMBIE_VIRUS,4));
			group.push_back(mon_struct(MON_ZOMBIE_BOOMER,2));
			group.push_back(mon_struct(MON_ZOMBIE_GHOST,2));
			//두번쨰로 나오는 좀비마을
			break;
		default:
			group.push_back(mon_struct(MON_WEAK_ZOMBIE,10));
			group.push_back(mon_struct(MON_BIG_ZOMBIE,1));
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_2,2));
			group.push_back(mon_struct(MON_ZOMBIE_SMALL,2));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,2));
			group.push_back(mon_struct(MON_ZOMBIE_VIRUS,4));
			group.push_back(mon_struct(MON_ZOMBIE_BOOMER,1));
			group.push_back(mon_struct(MON_ZOMBIE_GHOST,2));
			//세번쨰로 나오는 좀비마을
			break;
		}
	}
	else if(type_ == MPT_HUMAN){		
		switch(level)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			group.push_back(mon_struct(MON_PISTOL_REDNECK,10));
			group.push_back(mon_struct(MON_PYRO,5));
			group.push_back(mon_struct(MON_HUNTER,4));
			group.push_back(mon_struct(MON_STALKER,1));
			group.push_back(mon_struct(MON_BLUE_MAN,1));
			//첫번쨰로 나오는 인간마을
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			group.push_back(mon_struct(MON_PISTOL_REDNECK,5));
			group.push_back(mon_struct(MON_PYRO,3));
			group.push_back(mon_struct(MON_HUNTER,3));
			group.push_back(mon_struct(MON_STALKER,1));
			group.push_back(mon_struct(MON_BLUE_MAN,2));
			group.push_back(mon_struct(MON_ROCKET_MAN,2));
			group.push_back(mon_struct(MON_SF_MAN,3));
			group.push_back(mon_struct(MON_WATER_MAN,1));
			group.push_back(mon_struct(MON_SPY,3));
			group.push_back(mon_struct(MON_ALERT_ROBOT,1));
			//두번쨰로 나오는 인간마을
			break;
		default:
			group.push_back(mon_struct(MON_PYRO2,3));
			group.push_back(mon_struct(MON_HUNTER,3));
			group.push_back(mon_struct(MON_STALKER,1));
			group.push_back(mon_struct(MON_BLUE_MAN,3));
			group.push_back(mon_struct(MON_ROCKET_MAN,3));
			group.push_back(mon_struct(MON_SF_MAN,4));
			group.push_back(mon_struct(MON_WATER_MAN,2));
			group.push_back(mon_struct(MON_SPY,3));
			group.push_back(mon_struct(MON_ALERT_ROBOT,2));
			//세번쨰로 나오는 인간마을
			break;
		}
	}
	else if(type_ == MPT_BUG){		
		switch(level)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			group.push_back(mon_struct(MON_BUG_WEAK,10));
			group.push_back(mon_struct(MON_BUG_FLY,5));
			group.push_back(mon_struct(MON_BUG_BOMB,2));
			//첫번쨰로 나오는 벌레소굴
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			group.push_back(mon_struct(MON_BUG_WEAK,10));
			group.push_back(mon_struct(MON_BUG_FLY,5));
			group.push_back(mon_struct(MON_BUG_BOMB,3));
			group.push_back(mon_struct(MON_BUG_FLY2,3));
			group.push_back(mon_struct(MON_SPIDER,3));
			group.push_back(mon_struct(MON_BUG_BEETLE,1));
			//두번쨰로 나오는 벌레소굴
			break;
		default:
			group.push_back(mon_struct(MON_BUG_WEAK,3));
			group.push_back(mon_struct(MON_BUG_BOMB,1));
			group.push_back(mon_struct(MON_BUG_FLY2,3));
			//group.push_back(mon_struct(MON_SPIDER,3));
			group.push_back(mon_struct(MON_BUG_ANT_LION,2));
			group.push_back(mon_struct(MON_BUG_FLING,2));
			//세번쨰로 나오는 벌레소굴
			break;
		}
	}
	else{

		switch(level)
		{
		case 0:
			//group.push_back(mon_struct(MON_BUG_FLING,100));
			//d1ddddgroup.push_back(mon_struct(MON_BUG_BEETLE,100));
			//group.push_back(mon_struct(MON_WEAK_ZOMBIEd1,100));

			group.push_back(mon_struct(MON_WEAK_ZOMBIE,10));
			group.push_back(mon_struct(MON_PISTOL_REDNECK,10));
			group.push_back(mon_struct(MON_BIG_ZOMBIE,2));
			group.push_back(mon_struct(MON_BUG_WEAK,2));
			break;
		case 1:
			group.push_back(mon_struct(MON_WEAK_ZOMBIE,8));
			group.push_back(mon_struct(MON_PISTOL_REDNECK,10));
			group.push_back(mon_struct(MON_BIG_ZOMBIE,4));
			group.push_back(mon_struct(MON_BUG_WEAK,4));
			group.push_back(mon_struct(MON_PYRO,3));
			break;
		case 2:
			group.push_back(mon_struct(MON_WEAK_ZOMBIE,6));
			group.push_back(mon_struct(MON_BIG_ZOMBIE,4));
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_1,2));

			group.push_back(mon_struct(MON_BUG_WEAK,4));

			group.push_back(mon_struct(MON_PISTOL_REDNECK,8));
			group.push_back(mon_struct(MON_PYRO,5));
			group.push_back(mon_struct(MON_HUNTER,2));
			group.push_back(mon_struct(MON_STALKER,2));
			break;
		case 3:
			group.push_back(mon_struct(MON_WEAK_ZOMBIE,5));
			group.push_back(mon_struct(MON_BIG_ZOMBIE,5));
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_1,10));
			group.push_back(mon_struct(MON_ZOMBIE_VIRUS,1));

			group.push_back(mon_struct(MON_BUG_WEAK,10));
			group.push_back(mon_struct(MON_BUG_BOMB,1));

			group.push_back(mon_struct(MON_PYRO,10));
			group.push_back(mon_struct(MON_PISTOL_REDNECK,5));
			group.push_back(mon_struct(MON_HUNTER,10));
			group.push_back(mon_struct(MON_BLUE_MAN,5));
			group.push_back(mon_struct(MON_STALKER,5));
			break;
		case 4:
			group.push_back(mon_struct(MON_WEAK_ZOMBIE,5));
			group.push_back(mon_struct(MON_PISTOL_REDNECK,5));
			group.push_back(mon_struct(MON_BIG_ZOMBIE,3));
			group.push_back(mon_struct(MON_ZOMBIE_VIRUS,5));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,1));
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_1,10));

			group.push_back(mon_struct(MON_BUG_WEAK,10));
			group.push_back(mon_struct(MON_BUG_BOMB,2));
			group.push_back(mon_struct(MON_BUG_FLY,3));

			group.push_back(mon_struct(MON_PYRO,8));
			group.push_back(mon_struct(MON_HUNTER,10));
			group.push_back(mon_struct(MON_BLUE_MAN,5));
			group.push_back(mon_struct(MON_STALKER,5));
			break;
		case 5:
			group.push_back(mon_struct(MON_ZOMBIE_BOOMER,5));
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_1,10));
			group.push_back(mon_struct(MON_ZOMBIE_VIRUS,5));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,5));

			group.push_back(mon_struct(MON_BUG_WEAK,10));
			group.push_back(mon_struct(MON_BUG_BOMB,5));
			group.push_back(mon_struct(MON_BUG_FLY,10));

			group.push_back(mon_struct(MON_PYRO,10));
			group.push_back(mon_struct(MON_BLUE_MAN,10));
			group.push_back(mon_struct(MON_HUNTER,10));
			group.push_back(mon_struct(MON_ROCKET_MAN,5));
			break;
		case 6:
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_1,5));
			group.push_back(mon_struct(MON_ZOMBIE_BOOMER,5));
			group.push_back(mon_struct(MON_ZOMBIE_VIRUS,5));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,5));

			group.push_back(mon_struct(MON_BUG_WEAK,10));
			group.push_back(mon_struct(MON_BUG_BOMB,5));
			group.push_back(mon_struct(MON_BUG_FLY,5));
			group.push_back(mon_struct(MON_SPIDER,5));

			group.push_back(mon_struct(MON_PYRO,5));
			group.push_back(mon_struct(MON_BLUE_MAN,5));
			group.push_back(mon_struct(MON_HUNTER,10));
			group.push_back(mon_struct(MON_ROCKET_MAN,5));
			group.push_back(mon_struct(MON_SF_MAN,5));
			break;
		case 7:
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_2,5));
			group.push_back(mon_struct(MON_ZOMBIE_BOOMER,10));
			group.push_back(mon_struct(MON_ZOMBIE_VIRUS,10));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,10));

			group.push_back(mon_struct(MON_BUG_WEAK,10));
			group.push_back(mon_struct(MON_BUG_BOMB,10));
			group.push_back(mon_struct(MON_BUG_FLY,10));
			group.push_back(mon_struct(MON_SPIDER,10));

			group.push_back(mon_struct(MON_PYRO,3));
			group.push_back(mon_struct(MON_BLUE_MAN,3));
			group.push_back(mon_struct(MON_HUNTER,10));
			group.push_back(mon_struct(MON_ROCKET_MAN,10));
			group.push_back(mon_struct(MON_SF_MAN,10));
			group.push_back(mon_struct(MON_WATER_MAN,5));
			break;
		case 8:
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_2,5));
			group.push_back(mon_struct(MON_ZOMBIE_BOOMER,10));
			group.push_back(mon_struct(MON_ZOMBIE_VIRUS,10));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,10));

			group.push_back(mon_struct(MON_BUG_WEAK,10));
			group.push_back(mon_struct(MON_BUG_BOMB,5));
			group.push_back(mon_struct(MON_BUG_FLY,10));
			group.push_back(mon_struct(MON_SPIDER,10));
			group.push_back(mon_struct(MON_BUG_FLY2,5));

			group.push_back(mon_struct(MON_HUNTER,10));
			group.push_back(mon_struct(MON_ROCKET_MAN,10));
			group.push_back(mon_struct(MON_SF_MAN,10));
			group.push_back(mon_struct(MON_WATER_MAN,5));
			break;
		case 9:
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_2,10)); //이걸 2로 바꿈
			group.push_back(mon_struct(MON_ZOMBIE_BOOMER,10));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,10));
			group.push_back(mon_struct(MON_ZOMBIE_GHOST,10));

			group.push_back(mon_struct(MON_BUG_BOMB,5));
			group.push_back(mon_struct(MON_BUG_FLY,10));
			group.push_back(mon_struct(MON_BUG_FLY2,10));
			group.push_back(mon_struct(MON_SPIDER,10));
			group.push_back(mon_struct(MON_BUG_BEETLE,2));

			group.push_back(mon_struct(MON_HUNTER,10));
			group.push_back(mon_struct(MON_ROCKET_MAN,10));
			group.push_back(mon_struct(MON_SF_MAN,10));
			group.push_back(mon_struct(MON_WATER_MAN,10));
			group.push_back(mon_struct(MON_SPY,5));
						
			group.push_back(mon_struct(MON_ALERT_ROBOT,2));
			break;
		case 10:
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_2,10)); //이걸 2로 바꿈
			group.push_back(mon_struct(MON_ZOMBIE_BOOMER,10));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,10));
			group.push_back(mon_struct(MON_ZOMBIE_GHOST,10));

			group.push_back(mon_struct(MON_BUG_BOMB,5));
			group.push_back(mon_struct(MON_BUG_FLY,10));
			group.push_back(mon_struct(MON_BUG_FLY2,10));
			group.push_back(mon_struct(MON_BUG_BEETLE,10));

			group.push_back(mon_struct(MON_HUNTER,5));
			group.push_back(mon_struct(MON_ROCKET_MAN,10));
			group.push_back(mon_struct(MON_SF_MAN,10));
			group.push_back(mon_struct(MON_WATER_MAN,10));
			group.push_back(mon_struct(MON_SPY,10));
			group.push_back(mon_struct(MON_PYRO2,1));

			
			group.push_back(mon_struct(MON_ALERT_ROBOT,5));
			break;
		case 11:
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_2,10)); //이걸 2로 바꿈
			group.push_back(mon_struct(MON_ZOMBIE_STONE,5));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,10));
			group.push_back(mon_struct(MON_ZOMBIE_GHOST,10));

			group.push_back(mon_struct(MON_BUG_FLY,5));
			group.push_back(mon_struct(MON_BUG_FLY2,12));
			group.push_back(mon_struct(MON_SPIDER,7));
			group.push_back(mon_struct(MON_BUG_BEETLE,12));
			group.push_back(mon_struct(MON_BUG_ANT_LION,3));

			group.push_back(mon_struct(MON_HUNTER,5));
			group.push_back(mon_struct(MON_ROCKET_MAN,5));
			group.push_back(mon_struct(MON_SF_MAN,10));
			group.push_back(mon_struct(MON_WATER_MAN,10));
			group.push_back(mon_struct(MON_SPY,10));
			group.push_back(mon_struct(MON_PYRO2,10));
			
			group.push_back(mon_struct(MON_ALERT_ROBOT,10));
			break;
		case 12:
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_2,10)); //이걸 2로 바꿈
			group.push_back(mon_struct(MON_ZOMBIE_BOOMER,5));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,10));
			group.push_back(mon_struct(MON_ZOMBIE_GHOST,10));
			group.push_back(mon_struct(MON_ZOMBIE_SMALL,5));
			
			group.push_back(mon_struct(MON_SPIDER,5));
			group.push_back(mon_struct(MON_BUG_FLY2,10));
			group.push_back(mon_struct(MON_BUG_BEETLE,10));
			group.push_back(mon_struct(MON_BUG_ANT_LION,5));
			group.push_back(mon_struct(MON_BUG_FLING,3));

			group.push_back(mon_struct(MON_ROCKET_MAN,5));
			group.push_back(mon_struct(MON_SF_MAN,5));
			group.push_back(mon_struct(MON_WATER_MAN,10));
			group.push_back(mon_struct(MON_SPY,10));
			group.push_back(mon_struct(MON_PYRO2,10));
			
			group.push_back(mon_struct(MON_ALERT_ROBOT,10));
			break;
		case 13:
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_3,10)); //이걸 2로 바꿈
			group.push_back(mon_struct(MON_ZOMBIE_STONE,7));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,10));
			group.push_back(mon_struct(MON_ZOMBIE_GHOST,10));
			group.push_back(mon_struct(MON_ZOMBIE_SMALL,5));
			
			group.push_back(mon_struct(MON_BUG_FLY2,10));
			group.push_back(mon_struct(MON_BUG_BEETLE,10));
			group.push_back(mon_struct(MON_BUG_ANT_LION,10));
			group.push_back(mon_struct(MON_BUG_FLING,5));

			group.push_back(mon_struct(MON_ROCKET_MAN,5));
			group.push_back(mon_struct(MON_SF_MAN,5));
			group.push_back(mon_struct(MON_WATER_MAN,10));
			group.push_back(mon_struct(MON_SPY,10));
			group.push_back(mon_struct(MON_PYRO2,10));
			
			group.push_back(mon_struct(MON_ALERT_ROBOT,10));
			break;
		case 14:
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_3,10)); //이걸 2로 바꿈
			group.push_back(mon_struct(MON_ZOMBIE_STONE,7));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,10));
			group.push_back(mon_struct(MON_ZOMBIE_SMALL,10));
			
			group.push_back(mon_struct(MON_BUG_FLY2,10));
			group.push_back(mon_struct(MON_BUG_BEETLE,10));
			group.push_back(mon_struct(MON_BUG_ANT_LION,10));
			group.push_back(mon_struct(MON_BUG_FLING,10));

			group.push_back(mon_struct(MON_ROCKET_MAN,5));
			group.push_back(mon_struct(MON_SF_MAN,10));
			group.push_back(mon_struct(MON_WATER_MAN,10));
			group.push_back(mon_struct(MON_SPY,10));
			group.push_back(mon_struct(MON_PYRO2,10));

			group.push_back(mon_struct(MON_ALERT_ROBOT,8));
			break;
		case 15:
		default:
			group.push_back(mon_struct(MON_ZOMBIE_GROUP_3,10)); //이걸 2로 바꿈
			group.push_back(mon_struct(MON_ZOMBIE_STONE,10));
			group.push_back(mon_struct(MON_ZOMBIE_NOISE,10));
			group.push_back(mon_struct(MON_ZOMBIE_SMALL,10));
			
			group.push_back(mon_struct(MON_BUG_FLY2,5));
			group.push_back(mon_struct(MON_BUG_BEETLE,10));
			group.push_back(mon_struct(MON_BUG_ANT_LION,10));
			group.push_back(mon_struct(MON_BUG_FLING,10));

			group.push_back(mon_struct(MON_SF_MAN,10));
			group.push_back(mon_struct(MON_WATER_MAN,10));
			group.push_back(mon_struct(MON_SPY,10));
			group.push_back(mon_struct(MON_PYRO2,10));

			group.push_back(mon_struct(MON_ALERT_ROBOT,8));
			break;
		}
	}



	int total = 0;
	for(vector<mon_struct>::iterator it = group.begin(); it != group.end();it++)
		total+=it->percent;

	int rand_ = randA_1(total);
	vector<mon_struct>::iterator it;
	for(it = group.begin(); it != group.end(); it++)
	{
		if(rand_<=it->percent)
		{
			return it->id;
		}
		else
			rand_ -= it->percent;	
	}
	return MON_WEAK_ZOMBIE;
}

void Game_Manager::StageMake()
{	
	for(int i = 0; i<SS_MAX_FLOOR; i++)
		stage_kind[i] = SS_NORMAL;

	int kind_[3] = {0,0,0};
	kind_[0] = rand_int(1,3);
	kind_[1] = (kind_[0]==1? rand_int(2,3):(kind_[0]==2? rand_int(0,1)*2+1:rand_int(1,2)));
	kind_[2] = 6-kind_[0]-kind_[1];


	stage_kind[rand_int(2,4)] = (SPECIAL_STAGE)kind_[0];
	stage_kind[rand_int(6,8)] = (SPECIAL_STAGE)kind_[1];
	stage_kind[rand_int(10,12)] = (SPECIAL_STAGE)kind_[2];
	
	stage_kind[15] = SS_LAST;


}

void Game_Manager::NextStage()
{
	level++;
	switch(stage_kind[level]){
	case SS_NORMAL:
	default:
		StageInit(level,MPT_NOMAL,rand_int(1,3),13);
		break;
	case SS_ZOMBIE:
		StageInit(level,MPT_ZOMBIE,rand_int(1,3),16);
		break;
	case SS_HUMAN:
		StageInit(level,MPT_HUMAN,rand_int(1,3),12);
		break;
	case SS_BUG:
		StageInit(level,MPT_BUG,rand_int(1,3),12);
		break;
	case SS_LAST:
		StageInit(level,MPT_LAST,rand_int(1,3),60);
		break;
	}
}


void Game_Manager::StageInit(int level_, MAP_TYPE type_, int box_, int monster_)
{
	if(!player)
		return;
	
	switch(type_){
	case MPT_NOMAL:
		StopBGM(bgm_dungeon_1);
		StopBGM(bgm_dungeon_2);
		StopBGM(bgm_dungeon_3);
		PlayBGM(bgm_dungeon_0);
		break;
	case MPT_ZOMBIE:
		StopBGM(bgm_dungeon_0);
		StopBGM(bgm_dungeon_2);
		StopBGM(bgm_dungeon_3);
		PlayBGM(bgm_dungeon_1);
		break;
	case MPT_HUMAN:
		StopBGM(bgm_dungeon_0);
		StopBGM(bgm_dungeon_1);
		StopBGM(bgm_dungeon_3);
		PlayBGM(bgm_dungeon_2);
		break;
	case MPT_BUG:
		StopBGM(bgm_dungeon_0);
		StopBGM(bgm_dungeon_1);
		StopBGM(bgm_dungeon_2);
		PlayBGM(bgm_dungeon_3);
		break;
	default:
		StopBGM(bgm_dungeon_1);
		StopBGM(bgm_dungeon_2);
		StopBGM(bgm_dungeon_3);
		PlayBGM(bgm_dungeon_0);
		break;
	}

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
		for(list<Unit*>::iterator it = unit_list.begin(); it != unit_list.end(); )
		{
			if(!(*it)->isPlayer())
			{
				delete (*it);
				list<Unit*>::iterator temp = it++;
				unit_list.erase(temp);
			}
			else
				it++;
		}
	}	

	//player->Heal(player->GetFloorHeal());
	//player->SuppleBullet(player->GetFloorBullet());




	//종류에 따라
	map->MapMake(this, level_, type_);
	if(type_ == MPT_ZOMBIE)
		shot_list.push_back(new Effect_fog(&tex_smoke));
	if(type_ == MPT_LAST)
		shot_list.push_back(new Effect_last_message(this));
	map->MapInit();

	while(type_ != MPT_BUG) //벌레탄에서는 맵제작과 동시에 시작위치가 정해짐
	{
		coord_def c_ = GetRandomPos();
		if(type_ == MPT_HUMAN)
		{
			if(1/*rand_int(0,3)*/)
			{					
				list<Shot_base*>::iterator it = shot_list.begin();
				for(; it != shot_list.end(); it++)
				{
					if((*it)->isHouse())
					{
						if((*it)->HouseCollution(c_))
						{
							break;
						}
					}
				}
				if(it == shot_list.end())
					continue;
			}
		}
		player->Move(c_.x,c_.y);


		
		//item_list.push_back(New_Main_Weapon(MWK_RIFLE_PISTOL_BIG, c_, -1));
		break;
	}

	while(type_ != MPT_BUG && type_ != MPT_LAST) //벌레탄에서는 무조건 포탈은 한 가운데
	{
		coord_def c_ = GetRandomPos();
		if(!player->collution(c_,player->GetView()))
		{			
			if(type_ == MPT_HUMAN)
			{
				if(1/*rand_int(0,3)*/)
				{					
					list<Shot_base*>::iterator it = shot_list.begin();
					for(; it != shot_list.end(); it++)
					{
						if((*it)->isHouse())
						{
							if((*it)->HouseCollution(c_))
							{
								break;
							}
						}
					}
					if(it == shot_list.end())
						continue;
				}
			}
			Item* portal_ = new Portal(&tex_potal, c_,false);
			item_list.push_back(portal_);
			next_portal = portal_;
			break;
		}
	}

	if(type_ == MPT_LAST)
	{
		next_portal = NULL;
		for(int i = 0; i < player->GetSwitch(); i++)
		{
			while(1) //마지막 층에서 3개의 스위치
			{
				coord_def c_ = GetRandomPos();
				if(!player->collution(c_,player->GetView()))
				{						
					Item* button_ = new Button(c_);
					item_list.push_back(button_);
					break;
				}
			}
		}
	}

		
	for(int i = 0;i<box_;)
	{

		coord_def c_ = GetRandomPos();
		if(type_ == MPT_HUMAN)
		{
			if(1/*rand_int(0,3)*/)
			{					
				list<Shot_base*>::iterator it = shot_list.begin();
				for(; it != shot_list.end(); it++)
				{
					if((*it)->isHouse())
					{
						if((*it)->HouseCollution(c_))
						{
							break;
						}
					}
				}
				if(it == shot_list.end())
					continue;
			}
		}

		unit_list.push_back(new Box(&tex_box, c_, level_));
		i++;
	}

	for(int i = 0;i<monster_;)
	{
		coord_def c_ = GetRandomPos();
		if(!player->collution(c_,player->GetView()*1.5f))
		{
			if(type_ == MPT_HUMAN)
			{
				if(1/*rand_int(0,3)*/)
				{					
					list<Shot_base*>::iterator it = shot_list.begin();
					for(; it != shot_list.end(); it++)
					{
						if((*it)->isHouse())
						{
							if((*it)->HouseCollution(c_))
							{
								break;
							}
						}
					}
					if(it == shot_list.end())
						continue;
				}
			}
			unit_list.push_back(New_Monster(GetStageMonster(level,type_), c_, -1, (type_ == MPT_LAST)?MF_BURROW:0));
			i++;
		}
	}
	NamedMake(level);
	player->EnterMap(this, level_);
	
	if(level_ == 0)
		heal_stack=0;
	else
		heal_stack+=5;

	//item_list.push_back(new Rifle(rifle__shot_gun, coord_def(200,200), -1));
	//item_list.push_back(new Fire(rifle__flame_thrower, coord_def(180,200), -1));
	//item_list.push_back(new Sub_Kevlar(NULL, coord_def(120,350),-1));
	//item_list.push_back(new Melee_Weapon(melee__club, coord_def(120,400),-1));
	if(player->GetSniper()){
		player->Special(this, key->GetMousePos()+focus, 0.0f);
	}
	SetSniperMode(false,coord_def(),1.0f,false);

	if(player->GetMapHack())
	{
		map->map_hack();
	}
}
