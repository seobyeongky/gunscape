//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_sleep.cpp
//
// ����: źâ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_sleep.h"
#include "player.h"
#include "gamemanager.h"
#include "random.h"


Abil_sleep::Abil_sleep(int level_):
Ability("�㵵��", level_, 5, 50, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_sleep::~Abil_sleep()
{

}


Ability* Abil_sleep::Clone(int level_)
{
	return new Abil_sleep(level_);
}
int Abil_sleep::GetPercent()
{
	switch(level)
	{
	case 1:
		return 15;
	case 2:
		return 30;
	case 3:
		return 45;
	case 4:
		return 60;
	case 5:
		return 80;
	}
	return false;
}



const char* Abil_sleep::GetInfor()
{
	static char temp[128];
	sprintf_s(temp,128,"������ ���� ������ %d%%�� �ο��� �ῡ ���",GetPercent());
	return temp;
}

bool Abil_sleep::EnterMap(Game_Manager* gm_, Player* player_, int level_)
{
	for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
	{
		if(GetPercent()>=rand_int(1,100))
		{
			(*it)->Sleep();
		}
	}
	return true;
}
