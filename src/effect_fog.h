//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: effect_fog.h
//
// ����: ������ ������ �Ȱ��� ����.
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