//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: portal.h
//
// 내용: 포탈!!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __PORTAL_H__
#define  __PORTAL_H__

#include "item.h"

class Portal: public Item
{
	bool last;
public:	
	Portal(Texture* texture_, coord_def pos_, bool last_);

	virtual bool InterfaceDraw(Direct_Manager* direct_, coord_def offset_){return false;};
	virtual bool InterfaceNameDraw(Direct_Manager* direct_, coord_def offset_){return false;};
	virtual bool InforDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool InforNameDraw(Direct_Manager* direct_, coord_def offset_);
	virtual bool Action(Game_Manager* gm_);

	virtual ITEM_TYPE GetItemType(){return IT_DOOR;};

	virtual bool Effect(Game_Manager* gm_, Player* unit_);

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_){return 0;};

	virtual bool is_Click_Hold(){return false;};
};

#endif // __PORTAL_H__