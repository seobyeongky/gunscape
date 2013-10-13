//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: Shot_virus.h
//
// ����: ���̷���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __SHOT_VIRUS_H__
#define  __SHOT_VIRUS_H__

#include "Shot_base.h"


class Shot_virus: public Shot_base
{
	int count;
	int frame;
	float damage; //5�����Ӵ� ���� ������?
	float range; //����
	int time;
	bool valid;
	
public:
	Shot_virus(Texture* texture_, Unit* unit_, int frame_, float damage_, float range_, int team_, coord_def pos_, int time_);
	virtual ~Shot_virus();
	virtual char* GetName(){return "���̷���";};
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);
};


#endif // __SHOT_VIRUS_H__