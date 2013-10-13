//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: unit.h
//
// 내용: 유닛(적 아군 모두 포함)의 베이스 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __UNIT_H__
#define  __UNIT_H__

#include "coord_def.h"
#include "damage.h"
#include "FSM.h"
#include "Shot_base.h"
#include "damage.h"
#include <list>

using namespace std;


enum Speed_kind //슬로우 디버프 종류
{
	SK_NONE,
	SK_KILL_STAMINA,
	SK_ICE,
	SK_GUN,
	SK_ANTI_ZOMBIE,
	SK_TRAP,
	SK_BERSERKER,
	SK_MAX
};
enum Attack_buff_kind //공격 버프 종류(공속 버프도 귀찮으니까 이걸로 쓴다.)
{
	ABK_NONE,
	ABK_PORTAL,
	ABK_ADRENALIN,
	ABK_STACK_OK,
	ABK_HACK_SLASH,
	ABK_MAX
};

struct speed_apply
{
	float ratio;
	int turn;
	Speed_kind kind;
	speed_apply(float ratio_, int turn_, Speed_kind kind_):ratio(ratio_),turn(turn_),kind(kind_)
	{}
};
struct attack_apply
{
	float ratio;
	int turn;
	Attack_buff_kind kind;
	attack_apply(float ratio_, int turn_, Attack_buff_kind kind_):ratio(ratio_),turn(turn_),kind(kind_)
	{}
};
struct attack_speed_apply
{
	float ratio;
	int turn;
	Attack_buff_kind kind;
	attack_speed_apply(float ratio_, int turn_, Attack_buff_kind kind_):ratio(ratio_),turn(turn_),kind(kind_)
	{}
};

struct fly_module
{
	coord_def fly_speed;
	coord_def fly_acc;
	int fly_time;
	int fly;
	fly_module():fly_speed(),fly_acc(),fly_time(0),fly(0){};
};

enum Monster_Index
{
	MON_NONE= 0,
	MON_WEAK_ZOMBIE,
	MON_PISTOL_REDNECK,
	MON_BIG_ZOMBIE,
	MON_BUG_WEAK,
	MON_PYRO,
	MON_ZOMBIE_GROUP_1,
	MON_ZOMBIE_GROUP_2,
	MON_ZOMBIE_GROUP_3,
	MON_HUNTER,
	MON_BUG_BOMB,
	MON_BUG_FLY,
	MON_ZOMBIE_VIRUS,
	MON_ROCKET_MAN,
	MON_BLUE_MAN,
	MON_ZOMBIE_BOOMER,
	MON_ZOMBIE_GHOST,
	MON_ZOMBIE_STONE,
	MON_SF_MAN,
	MON_WATER_MAN,
	MON_SPY,
	MON_PYRO2,
	MON_ALERT_ROBOT,
	MON_BUG_FLY2,
	MON_BUG_CHILD_FLY,
	MON_BUG_FIRE_MOTH,
	MON_BUG_ANT_LION,
	MON_BUG_BEETLE,
	MON_ZOMBIE_SMALL,
	MON_ZOMBIE_NOISE,
	MON_STALKER,
	MON_SPIDER,
	MON_SPIDER_BABY,
	MON_BUG_FLING,
	MON_MONSTER_MAX,
	NAMED_START = MON_MONSTER_MAX,
	NAMED_JACK = NAMED_START,
	NAMED_LOOTER,
	NAMED_ROBOT,
	NAMED_DRILL,
	NAMED_FLY_BOSS,
	NAMED_ASSASIN,
	NAMED_SNIPER,
	NAMED_VIRUS,
	NAMED_BERSERKER,
	NAMED_SCREAM,
	NAMED_MAX,	
	MON_MAX	
};






class Game_Manager;
class Texture;
class Map;
class Main_Weapon;
class Ai_Manager;
class Player;
class Monster;

class Unit
{
	string name;
	Texture* texture;
	coord_def pos;
	float angle;
	float move_angle;
	float size;
	int team;
	int frame;

	int hp;
	int max_hp;
	float sight;
	float sight_width;//시야 너비
	int delay;
	int max_delay;//현재 딜레이의 전 최대치(?)
	float focus; //에임
	float speed;
	
	int invisible_temp; //두개이상의 투명값이 섞여서 이상해지는걸 방지하기위함. 매 프레임마다 갱신. -1이 비갱신상태에 높은 수치를 받아들인다.
	unsigned char invisible; //투명이다. 0은 불투명. 1부턴 투명(수치는 단순히 알파값 마이너스임)
	int none_move_count; //움직이지않은 카운트

	int slow;
	int bsk_slow;
	float atk_apply;
	float atk_spd_apply;
	float defense[DT_MAX];
	bool def_resist[DT_MAX]; //이게 true면 아예 면역이 된다.
	float vamp[VT_MAX-1][DT_MAX-1];
	float sneak[VT_MAX-1];
	float back_panalty;
	int net;
	float melee_knock_back; //근접 넉백
	int blind; //시야감소 상태(시야절반의 감소)
	bool fog_resist;
	int stop; //이동과 공격을 잠시 정지
	int angle_stop; //각도를 고정
	bool fixed; //바닥에 고정되어있는지
	bool immortal; //불사의분노!
	int warning; //주의경보(1000이 되면 시야에 있는 투명도 감지한다.)
	int fog_slow;
	int house_in;//방음장치가 있는 집안에선 바깥도 안보이고 소음도 안들린다.
	int invincible;//무적
	int shot_stop;
	float poison_damage;
	int poison_turn;
	Unit* poison_unit;

	float x_speed;
	float y_speed;

	
	int x_slip;	
	int y_slip;

	int slip_count;
	
	int detection_player[8]; //인덱스는 (플레이어의 팀 - 1)이 됨. 애초에 넷플레이는 최대 8인플로
	
	list<speed_apply> speed_list;
	list<attack_apply> attack_list;
	list<attack_speed_apply> attack_speed_list;

	fly_module fly;
	
public:
	Unit();
	Unit(string name_, Texture* texture_, float x_, float y_, int team_, int max_hp_);
	virtual ~Unit();

	virtual void SetAi(monster_state state_, Unit* head_ = NULL, int level_ = 0){};
	virtual void SetWeapon(Main_Weapon* weapon_){};
	virtual void SetWeapon(Main_Weapon* second_weapon_, Main_Weapon* third_weapon_){};
	virtual void PlusFlag(int flag_){}

	virtual bool charDraw(Game_Manager* gm_, coord_def offset, float size_);
	virtual bool Draw(Game_Manager* gm_, coord_def offset, float size_); //(이거 상속은 받지말자. 드릴벌레만 예외임. 갠 유닛이 아님)
	bool NameDraw(Game_Manager* gm_, coord_def offset, float size_);
	virtual  bool Action(Game_Manager* gm_); //겉을 감싼다. (이거 상속은 받지말자. 드릴벌레만 예외임. 갠 유닛이 아님)
	virtual bool Action_in(Game_Manager* gm_)=0; //안이다.
	void CommonAction(Game_Manager* gm_);
	virtual void Death(Game_Manager* gm_); //데미지로 죽을 경우.

	void InitNoneMoveCount(){none_move_count = 0;};
	
	virtual Monster_Index Getindex(){return MON_NONE;};
	const char* GetName(){return name.c_str();};
	Texture* GetTexture(){return texture;};
	float GetX(){return pos.x;};
	float GetY(){return pos.y;};
	coord_def GetPos(){return pos;};
	float GetSize(){return size;};	
	float GetFlySize();
	float GetAngle(){return angle;};
	float GetMoveAngle(){return move_angle;};
	virtual bool GetSearchAngle(float& angle_){return false;};
	float GetDefense(Damage_Type type_){return defense[type_];};
	float GetDefResist(Damage_Type type_){return def_resist[type_];};
	float GetVamp(Vamp_Type type_, Damage_Type type2_){if(!type_ || !type2_) return 0.0f; return vamp[type_-1][type2_-1];};
	float GetSneak(Vamp_Type type_){if(!type_) return 1.0f; return sneak[type_-1];};
	int GetTeam(){return team;};
	int GetFrame(){return frame;};
	int GetHp(){return hp;};
	int GetMaxHp(){return max_hp;};
	int GetFly(){return fly.fly;};
	float GetView(){return sight*((!fog_resist && blind>0)?0.5f:1);};
	float GetSight(){return sight;};
	float GetSightWidth(){return sight_width;};
	float GetSightPenalty(Unit* enemy);
	int GetDelay(){return delay;};
	int GetMaxDelay(){return max_delay;};
	virtual float GetFocusSum();
	float GetFocus(){return focus;};
	float GetSpeed(float angle_);
	virtual float GetPlayerSpeed(float angle_){return 1.0f;};
	float GetSpeed_Pure(){return speed;};
	int GetInvisible(){return invisible;};
	int GetAlpha(Game_Manager* gm_); //눈에 보이는 투명도
	int GetNoneMoveCount(){return none_move_count;};
	int GetSlow(){return slow;};
	int GetBskSlow(){return bsk_slow;};
	float GetAtkApply();
	float GetAtkSpdApply();
	int GetNet(){return net;};
	bool GetFogResist(){return fog_resist;};
	int GetStop(){return stop;};
	int GetAngleStop(){return angle_stop;};
	virtual monster_state GetState(){return MS_SEARCH;};
	virtual Vamp_Type GetKind(){return VT_ETC;};
	int GetWarning(){return warning;}
	int GetFogslow(){return fog_slow;}
	int GetHouseIn(){return house_in;}
	int GetInvincible(){return invincible;}
	int GetShotStop(){return shot_stop;}
	virtual int GetForgetCount(){return 300;};
	virtual int GetWarningTime(){return 1000;};
	virtual Ai_Manager* GetAi(){return NULL;};
	virtual float GetMirrorDamage(){return 0.0f;};
	virtual float GetMirrorKnockback(){return 0.0f;};
	virtual bool GetSniper(){return false;};
	virtual int GetCritical(){return 0;};
	virtual float GetSearchRate(){return 1.0f;};
	virtual float GetSilencer(){return 1.0f;};


	virtual void SetAngle(float angle_){if(!angle_stop)angle = angle_;};
	virtual void SetFlyAngle(float angle_){};
	void SetMoveAngle(float angle_){if(!angle_stop)move_angle = angle_;};
	void SetName(const char* name_){name = name_;};
	void SetHp(int hp_){hp = hp_;};
	void SetSize(float size_){size = size_;};
	virtual int SetDamage(Game_Manager* gm_, coord_def c, Damage_Type type_, float damage_, int team_, float sniper_ = 1.0f, int critical_ = 0);
	virtual void GiveDamage(Game_Manager* gm_, Unit* unit_, Damage_Type type_, int damage_);
	virtual void SetNoise(Game_Manager* gm_, int team_, coord_def pos_){};
	void SetKnockback(float power_, float max_power_, float angle_);
	void SetSight(float sight_){sight = sight_;};
	int SetDelay(float delay_);
	float SetFocus(float focus_){focus = focus_;return focus;};
	float SetSpeed(float speed_){speed = speed_;return speed;};
	int SetSlow(int slow_){slow = slow_;return slow;};
	int SetBskSlow(int bsk_slow_){bsk_slow = bsk_slow_;return bsk_slow;};
	bool SetDefResist(Damage_Type type_, bool value_){def_resist[type_] = value_;return value_;};
	float SetBackPanalty(float back_panalty_){back_panalty = back_panalty_;return back_panalty;};
	void SetInvisible(int invisible_); //투명값 자체를 바로 바꾸지않는다. 이는 두가지 이상의 요인으로 투명값이 뒤섞임을 방지하기 위함
	int SetNet(int net_){net = net_;return net;};
	void SetStop(int stop_){stop = stop_;};
	void SetAngleStop(int stop_){angle_stop = stop_;};
	void SetFixed(bool fixed_){fixed = fixed_;}
	void SetImmortal(bool immortal_){immortal = immortal_;}
	void SetFogslow(int fog_slow_){fog_slow=fog_slow_;};
	void SetHouseIn(int house_in_){house_in=house_in_;};
	void SetInvincible(int invincible_){invincible = invincible_;}
	void SetShotStop(int shot_stop_){shot_stop = shot_stop_;}
	virtual void SetStaminaDelay(int delay_){};
	virtual void SetSpeedDelay(int delay_){};
	void SetMeleeKnockBack(float melee_knock_back_){melee_knock_back = melee_knock_back_;};
	void SetBlind(int blind_){blind = max(blind,blind_);};
	void SeFogResist(bool resist_){fog_resist = resist_;};	
	virtual void SetPoison(float damage_, int turn_, Unit* unit_){poison_damage=damage_;poison_turn=turn_;poison_unit=unit_;};
	virtual void SetSniper(bool sniper_){};
	virtual void SetItemDrop(bool drop_){};
	
	void ApplySneak(Vamp_Type type_, float ratio_);
	void ApplyDefense(Damage_Type type_, float ratio_);
	void ApplySpeed(float ratio_){speed*=ratio_;};
	void ApplyBackPanalty(float ratio_){back_panalty*=ratio_;};
	void ApplyMeleeKnockBack(float ratio_){melee_knock_back*=ratio_;};
	void ApplyAtk(float ratio_){atk_apply*=ratio_;};
	void ApplyAtkSpd(float ratio_){atk_spd_apply*=ratio_;};

	void UpDownVamp(Vamp_Type type_, Damage_Type type2_, float updown_);
	void UpDownAngle(float angle_){angle+=angle_;};
	void UpDownMaxHp(int updown_){max_hp+=updown_;};
	void UpDownHp(int updown_){hp+=updown_;};
	void UpDownDelay(int updown_){delay+=updown_;};
	void UpDownSight(float updown_){sight+=updown_;};
	void UpDownFocus(float focus_){focus+=focus_;};
	void UpDownSlow(int slow_){slow+=slow_;};
	void UpDownBskSlow(int bsk_slow_){bsk_slow+=bsk_slow_;};
	void UpDownWarning(int warning_){warning+=warning_;if(warning<0)warning=0;};

	void Insight(Game_Manager* gm_, Player* player_, bool speed_); //투명몬스터를 볼수있는 시야에 들었다. speed는 빠른 탐지


	void SlowApply(float ratio_, int turn_, Speed_kind kind_);
	void AttackApply(float ratio_, int turn_, Attack_buff_kind kind_);
	void AttackSpeedApply(float ratio_, int turn_, Attack_buff_kind kind_);
	virtual void StateApply(const char* name_, int turn_){};
	void Heal(int updown_)
	{
		if(updown_<0) return;
		hp+=updown_;
		if((int)max_hp<hp)
			hp = (int)max_hp;
	};
	virtual void SuppleBullet(float updown_){return;};
	bool isLive(){return hp>0;};
	virtual bool isNonTarget(){return false;};
	virtual bool isCollution(){if(fly.fly)return false;return true;}; //충돌이 가능한지
	virtual bool isTargeting(){return true;}; //타겟팅(인공지능용)이 필요한 녀석인지
	virtual bool isPlayer() = 0;
	virtual bool isThrowable(){return true;};
	virtual bool isNamed(){return false;};	
	virtual bool isNonLife(){return false;};
	virtual bool isBackStabbing(){return false;}; //백스텝을 당할지 말지
	virtual bool isSleep(){return false;}; 
	virtual bool isItemOk(){return true;}; 
	virtual bool isTrueShot(){return false;}; //벽건너 공격을 할지 안할지
	virtual bool isViewName(){return true;}; //이름보이는지 아닌지


	void Move(float x_, float y_); //강제 이동
	virtual int UnitMove(Game_Manager* gm_, float speed_, float angle_); //스피드, 각도를 이용한 충돌확인이동. 0이 비충돌 1,2은 몹이랑 -1은 벽이랑
	virtual int UnitSlipMove(Game_Manager* gm_, float speed_, float angle_); //UnitMove의 미끄러지듯이 이동판. 장애물을 피함.
	//위 함수는 특이하게 이동했을때 0을 리턴해야한다. 1은 충돌됨(대신 몹이랑의 충돌껴있음.) -1은 벽이랑의 충돌
	int isCollutionX(Game_Manager* gm_, float move_); //x축으로 충돌되는지 확인. 0이 비충돌 1,2은 몹이랑 -1은 벽이랑
	int isCollutionY(Game_Manager* gm_, float move_); //y축으로 충돌되는지 확인. 0이 비충돌 1,2은 몹이랑 -1은 벽이랑
	bool collution(coord_def pos_, float radius_);
	void Friction(Game_Manager* gm_); //x_speed와 y_speed에 따른 충돌확인 이동
	bool TargetLost_unit();
	virtual bool TargetLost() = 0;
	virtual bool TargetBlinding() = 0;
	virtual bool InvisibleLost(coord_def c) = 0;
	virtual void Sleep(){return;};
	virtual bool GiveExp(Game_Manager* gm_, int value_){return false;};
	virtual bool KillMonster(Game_Manager* gm_, int team_, Monster* monster_, Damage_Type type_, float damage_, bool back_stab_){return false;};

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0) = 0;

	
	virtual bool Fly(Game_Manager* gm_, coord_def c, int time_);
};



#endif // __UNIT_H__