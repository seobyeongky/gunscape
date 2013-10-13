//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_house.h
//
// 내용: 인간의 마을의 집은 밖에선 안보인다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __EFFECT_HOUSE_H__
#define  __EFFECT_HOUSE_H__

#include "Shot_base.h"


class Effect_house: public Shot_base
{
	float width;
	float height;
	int alpha;

public:
	Effect_house(Texture* texture_, coord_def pos_, float width_, float height_);
	virtual ~Effect_house();
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
	
	virtual bool isHouse(){return true;};

	virtual bool HouseCollution(const coord_def& c);
};


#endif // __EFFECT_HOUSE_H__