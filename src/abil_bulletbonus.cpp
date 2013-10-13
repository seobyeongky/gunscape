//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: abil_bulletbonus.cpp
//
// ����: źâ���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "abil_bulletbonus.h"
#include "player.h"

Abil_bulletbonus::Abil_bulletbonus(int level_):
Ability("���ں���", level_, 3, 100, 1, AT_PASSIVE)
{
	//�ʿ�ɷ�. �ݴ�ɷ��� ���⼭ �Ǵ��ϱ�
}


Abil_bulletbonus::~Abil_bulletbonus()
{

}


Ability* Abil_bulletbonus::Clone(int level_)
{
	return new Abil_bulletbonus(level_);
}


const char* Abil_bulletbonus::GetInfor()
{
	switch(level)
	{
	case 1:
		return "���� ������ �Ѿ������ źâ 1���� ����";
	case 2:
		return "���� ������ �Ѿ������ źâ 2���� ����";
	case 3:
		return "���� ������ �Ѿ������ źâ 3���� ����";
	}
	return "���� ����";
}
bool Abil_bulletbonus::EnterMap(Game_Manager* gm_, Player* player_, int level_)
{
	player_->SuppleBullet((float)level);
	return true;
}
