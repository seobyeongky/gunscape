//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: melee_weapon.h
//
// 내용: 근접 무기 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MELEE_WEAPON_H__
#define  __MELEE_WEAPON_H__

#include "item.h"


enum Melee_Kind
{
	MK_NONE=-1,
	MK_KNIFE,
	MK_CLUB,
	MK_AXE,
	MK_SPEAR,
	MK_HAMMER,
	MK_ASSASIN_KNIFE,
	MK_MAX
};


typedef struct melee_weapon_infor
{
	Melee_Kind weapon_kind;
	Texture* texture;
	Texture* equip_texture;
	Texture* effect_texture;
	const char* name;
	const char* infor;
	float speed_apply; //들고있을때 감소하는 이동속도의 비율
	float equip_speed;//장비속도
	float burst_speed_apply; //연사속도 비율(무기따라서 적용안될수도있음)
	float damage_apply; //데미지 비율(무기따라서 적용안될수도있음)
	float distance; //사거리
	float power; //적을 밀치는정도
	float max_power; //적을 밀치는 최고치
	//--아래는 무기타입에 따라 달라짐
	int burst_speed;
	float damage;
	float width;
	float back_stab;
	float whirlwind_panalty;
}melee_weapon_infor;



class Melee_Weapon: public Item
{	
protected:
	Melee_Kind weapon_kind;
	Texture* equip_texture;
	Texture* effect_texture;
	int burst_speed;//총의 발사간격
	float damage; //데미지
	float equip_speed;//장비속도
	float distance; //사거리
	float distance_static; //사거리 처음치
	float width; //범위의 너비 각도치

	float speed_apply; //들고있을때 감소하는 이동속도의 비율
	float burst_speed_apply; //연사속도 비율
	float damage_apply; //데미지 비율
	float power; //적을 밀치는정도
	float max_power; //적을 밀치는 최고치

	float back_stab; //백스탭데미지(0일땐 없음. 0보다 커지면 백스탭가능. 수치만큼 데미지 비율증가)
	float back_stab_static;

	float whirlwind_panalty; //휠윈드 패널티 (0은 휠윈드 불가 1은 없음 1부터는 해당수치만큼 공속 감소)
public:
	Melee_Weapon(const melee_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Melee_Weapon();


	virtual bool InterfaceDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InterfaceNameDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InforDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InforNameDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool DetailInforDraw(Direct_Manager* direct_, coord_def offset_);
	
	virtual const char* GetDamage();
	virtual const char* GetAtkSpeed();
	virtual const char* GetRangeStr();
	virtual const char* GetSpeedApplyStr();
	virtual const char* GetBackstabStr();
	const char* GetWWPannaltyStr();



	Melee_Kind GetWeaponKind(){return weapon_kind;};

	float GetSpeedApply(){return speed_apply;};
	float GetEquipSpeed(){return equip_speed;};
	float GetBurstSpeedApply(){return burst_speed_apply;};
	float GetDamegeApply(){return damage_apply;};
	float GetDistance(){return distance;};
	float GetWidth(){return width;};
	float GetPower(){return power;};
	float GetMaxPower(){return max_power;};
	float GetBackStab(){return back_stab;};
	virtual int GetBackStabDamage(Unit* User_);
	float GetWWPannalty(){return whirlwind_panalty;};

	void SetBackStab(float back_stab_){back_stab = back_stab_;};

	
	void ApplySpeedApply(float ratio_){speed_apply*=ratio_;}
	void ApplyEquipSpeed(float ratio_){equip_speed*=ratio_;}
	void ApplyBurstSpeedApply(float ratio_){burst_speed_apply*=ratio_;};
	void ApplyDamegeApply(float ratio_){damage_apply*=ratio_;};
	void ApplyDistance(float ratio_){distance*=ratio_;};
	void ApplyWidth(float ratio_){width*=ratio_;};
	void ApplyPower(float ratio_){power*=ratio_;};
	void ApplyMaxPower(float ratio_){max_power*=ratio_;};
	void ApplyBackStab(float ratio_){back_stab*=ratio_;};
	void ApplyWWPannalty(float ratio_){whirlwind_panalty*=ratio_;};

	void UpDownBackStab(float updown_){back_stab+=updown_;};


	virtual ITEM_TYPE GetItemType(){return IT_MELEE;};

	virtual bool Effect(Game_Manager* gm_, Player* unit_);
	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);

	virtual bool is_Click_Hold(){return true;};
};

#endif // __MELEE_WEAPON_H__