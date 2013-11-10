//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: gamemanager.h
//
// ����: �������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __GAME_MANAGER_H__
#define  __GAME_MANAGER_H__

#include "coord_def.h"
#include "map.h"
#include "damage.h"
#include "stages.h"
#include "smap.h"
#include <list>
#include <vector>
#include <windows.h>
#include <opznet\shared_structs.h>


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

class Command;

struct cl_t
{
	string	name;
	int		sel;
	Player * player;

	cl_t(void) : name(), sel(0), player(nullptr) {
	}

	cl_t(const string & name_) : name(name_), sel(0), player(nullptr) {
	}
};

class Game_Manager
{
	int level;
	int state;
	float scale; //�ý����� ������ �̹��� Ȯ��ũ��
	int heal_stack;
	bool sniper_mode;
	coord_def focus;

	SPECIAL_STAGE stage_kind[SS_MAX_FLOOR];

	Character_Maker* char_maker;
	NetworkManager* Network_host;
	NetworkClient* Network_client;

	bool next_floor;

	string full_text;
	
	int accum;
	bool command_send_ok;
	int	state_handle_count;

	bool wait_scene;

	static Game_Manager* pInstance;
	static HWND handle;

	Game_Manager();
	Game_Manager(const Game_Manager* rhs);
	~Game_Manager();
	//void SetSight(coord_def c_, int radius_);
	//void SetFogTexture();

	typedef vector<Command> commands_t;

	commands_t commands;

	typedef smap<opznet::ID, cl_t>::Iter cl_iter_t;
	// �ٸ� ��� ī�޶�� ���� �ִ°�? ����
	bool otherview;

	void HandlePlayer(Player * p);
	bool CheckCollideWithPlayersView(const coord_def  &c_);
	bool IsValidPos(int x_, int y_);

	bool	AnyonePlaying();
	Player * GetFirstPlayingCl();
	Player * GetNextPlayingCl(Player * cur);
	Player * GetPrevPlayingCl(Player * cur);

public:
	Player* player;
	Item* next_portal;

	list<Item*> item_list;
	list<Shot_base*> shot_list;
	list<Unit*> unit_list;
	Key_Manager* key;//�Է��� ���� �Ŵ��� Ŭ����
	Direct_Manager* direct;
	Map* map;

	static Game_Manager* CreateInstance();
	static void DestroyInstance(Game_Manager* pInstance_);
	static void SetHandle(HWND handle_);

	
	void NextLevel(){next_floor = true;};
	/*Map* GetMapClass(){return map;};*/

	coord_def GetPlayerPos();
	bool GetStateView(); //���º��Ⱑ �����Ҷ�
	bool GetMonSightView(); //�þߺ��Ⱑ �����Ҷ�

	void SetKeyClass(Key_Manager* key_){key = key_;};
	void SetDirectClass(Direct_Manager* direct_);
	void SetState(int state_){state = state_;};

	bool isPlayerLive();

	void GameMenu();

	void MakeStageTypes();
	void SetStageTypesFrom(const vector<int> stages);	
	void MakeStage(int level);
	void NextStage();

	void MovePlayersToStartPos(MAP_TYPE type_);
	void EnterPlayers(int level_);
	void StageInit(int level_, MAP_TYPE type_, int box_, int monster_);
	void NamedMake(int level_);
	void TargetLost(); //������ ��������� ai�� Ÿ���� ���־���.
	void InvisibleLost(coord_def c); //������ �Ǿ�����
	void GiveExp(int team_, int value_); //team���ֿ��� value_�� ����ġ�� ��
	void KillMonster(int team_, Monster* monster_, Damage_Type type_, float damage_, bool back_stab_); //team������ ������ �׿���.
	void Noise(int team_, coord_def pos_, float size_); //team_�� pos��ġ���� size�� ������ �´�.
	coord_def GetRandomPos();
	int GetMonsterNum();
	bool SetSniperMode(bool ok_, coord_def pos_, float scale_, bool mouse_ = true);
	bool Heal_percent(bool box_);
	SPECIAL_STAGE GetCurrentStage(){return stage_kind[level];};
	void SetText(const char* text_){full_text = text_;};
	void AddText(const char* text_){full_text += text_;};


	static void Loop();
	void SelectLoop();
	void LocalGameStart();
	void MultiGameStart();

	void ConnectToServer();
	void HandleInputs();
	void HandleCommand(Command & c);
	void HandleCommands();
	void HandleState();
	void GameLoop();

	void NetworkLoop();

	void TextLoop();


	static bool Draw();
	bool SelectDraw();
	bool GameDraw();
	bool NetworkDraw();
	bool TextDraw();
	void WaitDraw();

	void UpdateWaitMessage();

};




#endif // __GAME_MANAGER_H__