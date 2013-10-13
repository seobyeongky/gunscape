//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: player.h
//
// 내용: 플레이어를 다루는 클래스(네트워크 플레이를 염두에 두고 만들자.)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __PLAYER_H__
#define  __PLAYER_H__

#include<vector>
#include "unit.h"


using namespace std;

class Item;
class Main_Weapon;
class Sub_Weapon;
class Melee_Weapon;
class Ability;


struct state_name
{
	string name;
	int turn;
	int max_turn;
	state_name(const char *name_, int turn_): name(name_), turn(turn_), max_turn(turn_){}
};



class Player: public Unit
{
	coord_def focus_pos;

	int level;
	int exp;
	float stamina;
	float max_stamina;
	int stamina_delay;
	int speed_delay;
	int remain_ability;
	int select_ability_num;
	int ability_select_count;
	int ability_select_num;

	float bullet;
	int max_bullet;

	bool ability_select; //고를 수 있는 능력갯수
	bool quick_select; //퀵메뉴 선택
	int quick_menu; //퀵메뉴
	int portal_time; //포탈을 건너는 시간
	bool state_view;//상태보임
	bool mon_sight_view; //적의 시야가 보임
	bool berserker; //버서커상태!
	int blood_reload;
	int forget_count; //적을 따돌리는 시간
	int warning_time;
	int temp_invisible_turn;
	float mirror_damage;
	float mirror_knockback;
	bool sniper; //스나이퍼모드!
	bool map_hack; //맵핵
	int critical;
	int your_switch;
	float silencer;


	int sub_change;
	int current_weapon_num;
	Item* current_weapon;


	list<state_name> state_list;
public:
	Main_Weapon* main_weapon;
	Sub_Weapon* sub_weapon[2];
	Melee_Weapon* melee_weapon;

	//비무장일때 드는 무기
	
	Main_Weapon* no_weapon;
	Sub_Weapon* no_sub_weapon;
	Melee_Weapon* pist;




	/*Player();*/
	Player(Texture* texture_, float x_, float y_);
	virtual ~Player();


	vector<Ability*> use_abil_list; //이 것은 abil에 있는 능력을 복붙해야하므로 실제로 delete하지않는다.
	vector<Ability*> abil_list;
	vector<Ability*> select_abil_list; //어빌리티에서 사용하자



	coord_def GetFocusPos(){return focus_pos;};
	Item* GetCurrentWeapon(){return current_weapon;};
	Item* GetEmptyWeapon();
	Main_Weapon* GetMainWeapon(){return main_weapon;};
	Sub_Weapon* GetSubWeapon(int i){return sub_weapon[i];};
	Melee_Weapon* GetMeleeWeapon(){return melee_weapon;};
	int GetLevel(){return level;};
	int GetExp(){return exp;};
	float GetStamina(){return stamina;};
	float GetMaxStamina(){return max_stamina;};
	int GetNeedExp(int level_);
	float GetExpPercent();
	int GetSelectAbilityNum(){return select_ability_num;};
	float GetBullet(){return bullet;};
	int GetMaxBullet(){return max_bullet;};
	bool GetAbilitySelect(){return ability_select;};
	bool GetQuickSelect(){return quick_select;};
	int GetPortalTime(){return portal_time;};
	bool GetStateView(){return state_view;};
	bool GetMonSightView(){return mon_sight_view;};
	virtual int GetForgetCount(){return forget_count;};
	virtual int GetWarningTime(){return warning_time;};
	int GetInvisibleturn(){return temp_invisible_turn;};
	virtual float GetMirrorDamage(){return mirror_damage;};
	virtual float GetMirrorKnockback(){return mirror_knockback;};
	bool GetSniper(){return sniper;};
	float GetSniperSight(){return GetSight();};
	bool GetMapHack(){return map_hack;};
	virtual int GetCritical(){return critical;};
	int GetSwitch(){return your_switch;};
	int GetBackStabDamage();
	virtual float GetSilencer(){return silencer;};
	
	
	bool StartAbility();
	void SelectAbilityBefore(int i);
	bool SelectAbility(Game_Manager* gm_, int i);
	bool StartQuickStart();
	bool SetQuickmenu(int i);
	bool GetAbility(Game_Manager* gm_, Ability* abil_);
	bool UseAbility(Game_Manager* gm_, unsigned int i);

	bool Swap(int i);
	
	void SetFocusPos(coord_def focus_pos_){focus_pos = focus_pos_;};
	bool SetMainWeapon(Main_Weapon* main_weapon_);
	int SetSubWeapon(Sub_Weapon* sub_weapon_); //리턴 값은 바꾼 서브웨폰의 인덱스이다
	bool SetMeleeWeapon(Melee_Weapon* melee_weapon_);
	virtual void SetStaminaDelay(int delay_){if(delay_>stamina_delay) stamina_delay = delay_;};
	virtual void SetSpeedDelay(int delay_){if(delay_>speed_delay) speed_delay = delay_;};
	void SetSelectAbilityNum(int select_ability_num_){select_ability_num = select_ability_num_;};
	void SetPortalTime(int portal_time_){portal_time=portal_time_;};
	void SetStateView(bool state_view_){state_view = state_view_;};
	void SetMonSightView(bool mon_sight_view_){mon_sight_view = mon_sight_view_;};
	void SetBerserker(bool berserker_){berserker = berserker_;};
	void SetBloodReload(int blood_reload_){blood_reload = blood_reload_;};
	void SetForgetCount(int forget_count_){forget_count = forget_count_;};
	void SetWarningTime(int warning_time_){warning_time = warning_time_;};
	void SetInvisibleturn(int temp_invisible_turn_){temp_invisible_turn=temp_invisible_turn_;};
	void SetMirrorDamage(float mirror_damage_){mirror_damage = mirror_damage_;};
	void SetMirrorKnockback(float mirror_knockback_){mirror_knockback= mirror_knockback_;};
	void SetSniper(bool sniper_){sniper = sniper_;};
	void SetCritical(int critical_){critical = critical_;};
	void SetSwitch(int your_switch_){your_switch = your_switch_;};
	void SetMapHack(bool map_hack_){map_hack = map_hack_;};
	void SetSilencer(float silencer_){silencer = silencer_;};
	void ApplySilencer(float ratio_){silencer*=ratio_;};

	void UpDownMaxStamina(float updown_){max_stamina+=updown_;};
	void UpDownStamina(float updown_){stamina+=updown_;if(stamina>max_stamina)stamina=max_stamina; };
	void UpDownMaxBullet(int updown_){max_bullet+=updown_;};
	void UpDownCritical(int updown_){critical+=updown_;};
	
	bool UseStamina(float value_);
	virtual void SuppleBullet(float updown_)
	{
		if(updown_<0) return;
		bullet+=updown_;
		if(max_bullet<bullet)
			bullet = (float)max_bullet;
	}

	void DeleteMainWeapon();
	void DeleteSubWeapon(Item* it_, int num);
	void DeleteMeleeWeapon();
	
	virtual bool isPlayer(){return true;};
	
	virtual bool Action_in(Game_Manager* gm_);
	void SelectAction(Game_Manager* gm_);

	virtual float GetFocusSum();
	virtual float GetPlayerSpeed(float angle_);

	
	virtual void StateApply(const char* name_, int turn_);
	virtual bool TargetLost(){return false;};
	virtual bool TargetBlinding(){return false;};
	virtual bool InvisibleLost(coord_def c){return false;};
	virtual bool GiveExp(Game_Manager* gm_, int value_);
	virtual bool KillMonster(Game_Manager* gm_, int team_, Monster* monster_, Damage_Type type_, float damage_, bool back_stab_);
	virtual bool EnterMap(Game_Manager* gm_, int level_);
	bool LevelUp(Game_Manager* gm_);

	bool HpDraw(coord_def offset_);
	bool StaminaDraw(coord_def offset_);
	bool ExpDraw(coord_def offset_);
	bool AbilityUpDraw(Game_Manager* gm_, coord_def offset_);
	bool TestDraw(Game_Manager* gm_, coord_def offset_);
	bool PickUpDraw(Game_Manager* gm_, coord_def offset_);
	bool PickUpNameDraw(Game_Manager* gm_, coord_def offset_);
	bool DetailInforDraw(Game_Manager* gm_, coord_def L_offset_, coord_def R_offset_);
	bool AbilitySelectDraw(Game_Manager* gm_, coord_def offset_);
	bool AbilityDraw(Game_Manager* gm_, coord_def offset_);
	bool QuickMenuDraw(Game_Manager* gm_, coord_def offset_);
	bool UseAbilityDraw(Game_Manager* gm_, coord_def offset_);
	bool StateDraw(Game_Manager* gm_, coord_def offset_);
	bool StateGaugeDraw(Game_Manager* gm_, coord_def offset_);
	bool DelayDraw(coord_def offset_, float size_);
	bool BulletDraw(coord_def offset_);
	bool FogDraw(coord_def offset_, coord_def window_size_);
	bool SniperDraw(coord_def offset_, coord_def window_size_);

	bool PickUp(Game_Manager* gm_);
	bool is_Click_Hold();

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0);
	virtual bool Special(Game_Manager* gm_, coord_def c, float focus_);
	virtual bool Quick(Game_Manager* gm_, coord_def c, float focus_);
	
	bool Reload();

	bool UseBullet(float bullet_);
};

#endif // __PLAYER_H__