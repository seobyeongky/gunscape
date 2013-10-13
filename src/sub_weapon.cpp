//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: sub_weapon.cpp
//
// ����: ������� Ŭ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "sub_weapon.h"
#include "image.h"
#include "d3dx_class.h"
#include "gamemanager.h"
#include "player.h"
#include "font.h"
#include <stdio.h>

Sub_Weapon::Sub_Weapon(Texture* texture_, const char* name_, const char* infor_, coord_def pos_, int time_, Player* user_, Texture* equip_texture_,  int num_, float equip_speed_):
Item(texture_, name_, infor_, pos_, time_),
user(user_), equip_texture(equip_texture_), num(num_), equip_speed(equip_speed_), equip(false), Used(user?true:false)
{

}
Sub_Weapon::~Sub_Weapon()
{
}

bool Sub_Weapon::InterfaceDraw(Direct_Manager* direct_, coord_def offset_)
{
	if(!equip_texture->Draw(offset_.x+64-600.0f/2, offset_.y-400.0f/2, 1.0f, 0.0f))
		return false;
	RECT rc={(LONG)offset_.x, (LONG)offset_.y+16, (LONG)offset_.x+128, 1000};
	rc.top+=16;
	if(num)
		d3dx_vprintf(coord_def((float)rc.left+15-600.0f/2, (float)rc.top-400.0f/2+10), 1.0f, D3DCOLOR_XRGB(255,255,255), "%5d", num);

	return true;
}
bool Sub_Weapon::InterfaceNameDraw(Direct_Manager* direct_, coord_def offset_)
{
	RECT rc={(LONG)offset_.x, (LONG)(offset_.y+16*direct_->GetHR()), (LONG)(offset_.x+128*direct_->GetWR()), 1000};
	direct_->GetFont()->DrawTextA(NULL, GetName(), -1, &rc, DT_CENTER | DT_NOCLIP, 0xffff0000);
	rc.top+=(LONG)(16*direct_->GetHR());
	if(num)
	{
	}
	else if(equip)
	{
		direct_->GetFont()->DrawTextA(NULL, "<������>", -1, &rc, DT_CENTER | DT_NOCLIP, 0xffff0000);
	}
	return true;
}
bool Sub_Weapon::InforDraw(Direct_Manager* direct_, coord_def offset_)
{
	if(!equip_texture->Draw(offset_.x+64-600.0f/2, offset_.y-400.0f/2, 1.0f, 0.0f))
		return false;
	return true;
}
bool Sub_Weapon::InforNameDraw(Direct_Manager* direct_, coord_def offset_)
{
	RECT rc={(LONG)offset_.x, (LONG)(offset_.y+16*direct_->GetHR()), (LONG)(offset_.x+128*direct_->GetWR()), 1000};
	direct_->GetFont()->DrawTextA(NULL, GetName(), -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	rc.top+=(LONG)(16*direct_->GetHR());
	direct_->GetFont()->DrawTextA(NULL, "SHIFTŰ�� ������ �ݱ�", -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	rc.top+=(LONG)(16*direct_->GetHR());
	direct_->GetFont()->DrawTextA(NULL, "CTRLŰ�� ������ ����Ȯ��", -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	return true;
}
bool Sub_Weapon::DetailInforDraw(Direct_Manager* direct_, coord_def offset_)
{
	RECT rc={(LONG)offset_.x, (LONG)offset_.y, (LONG)(offset_.x+164*direct_->GetWR()), 1000};
	string temp;
	temp+="\n\n����:";
	temp+=GetKindstr();
	if(isUsed())
	{
		temp+="\n����:";
		temp+=GetNumstr();
	}
	temp+="\n\n";
	temp+=GetInfor();
	direct_->GetFont()->DrawTextA(NULL, temp.c_str(), -1, &rc, DT_NOCLIP, 0xffffffff);
	return true;
}
const char* Sub_Weapon::GetKindstr()
{
	sprintf_s(temp_str,32,"%s",isUsed()?"�����":"������");
	return temp_str;
}
const char* Sub_Weapon::GetNumstr()
{
	sprintf_s(temp_str,32,"%d",num);
	return temp_str;
}
bool Sub_Weapon::Effect(Game_Manager* gm_, Player* unit_)
{
	user = unit_;
	Sub_Weapon* temp[2];
	temp[0] = unit_->GetSubWeapon(0);	//�� �κ��� ����. ��� ��������� ������� �˱��� ������?
	temp[1] = unit_->GetSubWeapon(1);	//�� �κ��� ����. ��� ��������� ������� �˱��� ������?
	//������ setSubweapon���� �ٲ� ��������� �ε����� �޾ƿ´�.
	int index_ = unit_->SetSubWeapon(this); //�� �ȿ��� ���� �����ϴ� ��������� ��������.
	if(temp[index_])
	{
		temp[index_]->SetPos(GetPos());
		gm_->item_list.push_back(temp[index_]);
	}
	gm_->item_list.remove(this); //�� �������� �÷��̾�� �ٷ� �����ǹǷ� delete�Ǹ� �ȵȴ�.
	Used = true;
	return true;
}