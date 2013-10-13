//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_fog.h
//
// 내용: 좀비의 마을엔 안개가 낀다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __EFFECT_FOG_H__
#define  __EFFECT_FOG_H__

#include "Shot_base.h"


class Effect_fog: public Shot_base
{
	
public:
	Effect_fog(Texture* texture_);
	virtual ~Effect_fog();
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);

};


#endif // __EFFECT_FOG_H__