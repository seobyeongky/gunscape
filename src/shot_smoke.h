//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: Shot_smoke.h
//
// ����: ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_SMOKE_H__
#define  __SHOT_SMOKE_H__

#include "Shot_base.h"


class Shot_smoke: public Shot_base
{
	int count;
	float range; //����
	int time;
	bool valid;
	
public:
	Shot_smoke(Texture* texture_, Unit* unit_, float range_, int team_, coord_def pos_, int time_);
	virtual ~Shot_smoke();
	virtual char* GetName(){return "����ź";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);

};


#endif // __SHOT_VIRUS_H__