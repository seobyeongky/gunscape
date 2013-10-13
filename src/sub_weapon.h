//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sub_weapon.h
//
// 내용: 서브웨폰 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SUB_WEAPON_H__
#define  __SUB_WEAPON_H__

#include "item.h"

enum Sub_Weapon_Kind
{
	SWK_NONE=-1,
	SWK_GRENADE,
	SWK_KEVLAR,
	SWK_NET,
	SWK_SMOKE_BOMB,
	SWK_CLOAK,
	SWK_RUNNING_SHOES,
	SWK_BARRICADE,
	SWK_SHIELD,
	SWK_THROW_KNIFE,
	SWK_BULLET_PACK,
	SWK_FIRE_CLOTH,
	SWK_ADRENALIN,
	SWK_SILENCER,
	SWK_TRAP,
	SWK_MAX
};

class Sub_Weapon: public Item
{
	Player* user;
	Texture* equip_texture;
	int num;
	float equip_speed;//장비속도
	bool equip;
	bool Used;

public:
	Sub_Weapon(Texture* texture_, const char* name_, const char* infor_, coord_def pos_, int time_, Player* user_, Texture* equip_texture_,  int num_, float equip_speed_);
	virtual ~Sub_Weapon();

	virtual bool InterfaceDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InterfaceNameDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InforDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InforNameDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool DetailInforDraw(Direct_Manager* direct_, coord_def offset_);
	
	
	virtual const char* GetKindstr();
	virtual const char* GetNumstr();


	virtual ITEM_TYPE GetItemType(){return IT_SUB_WEAPON;};
	Player* GetPlayer(){return user;};
	float GetEquipSpeed(){return equip_speed;};
	bool GetEquip(){return equip;};

	
	void SetEquip(bool equip_){equip = equip_;};

	int UpDownNum(int updown_){num+=updown_;return num;}

	virtual bool Effect(Game_Manager* gm_, Player* unit_);
	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)=0;
	virtual bool is_Click_Hold(){return false;};
	bool isUsed(){return !isEquip();}

	virtual bool Equip() = 0;
	virtual bool UnEquip() = 0;

	
	virtual bool isEquip(){return false;};
};
#endif // __SUB_WEAPON_H__


