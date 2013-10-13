//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_politician.h
//
// ����: ���� - ��ġ��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_POLITICIAN_H__
#define  __JOB_POLITICIAN_H__

#include "job.h"


class Job_politician: public Job_base
{
public:	
	Job_politician();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_POLITICIAN_H__

