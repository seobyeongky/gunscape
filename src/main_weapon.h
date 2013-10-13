//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: main_weapon.h
//
// ����: ���ο��� Ŭ����
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
	MWK_MON_ASSAUL_RIFLE,//���⼭���� ���Ϳ�
	MWK_MON_PISTOL,//���⼭���� ���Ϳ�
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
	float max_bullet; //�ɷ¿��� �ۼ�Ƽ�� ������ ���ؼ� float������ �ߴ�.
	float speed_apply; //��������� �����ϴ� �̵��ӵ��� ����
	float reload_speed;//�����ӵ�
	float equip_speed;//���ӵ�
	float burst_speed_apply; //����ӵ� ����(������� ����ȵɼ�������)
	float shot_speed_apply; //źȯ�ӵ� ����(������� ����ȵɼ�������)
	float damage_apply; //������ ����(������� ����ȵɼ�������)
	float focus_base; //���� ����(��������)
	float focus_react; //��� �ݵ�
	float focus_max_react; //�ִ� �ݵ�
	float focus_calm; //�ݵ��پ��� �ӵ�
	float distance; //��Ÿ�
	float noise; //����
	float power; //���� ��ġ������
	float max_power; //���� ��ġ�� �ְ�ġ
	//--�Ʒ��� ����Ÿ�Կ� ���� �޶���
	int burst_speed;
	int burst_speed_init;
	int shot_speed;
	float damage;
	float bonus_damage; //����ī�� ��������
	int bunch; //�ѹ��� ������ �Ѿ˾�
	float size_var;//�����ȭ��? �������� ���ο�, ȭ���� ũ�� Ŀ���� ����, ����ī�� ���� ����, �߻�ȭ���� ȭ�����ӽð�
	int bonus_int;//�������� �̼Ӱ��ҽð� ����ī�� ��������
}main_weapon_infor;


class Main_Weapon: public Item
{
	Main_Weapon_Kind weapon_kind;
	Texture* equip_texture;
	WEAPON_TYPE type;
	int bullet;
	float max_bullet; //�ɷ¿��� �ۼ�Ƽ�� ������ ���ؼ� float������ �ߴ�.
	float max_bullet_static; //���� �ִ�źâ
	float speed_apply; //��������� �����ϴ� �̵��ӵ��� ����
	float reload_speed;//�����ӵ�
	float equip_speed;//���ӵ�
	float burst_speed_apply; //����ӵ� ����(������� ����ȵɼ�������)
	float shot_speed_apply; //źȯ�ӵ� ����(������� ����ȵɼ�������)
	float damage_apply; //������ ����(������� ����ȵɼ�������)
	float focus_base; //���� ����(��������)
	float focus_react; //��� �ݵ�
	float focus_max_react; //�ִ� �ݵ�
	float focus_calm; //�ݵ��پ��� �ӵ�
	float distance; //��Ÿ�
	float noise; //����
	float power; //���� ��ġ������
	float max_power; //���� ��ġ�� �ְ�ġ


public:


	Main_Weapon(const main_weapon_infor& infor_, coord_def pos_, int time_);
	virtual ~Main_Weapon();

	virtual bool InterfaceDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InterfaceNameDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InforDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InforNameDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool DetailInforDraw(Direct_Manager* direct_, coord_def offset_);
	

	//���� ���ۿ뵵�� �Լ�
	virtual const char* GetTypeStr();
	virtual const char* GetDamage(){return "����";};
	virtual const char* GetAtkSpeed(){return "����";};
	virtual const char* GetBulletStr();
	virtual const char* GetSpeedApplyStr();
	virtual const char* GetSniperStr(){return NULL;};
	//��
	
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
	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)=0; //���� ���. ���ϰ��� �����̰� �ȴ�. -1�� ���ε� �ʿ�.
	virtual float special(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_){return 0;}; //������ ��ư. Ư��Ű
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


