//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_virus.h
//
// 내용: 바이러스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_VIRUS_H__
#define  __SHOT_VIRUS_H__

#include "Shot_base.h"


class Shot_virus: public Shot_base
{
	int count;
	int frame;
	float damage; //5프레임당 들어가는 데미지?
	float range; //범위
	int time;
	bool valid;
	
public:
	Shot_virus(Texture* texture_, Unit* unit_, int frame_, float damage_, float range_, int team_, coord_def pos_, int time_);
	virtual ~Shot_virus();
	virtual char* GetName(){return "바이러스";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
};


#endif // __SHOT_VIRUS_H__