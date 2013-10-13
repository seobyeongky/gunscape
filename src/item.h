//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: item.h
//
// 내용: 아이템 정리(바닥에 떨어져있는것이 중심)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ITEM_H__
#define  __ITEM_H__

#include "coord_def.h"
#include <d3dx9.h>

class Texture;
class Game_Manager;
class Direct_Manager;
class Unit;
class Player;

enum ITEM_TYPE
{
	IT_MAIN_WEAPON = 0,
	IT_SUB_WEAPON,
	IT_MELEE,
	IT_INSTANT,
	IT_DOOR,
	IT_MAX
};

enum Instant_Kind
{
	IK_NONE=-1,
	IK_HEAL,
	IK_BULLET,
	IK_MAX
};

class Item
{
protected:
	Texture* texture;
	const char* name;
	const char* infor;
	coord_def pos;
	int time;
	bool valid;


public:
	static char temp_str[32];

	Item(Texture* texture_, const char* name_, const char* infor_, coord_def pos_, int time_);
	virtual ~Item();
	
	bool Draw(coord_def offset, float size_);
	virtual bool InterfaceDraw(Direct_Manager* direct_, coord_def offset_)=0;
	virtual bool InterfaceNameDraw(Direct_Manager* direct_, coord_def offset_)=0;
	virtual bool InforDraw(Direct_Manager* direct_, coord_def offset_)=0;
	virtual bool InforNameDraw(Direct_Manager* direct_, coord_def offset_)=0;
	virtual bool DetailInforDraw(Direct_Manager* direct_, coord_def offset_){return true;};
	virtual bool Action(Game_Manager* gm_);

	const char* GetName(){return name;};
	const char* GetInfor(){return infor;};
	coord_def GetPos(){return pos;};
	float GetX(){return pos.x;};
	float GetY(){return pos.y;};
	virtual int GetBackStabDamage(Unit* User_){return 0;};

	void SetPos(const coord_def& pos_){pos = pos_;};

	virtual ITEM_TYPE GetItemType() = 0;
	bool isValid(){ return valid;};


	virtual bool Effect(Game_Manager* gm_, Player* unit_) = 0;
	void Erase(){ valid= false;};
	virtual void Passive(Game_Manager* gm_, Player* unit_, bool current_){};

	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)=0;
	virtual float special(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_){return 0;};

	virtual bool is_Click_Hold() = 0;
	
	virtual bool is_On(){return false;};
};


#endif // __ITEM_H__

