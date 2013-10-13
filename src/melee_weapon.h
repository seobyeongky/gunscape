//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: melee_weapon.h
//
// ����: ���� ���� Ŭ����
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
	float speed_apply; //��������� �����ϴ� �̵��ӵ��� ����
	float equip_speed;//���ӵ�
	float burst_speed_apply; //����ӵ� ����(������� ����ȵɼ�������)
	float damage_apply; //������ ����(������� ����ȵɼ�������)
	float distance; //��Ÿ�
	float power; //���� ��ġ������
	float max_power; //���� ��ġ�� �ְ�ġ
	//--�Ʒ��� ����Ÿ�Կ� ���� �޶���
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
	int burst_speed;//���� �߻簣��
	float damage; //������
	float equip_speed;//���ӵ�
	float distance; //��Ÿ�
	float distance_static; //��Ÿ� ó��ġ
	float width; //������ �ʺ� ����ġ

	float speed_apply; //��������� �����ϴ� �̵��ӵ��� ����
	float burst_speed_apply; //����ӵ� ����
	float damage_apply; //������ ����
	float power; //���� ��ġ������
	float max_power; //���� ��ġ�� �ְ�ġ

	float back_stab; //�齺�ǵ�����(0�϶� ����. 0���� Ŀ���� �齺�ǰ���. ��ġ��ŭ ������ ��������)
	float back_stab_static;

	float whirlwind_panalty; //������ �г�Ƽ (0�� ������ �Ұ� 1�� ���� 1���ʹ� �ش��ġ��ŭ ���� ����)
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