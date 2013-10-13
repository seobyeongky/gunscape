//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_hunter.h
//
// 내용: 직업 - 사냥꾼
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_HUNTER_H__
#define  __JOB_HUNTER_H__

#include "job.h"


class Job_hunter: public Job_base
{
public:	
	Job_hunter();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_HUNTER_H__

