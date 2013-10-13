//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: job.h
//
// 내용: 직업만들기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __JOB_H__
#define  __JOB_H__

#include <string>
using namespace std;

class Player;
class Game_Manager;

class Job_base
{
	string name;
public:	
	Job_base(string name_):name(name_){};
	virtual ~Job_base(){};

	virtual void SetPlayer(Game_Manager* gm_, Player* unit)=0;
	const char* GetName(){return name.c_str();};
	virtual const char* GetInfor()=0;
	virtual const char* GetItemInfor()=0;
	virtual const char* GetAblityInfor()=0;
	virtual const char* GetTip()=0;
};



#endif // __JOB_H__






