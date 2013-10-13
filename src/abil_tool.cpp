//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: abil_.cpp
//
// 내용: 툴
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_tool.h"

Abil_::Abil_(int level_):
Ability("이름", level_,/*최대레벨*/1, /*확률*/100, /*필요레벨*/1, /*능력종류*/AT_PASSIVE)
{
	//필요능력. 반대능력은 여기서 판단하기
}


Abil_::~Abil_()
{

}


Ability* Abil_::Clone(int level_)
{
	return new Abil_(level_);
}


const char* Abil_::GetInfor()
{
	switch(level)
	{
	case 1:
		return "";
	case 2:
		return "";
	case 3:
		return "";
	case 4:
		return "";
	case 5:
		return "";	
	}
	return "레벨 에러";
}