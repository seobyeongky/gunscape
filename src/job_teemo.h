//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: job_teemo.h
//
// ����: ���� - Ƽ��...�ƴ� ������
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_TEEMO_H__
#define  __JOB_TEEMO_H__

#include "job.h"


class Job_teemo: public Job_base
{
public:	
	Job_teemo();

	virtual void SetPlayer(Game_Manager* gm_, Player* unit);
	virtual const char* GetInfor();
	virtual const char* GetItemInfor();
	virtual const char* GetAblityInfor();
	virtual const char* GetTip();
};



#endif // __JOB_TEEMO_H__
