//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: sub_weapon.cpp
//
// 내용: 서브웨폰 클래스
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
		direct_->GetFont()->DrawTextA(NULL, "<장착중>", -1, &rc, DT_CENTER | DT_NOCLIP, 0xffff0000);
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
	direct_->GetFont()->DrawTextA(NULL, "SHIFT키를 누르면 줍기", -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	rc.top+=(LONG)(16*direct_->GetHR());
	direct_->GetFont()->DrawTextA(NULL, "CTRL키를 누르면 정보확인", -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	return true;
}
bool Sub_Weapon::DetailInforDraw(Direct_Manager* direct_, coord_def offset_)
{
	RECT rc={(LONG)offset_.x, (LONG)offset_.y, (LONG)(offset_.x+164*direct_->GetWR()), 1000};
	string temp;
	temp+="\n\n종류:";
	temp+=GetKindstr();
	if(isUsed())
	{
		temp+="\n갯수:";
		temp+=GetNumstr();
	}
	temp+="\n\n";
	temp+=GetInfor();
	direct_->GetFont()->DrawTextA(NULL, temp.c_str(), -1, &rc, DT_NOCLIP, 0xffffffff);
	return true;
}
const char* Sub_Weapon::GetKindstr()
{
	sprintf_s(temp_str,32,"%s",isUsed()?"사용형":"장착형");
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
	temp[0] = unit_->GetSubWeapon(0);	//이 부분이 난점. 어느 서브웨폰을 장비한지 알길이 있을까?
	temp[1] = unit_->GetSubWeapon(1);	//이 부분이 난점. 어느 서브웨폰을 장비한지 알길이 있을까?
	//정답은 setSubweapon에서 바꾼 서브웨폰의 인덱스를 받아온다.
	int index_ = unit_->SetSubWeapon(this); //이 안에서 원래 착용하던 서브웨폰은 없어진다.
	if(temp[index_])
	{
		temp[index_]->SetPos(GetPos());
		gm_->item_list.push_back(temp[index_]);
	}
	gm_->item_list.remove(this); //이 아이템은 플레이어에게 바로 장착되므로 delete되면 안된다.
	Used = true;
	return true;
}