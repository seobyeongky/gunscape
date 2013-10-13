//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: item_heal.h
//
// 내용: 힐링아이템
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ITEM_HEAL_H__
#define  __ITEM_HEAL_H__

#include "item.h"


class Item_heal: public Item
{
public:
	Item_heal(coord_def pos_, int time_);
	virtual ~Item_heal();

	virtual bool InterfaceDraw(Direct_Manager* direct_, coord_def offset_){return false;};
	virtual bool InterfaceNameDraw(Direct_Manager* direct_, coord_def offset_){return false;};
	virtual bool InforDraw(Direct_Manager* direct_, coord_def offset_){return false;};
	virtual bool InforNameDraw(Direct_Manager* direct_, coord_def offset_){return false;};

	virtual ITEM_TYPE GetItemType(){return IT_INSTANT;};

	virtual bool Effect(Game_Manager* gm_, Player* unit_);
	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_){return false;};

	virtual bool Equip(){return false;};
	virtual bool UnEquip(){return false;};

	virtual bool is_Click_Hold(){return false;};

};

#endif // __ITEM_HEAL_H__


