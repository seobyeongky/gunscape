//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_smoke.h
//
// 내용: 연막
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_SMOKE_H__
#define  __SHOT_SMOKE_H__

#include "Shot_base.h"


class Shot_smoke: public Shot_base
{
	int count;
	float range; //범위
	int time;
	bool valid;
	
public:
	Shot_smoke(Texture* texture_, Unit* unit_, float range_, int team_, coord_def pos_, int time_);
	virtual ~Shot_smoke();
	virtual char* GetName(){return "연막탄";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);

};


#endif // __SHOT_VIRUS_H__