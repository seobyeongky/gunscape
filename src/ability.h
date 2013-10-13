//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: ability.h
//
// ����: �ɷ� Ŭ����
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
	string name; //�̸�
	int id; //������ȣ
	int level; //�� �ɷ��� ����
	int max_level; //�� �ɷ��� �ִ� ����
	int percent; //�� Ȯ���� ���õ� Ȯ��
	int need_level; //�� �ɷ¿� �ʿ��� ����
	Ability_Type type; //�� �ɷ��� Ÿ��
	//�нú�: �ѹ������� ��� ȿ���� �����ϴ� �ɷ�. ���� ����
	//�����: ������ ���¹̳����� �Ҹ��ؼ� ����Ҽ��ִ� �ɷ��� �����. �� 2~3�� �ۿ� ����������
	//�����: ������ ������� ȿ���� ���ֵ�
	
	static int abil_num; //�ɷ� �� ����
	static map<string,Ability*> ability_list;

	Ability(const char* name_, int level_, int max_level_, int percent_, int need_level_, Ability_Type type_);


	vector<abil_level> need_abil; //�ش� ��ų�� ������ �ʿ��� ���
	vector<abil_level> oppose_abil; //�ش� ��ų�� ���� �̻��ΰ�� ���� �Ұ�

public:	
	virtual ~Ability();

	virtual Ability* Clone(int level_)=0;

	static void InitAbility(Game_Manager* gm_);
	static void ReleaseAbility();
	static bool AddAbility(Ability* ability_);
	static bool GetAbility(Player* player_, int num); //���� �÷��̾��� �����Ƽ�� �̹� �������� ����.

	bool Learn(Game_Manager* gm_, Player* player_); //ó�� �ɷ��� �������
	bool UnLearn(Game_Manager* gm_, Player* player_); //�ɷ��� �����ɶ�

	bool Active(Game_Manager* gm_, Player* player_); //�нú� �ɷ��� ���Ǿ�����. �̰� �񰡻��Լ�
	bool UnActive(Game_Manager* gm_, Player* player_); //�нú� �ɷ��� ��ҵȴ�. �̰� �񰡻��Լ�
	bool UseOnOff(Game_Manager* gm_, Player* player_); //���ɷ��� Ű�� ����. �񰡻��Լ�


	virtual bool Action(Game_Manager* gm_, Player* player_){return false;} //�нú�, ���Ŀ��� �� �����ӽ��� �Լ�

	virtual bool InstanceActive(Player* player_){return false;};

	virtual bool isUsing(){return false;}; //���� �ɷ��� ���������?
	virtual bool Use(Game_Manager* gm_, Player* player_){return false;} //����� �ɷ��� ���
	virtual bool UnUse(Game_Manager* gm_, Player* player_){return false;}//����� �ɷ��� ���

	
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
	virtual const char* GetInfor(){return "�������� �ʴ� �ɷ�";};
	virtual float GetUseBullet(){return 0;};


	int Possible(Player* player_); //�����ϴ� ���� �ٷ� ���� ����

	void SetId(int id_){id = id_;};
	void SetLevel(int level_){level = level_;};
};

#endif // __ABILITY_H__