//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: obj_barricade.h
//
// 내용: 바리케이트 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __OBJ_BARRICADE_H__
#define  __OBJ_BARRICADE_H__

#include "unit.h"


class Barricade: public Unit
{
	int time;
public:
	Barricade(Texture* texture_, coord_def pos_, int health_, int time_, int team_);
	virtual ~Barricade();

	virtual bool Action_in(Game_Manager* gm_);
	virtual bool isPlayer(){return false;};
	virtual bool isTargeting(){return false;};
	virtual bool isNonLife(){return true;};
	virtual bool TargetLost(){return false;};
	virtual bool TargetBlinding(){return false;};
	virtual bool InvisibleLost(coord_def c){return false;};

	virtual bool Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num = 0){return false;};

	virtual bool DropItem(Game_Manager* gm_);
};


#endif // __OBJ_BARRICADE_H__


