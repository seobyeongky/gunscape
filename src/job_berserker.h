//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_berserker.h
//
// 내용: 직업 - 광전사
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_BERSERKER_H__
#define  __JOB_BERSERKER_H__

#include "job.h"


class Job_berserker: public Job_base
{
public:	
	Job_berserker();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_BERSERKER_H__






