//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_deserter.h
//
// 내용: 직업 - 탈영병
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_DESERTER_H__
#define  __JOB_DESERTER_H__

#include "job.h"


class Job_deserter: public Job_base
{
public:	
	Job_deserter();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_DESERTER_H__

