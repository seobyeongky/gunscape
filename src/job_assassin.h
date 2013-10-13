//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_assassin.h
//
// 내용: 직업 - 암살자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_ASSASSIN_H__
#define  __JOB_ASSASSIN_H__

#include "job.h"


class Job_assassin: public Job_base
{
public:	
	Job_assassin();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_ASSASSIN_H__

