//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_.cpp
//
// ����: ��
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_tool.h"

Abil_::Abil_(int level_):
Ability("�̸�", level_,/*�ִ뷹��*/1, /*Ȯ��*/100, /*�ʿ䷹��*/1, /*�ɷ�����*/AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
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
	return "���� ����";
}