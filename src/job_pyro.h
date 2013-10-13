//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_pyro.h
//
// ����: ���� - ��ȭ��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_PYRO_H__
#define  __JOB_PYRO_H__

#include "job.h"


class Job_pyro: public Job_base
{
public:	
	Job_pyro();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_PYRO_H__

