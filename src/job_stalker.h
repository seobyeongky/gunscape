//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_stalker.h
//
// 내용: 직업 - 추적자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_STALKER_H__
#define  __JOB_STALKER_H__

#include "job.h"


class Job_stalker: public Job_base
{
public:	
	Job_stalker();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_STALKER_H__

