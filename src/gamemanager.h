//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: gamemanager.h
//
// 내용: 게임통괄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __GAME_MANAGER_H__
#define  __GAME_MANAGER_H__

#include "coord_def.h"
#include "map.h"
#include "damage.h"
#include <list>
#include <windows.h>

using namespace std;

class Unit;
class Player;
class Map;
class Key_Manager;
class Direct_Manager;
class BitRect;
class Shot_base;
class Item;
class Character_Maker;
class NetworkManager;
class NetworkClient;
class Monster;


enum SPECIAL_STAGE
{
	SS_NORMAL = 0,
	SS_ZOMBIE = 1,
	SS_HUMAN = 2,
	SS_BUG = 3,
	SS_LAST = 4,
	SS_MAX_FLOOR = 16
};


class Game_Manager
{
	int count;
	int level;
	int state;
	float scale; //시스템을 제외한 이미지 확대크기
	int heal_stack;
	bool sniper_mode;
	coord_def focus;

	SPECIAL_STAGE stage_kind[SS_MAX_FLOOR];

	Character_Maker* char_maker;
	NetworkManager* Network_host;
	NetworkClient* Network_client;

	bool next_floor;

	string full_text;

	static Game_Manager* pInstance;
	static HWND handle;

	Game_Manager();
	Game_Manager(const Game_Manager* rhs);
	~Game_Manager();
	//void SetSight(coord_def c_, int radius_);
	//void SetFogTexture();

public:
	Player* player;
	Item* next_portal;

	list<Item*> item_list;
	list<Shot_base*> shot_list;
	list<Unit*> unit_list;
	Key_Manager* key;//입력을 받을 매니져 클래스
	Direct_Manager* direct;
	Map* map;

	static Game_Manager* CreateInstance();
	static void DestroyInstance(Game_Manager* pInstance_);
	static void SetHandle(HWND handle_);

	
	void NextLevel(){next_floor = true;};
	/*Map* GetMapClass(){return map;};*/

	coord_def GetPlayerPos();
	bool GetStateView(); //상태보기가 가능할때
	bool GetMonSightView(); //시야보기가 가능할때

	void SetKeyClass(Key_Manager* key_){key = key_;};
	void SetDirectClass(Direct_Manager* direct_);
	void SetState(int state_){state = state_;};

	bool isPlayerLive();

	void GameMenu();
	void StageMake();
	void NextStage();
	void StageInit(int level_, MAP_TYPE type_, int box_, int monster_);
	void NamedMake(int level_);
	void TargetLost(); //유닛이 사라졌을때 ai의 타겟팅 없애야함.
	void InvisibleLost(coord_def c); //투명이 되었을때
	void GiveExp(int team_, int value_); //team유닛에게 value_의 경험치를 줌
	void KillMonster(int team_, Monster* monster_, Damage_Type type_, float damage_, bool back_stab_); //team유닛이 유닛을 죽였다.
	void Noise(int team_, coord_def pos_, float size_); //team_이 pos위치에서 size의 소음을 냈다.
	coord_def GetRandomPos();
	int GetMonsterNum();
	bool SetSniperMode(bool ok_, coord_def pos_, float scale_, bool mouse_ = true);
	bool Heal_percent(bool box_);
	SPECIAL_STAGE GetCurrentStage(){return stage_kind[level];};
	void SetText(const char* text_){full_text = text_;};
	void AddText(const char* text_){full_text += text_;};


	static void Loop();
	void SelectLoop();
	void GameLoop();
	void NetworkLoop();
	void TextLoop();


	static bool Draw();
	bool SelectDraw();
	bool GameDraw();
	bool NetworkDraw();
	bool TextDraw();


};




#endif // __GAME_MANAGER_H__