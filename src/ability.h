//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ability.h
//
// 내용: 능력 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ABILITY_H__
#define  __ABILITY_H__

#include <map>
#include <vector>
#include "damage.h"
using namespace std;


class Player;
class Monster;
class Main_Weapon;
class Sub_Weapon;
class Melee_Weapon;
class Game_Manager;


enum Ability_Type
{
	AT_PASSIVE,
	AT_USE,
	AT_INSTANCE,
	AT_MAX
};

typedef struct abil_level
{
	string name;
	int level;
}abil_level;


class Ability
{
protected:
	string name; //이름
	int id; //고유번호
	int level; //이 능력의 레벨
	int max_level; //이 능력의 최대 레벨
	int percent; //이 확률이 선택될 확률
	int need_level; //이 능력에 필요한 레벨
	Ability_Type type; //이 능력의 타입
	//패시브: 한번얻으면 계속 효과를 발휘하는 능력. 가장 흔함
	//사용형: 얻으면 스태미나등을 소모해서 사용할수있는 능력이 생긴다. 총 2~3개 밖에 가지지못함
	//즉시형: 사용즉시 사라지고 효과가 발휘됨
	
	static int abil_num; //능력 총 갯수
	static map<string,Ability*> ability_list;

	Ability(const char* name_, int level_, int max_level_, int percent_, int need_level_, Ability_Type type_);


	vector<abil_level> need_abil; //해당 스킬과 레벨이 필요한 경우
	vector<abil_level> oppose_abil; //해당 스킬의 레벨 이상인경우 존재 불가

public:	
	virtual ~Ability();

	virtual Ability* Clone(int level_)=0;

	static void InitAbility(Game_Manager* gm_);
	static void ReleaseAbility();
	static bool AddAbility(Ability* ability_);
	static bool GetAbility(Player* player_, int num); //만약 플레이어의 어빌리티가 이미 차있으면 무시.

	bool Learn(Game_Manager* gm_, Player* player_); //처음 능력을 얻었을때
	bool UnLearn(Game_Manager* gm_, Player* player_); //능력이 삭제될때

	bool Active(Game_Manager* gm_, Player* player_); //패시브 능력이 사용되어진다. 이건 비가상함수
	bool UnActive(Game_Manager* gm_, Player* player_); //패시브 능력이 취소된다. 이건 비가상함수
	bool UseOnOff(Game_Manager* gm_, Player* player_); //사용능력을 키고 끈다. 비가상함수


	virtual bool Action(Game_Manager* gm_, Player* player_){return false;} //패시브, 사용식에서 매 프레임실행 함수

	virtual bool InstanceActive(Player* player_){return false;};

	virtual bool isUsing(){return false;}; //현재 능력을 사용중인지?
	virtual bool Use(Game_Manager* gm_, Player* player_){return false;} //사용형 능력의 사용
	virtual bool UnUse(Game_Manager* gm_, Player* player_){return false;}//사용형 능력의 취소

	
	virtual bool KillMonster(Game_Manager* gm_, Monster* monster_, Player* player_, Damage_Type type_, float damage_, bool back_stab_){return false;};
	virtual bool EnterMap(Game_Manager* gm_, Player* player_, int level_){return false;};

	virtual bool ActiveMainWeapon(Main_Weapon* weapon_){return false;};
	virtual bool ActiveSubWeapon(Sub_Weapon* weapon_){return false;};
	virtual bool ActiveMeleeWeapon(Melee_Weapon* weapon_){return false;};
	virtual bool ActivePlayer(Player* player_){return false;};
	virtual bool ActiveGame(Game_Manager* gm_, Player* player_){return false;};

	virtual bool UnActiveMainWeapon(Main_Weapon* weapon_){return false;};
	virtual bool UnActiveSubWeapon(Sub_Weapon* weapon_){return false;};
	virtual bool UnActiveMeleeWeapon(Melee_Weapon* weapon_){return false;};
	virtual bool UnActivePlayer(Player* player_){return false;};
	virtual bool UnActiveGame(Game_Manager* gm_, Player* player_){return false;};

	const char* GetName(){return name.c_str();};
	int GetId(){return id;};
	int GetLevel(){return level;};
	int GetPercent(){return percent;};
	Ability_Type GetType(){return type;}
	virtual const char* GetInfor(){return "존재하지 않는 능력";};
	virtual float GetUseBullet(){return 0;};


	int Possible(Player* player_); //리턴하는 값이 바로 다음 레벨

	void SetId(int id_){id = id_;};
	void SetLevel(int level_){level = level_;};
};

#endif // __ABILITY_H__