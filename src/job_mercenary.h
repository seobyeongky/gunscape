//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job_mercenary.h
//
// 내용: 직업 - 용병
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_MERCENARY_H__
#define  __JOB_MERCENARY_H__

#include "job.h"


class Job_Mercenary: public Job_base
{
public:	
	Job_Mercenary();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_DESERTER_H__

