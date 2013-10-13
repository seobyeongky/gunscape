//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: main_weapon.h
//
// 내용: 메인웨폰 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MAIN_WEAPON_H__
#define  __MAIN_WEAPON_H__

#include "item.h"



enum WEAPON_TYPE
{
	WT_PISTOL = 0,
	WT_RIFLE,
	WT_SHOTGUN,
	WT_BAZOOKA,
	WT_FLAME_THROWER,
	WT_ECT,
	WT_SILENCE,
	WT_MAX
};
enum Main_Weapon_Kind
{
	MWK_NONE=-1,
	MWK_ASSAUL_RIFLE,
	MWK_HEAVY,
	MWK_RIFLE_PISTOL,
	MWK_RIFLE_PISTOL_BIG,
	MWK_RIFLE_ASSASSIN_PISTOL,
	MWK_RIFLE_DOUBLE_PISTOL,
	MWK_SHOT_GUN,
	MWK_SHOT_GUN_SHORT,
	MWK_SHOT_GUN_KNOCKBACK,
	MWK_FLAME_THROWER,
	MWK_ICE_THROWER,
	MWK_FLAME_THROWER2,
	MWK_BAZOOKA,
	MWK_AP_BAZOOKA,
	MWK_GUIDED_BAZOOKA,
	MWK_GRENADE_GUN,
	MWK_SNIPER,
	MWK_BOW,
	MWK_CROSS_BOW,
	MWK_DART,
	MWK_MAX,
	MWK_MON_ASSAUL_RIFLE,//여기서부터 몬스터용
	MWK_MON_PISTOL,//여기서부터 몬스터용
	MWK_MON_SILENCE_GUN,
	MWK_MON_BAZOOKA,
	MWK_MON_WATER_GUN,
	MWK_MON_BOUNCE_FIRE,
	MWK_MON_SNIPER,
	MWK_MON_ROBOT_MINIGUN,
	MWK_MON_ROBOT_BAZOOKA,
	MWK_MON_ROBOT_GRENADE,
	MWK_NO_WEAPON
};


typedef struct main_weapon_infor
{
	Main_Weapon_Kind weapon_kind;
	Texture* texture;
	Texture* equip_texture;
	WEAPON_TYPE type;
	const char* name;
	const char* infor;
	float max_bullet; //능력에서 퍼센티지 적용을 위해서 float형으로 했다.
	float speed_apply; //들고있을때 감소하는 이동속도의 비율
	float reload_speed;//장전속도
	float equip_speed;//장비속도
	float burst_speed_apply; //연사속도 비율(무기따라서 적용안될수도있음)
	float shot_speed_apply; //탄환속도 비율(무기따라서 적용안될수도있음)
	float damage_apply; //데미지 비율(무기따라서 적용안될수도있음)
	float focus_base; //기준 초점(서있을때)
	float focus_react; //쏘는 반동
	float focus_max_react; //최대 반동
	float focus_calm; //반동줄어드는 속도
	float distance; //사거리
	float noise; //소음
	float power; //적을 밀치는정도
	float max_power; //적을 밀치는 최고치
	//--아래는 무기타입에 따라 달라짐
	int burst_speed;
	int burst_speed_init;
	int shot_speed;
	float damage;
	float bonus_damage; //바주카는 유도정도
	int bunch; //한번에 나가는 총알양
	float size_var;//사이즈변화량? 라이플은 슬로우, 화염은 크기 커지는 비율, 바주카는 폭발 범위, 발사화방은 화염지속시간
	int bonus_int;//라이플은 이속감소시간 바주카는 유도범위
}main_weapon_infor;


class Main_Weapon: public Item
{
	Main_Weapon_Kind weapon_kind;
	Texture* equip_texture;
	WEAPON_TYPE type;
	int bullet;
	float max_bullet; //능력에서 퍼센티지 적용을 위해서 float형으로 했다.
	float max_bullet_static; //원래 최대탄창
	float speed_apply; //들고있을때 감소하는 이동속도의 비율
	float reload_speed;//장전속도
	float equip_speed;//장비속도
	float burst_speed_apply; //연사속도 비율(무기따라서 적용안될수도있음)
	float shot_speed_apply; //탄환속도 비율(무기따라서 적용안될수도있음)
	float damage_apply; //데미지 비율(무기따라서 적용안될수도있음)
	float focus_base; //기준 초점(서있을때)
	float focus_react; //쏘는 반동
	float focus_max_react; //최대 반동
	float focus_calm; //반동줄어드는 속도
	float distance; //사거리
	float noise; //소음
	float power; //적을 밀치는정도
	float max_power; //적을 밀치는 최고치


public:


	Main_Weapon(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Main_Weapon();

	virtual bool InterfaceDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InterfaceNameDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InforDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InforNameDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool DetailInforDraw(Direct_Manager* direct_, coord_def offset_);
	

	//설명 제작용도의 함수
	virtual const char* GetTypeStr();
	virtual const char* GetDamage(){return "없음";};
	virtual const char* GetAtkSpeed(){return "없음";};
	virtual const char* GetBulletStr();
	virtual const char* GetSpeedApplyStr();
	virtual const char* GetSniperStr(){return NULL;};
	//끝
	
	Texture* GetEquipTexture(){return equip_texture;};
	Main_Weapon_Kind GetWeaponKind(){return weapon_kind;};
	int GetBullet(){return bullet;};
	float GetMaxBullet(){return max_bullet;};
	float GetSpeedApply(){return speed_apply;};
	float GetReloadSpeed(){return reload_speed;};
	float GetEquipSpeed(){return equip_speed;};
	float GetBurstSpeedApply(){return burst_speed_apply;};
	float GetShotSpeedApply(){return shot_speed_apply;};
	float GetDamegeApply(){return damage_apply;};
	float GetFocusBase(){return focus_base;};
	float GetFocusReact(){return focus_react;};
	float GetFocusMaxReact(){return focus_max_react;};
	float GetFocusCalm(){return focus_calm;};
	float GetDistance(){return distance;};
	float GetNoise(){return noise;};
	float GetPower(){return power;};
	float GetMaxPower(){return max_power;};
	virtual float GetSniper(){return 0;};

		
	
	void SetFocusBase(float focus_base_){focus_base = focus_base_;}
	void SetBullet(int bullet_){bullet = bullet_;}
	void SetMaxBullet(float bullet_){max_bullet = bullet_;}


	int UseBullet(int Decre_)
	{
		if(bullet<Decre_)
		{
			int temp = bullet;
			bullet = 0;
			return temp;
		}
		bullet-=Decre_;
		return Decre_;
	}
	void ApplyMaxBullet(float ratio_){max_bullet*=ratio_;}
	void ApplySpeedApply(float ratio_){speed_apply*=ratio_;}
	void ApplyReloadSpeed(float ratio_){reload_speed*=ratio_;}
	void ApplyEquipSpeed(float ratio_){equip_speed*=ratio_;}
	void ApplyBurstSpeedApply(float ratio_){burst_speed_apply*=ratio_;};
	void ApplyShotSpeedApply(float ratio_){shot_speed_apply*=ratio_;};
	void ApplyDamegeApply(float ratio_){damage_apply*=ratio_;};
	void ApplyFocusBase(float ratio_){focus_base*=ratio_;};
	void ApplyFocusReact(float ratio_){focus_react*=ratio_;};
	void ApplyFocusMaxReact(float ratio_){focus_max_react*=ratio_;};
	void ApplyFocusCalm(float ratio_){focus_calm*=ratio_;};
	void ApplyDistance(float ratio_){distance*=ratio_;};
	void ApplyNoise(float ratio_){noise*=ratio_;};
	void ApplyPower(float ratio_){power*=ratio_;};
	void ApplyMaxPower(float ratio_){max_power*=ratio_;};
	virtual void ApplySniper(float ratio_){return;};

	void UpDownDistance(float value_){distance+=value_;};
	virtual void UpDownBunch(int value_){};

	WEAPON_TYPE GetType(){return type;};
	virtual ITEM_TYPE GetItemType(){return IT_MAIN_WEAPON;};

	virtual bool Effect(Game_Manager* gm_, Player* unit_);
	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)=0; //총을 쏘다. 리턴값이 딜레이가 된다. -1은 리로드 필요.
	virtual float special(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_){return 0;}; //오른쪽 버튼. 특수키
	float Reload(float bullet_ = 1.0f)
	{
		bullet += (int)floor(max_bullet*bullet_+0.5f);
		if(bullet>max_bullet)
			bullet = (int)max_bullet;
		return reload_speed;
	}; //
	virtual void PlayReloadSE();
	
	virtual bool is_Click_Hold(){return true;};
	virtual char* is_Special(){return NULL;};
};


#endif // __MAIN_WEAPON_H__


