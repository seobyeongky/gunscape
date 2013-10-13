//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_archer.h
//
// 내용: 직업 - 궁수(바꾸기)
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_ARCHER_H__
#define  __JOB_ARCHER_H__

#include "job.h"


class Job_archer: public Job_base
{
public:	
	Job_archer();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_ARCHER_H__

