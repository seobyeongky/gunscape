//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: monster.h
//
// 내용: 플레이어를 다루는 클래스(네트워크 플레이를 염두에 두고 만들자.)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MONSTER_H__
#define  __MONSTER_H__

#include "unit.h"
#include "ai.h"
#include "map.h"


class Main_Weapon;

enum Monster_Flag
{
	MF_DROP_BULLET=1<<0,	
	MF_TRUE_SIGHT=1<<1, //트루사이트. 벽을 뚫는 시선
	MF_HUMAN=1<<2, //인간
	MF_ZOMBIE=1<<3, //좀비
	MF_BUG=1<<4, //벌레
	MF_ROBOT=1<<5, //기계
	MF_BURROW=1<<6, //진짜 버로우는 아니고 맵의 과부하를 줄이기위해 숨어있음
	MF_INVISIBLE_RESIST=1<<7 //투명으로 따돌릴수 없게된다.
};




struct main_weapon_infor;


typedef struct monster_infor
{
	Monster_Index index;
	Texture* texture;
	Texture* second_texture;
	const char* name;
	main_weapon_infor* weapon;
	float minimum_distans;
	float maximum_distans;
	float panalty;
	float damage;

	int hp;
	float size;
	float speed;
	float sight;
	int exp;
	int level;

	int flag;	
}monster_infor;


class Monster: public Unit
{
protected:
	Monster_Index index;
	Ai_Manager* ai;

	Main_Weapon* weapon;
	float minimum_distans; //총쏘는 최소거리
	float maximum_distans; //총쏘는 최소거리
	float panalty;
	float damage; //근접 데미지
	bool item_drop;	

	int exp;

	int flag;

	int nonmove_delay;

	int target_continue;


public:
	Monster(monster_infor& infor_, float x_, float y_, int team_, int time_ = 0);
	virtual ~Monster();
	
	virtual bool charDraw(Game_Manager* gm_, coord_def offset, float size_);



	virtual void PlusFlag(int flag_){flag = flag | flag_;}

	virtual void SetAi(monster_state state_, Unit* head_ = NULL, int level_ = 0);
	virtual void SetWeapon(Main_Weapon* weapon_);

	virtual Monster_Index Getindex(){return index;};
	Main_Weapon* GetMainWeapon(){return weapon;};
	float GetMinimumDistans(){return minimum_distans;};
	float GetMaximumDistans(){return maximum_distans;};
	float GetDamage(){return damage;};
	virtual monster_state GetState(){return ai->GetState();};
	virtual Vamp_Type GetKind();
	virtual Ai_Manager* GetAi(){return ai;};
	int GetTargetContinue(){return target_continue;};

	bool CheckFlag(Monster_Flag flag_);

	virtual int SetDamage(Game_Manager* gm_, coord_def c, Damage_Type type_, float damage_, int team_, float sniper_ = 1.0f, int critical_ = 0);
	virtual void SetNoise(Game_Manager* gm_, int team_, coord_def pos_);
	void SetTargetContinue(int target_continue_){target_continue = target_continue_;};
	virtual void SetItemDrop(bool drop_){item_drop = drop_;};
	


	virtual bool isPlayer(){return false;};	
	virtual bool isBackStabbing();	
	virtual bool isSleep(); 

	virtual bool CanSpeeing(){if(GetKind()!=VT_ZOMBIE)return true;return false;};		
	
	
	virtual bool Action_in(Game_Manager* gm_);
	virtual bool Special_Action(Game_Manager* gm_){return false;};
	virtual void Approach(Game_Manager* gm_, coord_def c, Unit* target_){};
	virtual bool TargetLost();
	virtual bool TargetBlinding();
	virtual bool InvisibleLost(coord_def c);
	virtual void Sleep();	

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);

	virtual bool DropItem(Game_Manager* gm_);

	virtual bool Melee(Game_Manager* gm_);
	virtual void MeleeDamage(Game_Manager* gm_, Unit* target_);

};


Monster_Index GetStageMonster(int level, MAP_TYPE type_);
void InitNamed();

#endif // __MONSTER_H__