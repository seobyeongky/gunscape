//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_sniper.h
//
// ����: ���� - ���ݼ�
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_SNIPER_H__
#define  __JOB_SNIPER_H__

#include "job.h"


class Job_sniper: public Job_base
{
public:	
	Job_sniper();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_SNIPER_H__

