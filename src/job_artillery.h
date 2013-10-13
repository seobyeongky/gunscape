//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_artillery.h
//
// 내용: 직업 - 포병
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_ARTILLERY_H__
#define  __JOB_ARTILLERY_H__

#include "job.h"


class Job_artillery: public Job_base
{
public:	
	Job_artillery();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_ARTILLERY_H__

