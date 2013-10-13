//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: main_weapon.cpp
//
// ����: ���ο���
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "main_weapon.h"
#include "main_weapon_list.h"
#include "image.h"
#include "d3dx_class.h"
#include "gamemanager.h"
#include "player.h"
#include "font.h"
#include "sound.h"
#include <stdio.h>



Main_Weapon::Main_Weapon(const main_weapon_infor& infor_, coord_def pos_, int time_):
Item( infor_.texture, infor_.name, infor_.infor, pos_, time_), weapon_kind(infor_.weapon_kind),
equip_texture(infor_.equip_texture), type(infor_.type), bullet(0), max_bullet(infor_.max_bullet), max_bullet_static(infor_.max_bullet), speed_apply(infor_.speed_apply),
reload_speed(infor_.reload_speed), equip_speed(infor_.equip_speed), burst_speed_apply(infor_.burst_speed_apply),
shot_speed_apply(infor_.shot_speed_apply), damage_apply(infor_.damage_apply),focus_base(infor_.focus_base), 
focus_react(infor_.focus_react), focus_max_react(infor_.focus_max_react), focus_calm(infor_.focus_calm),
distance(infor_.distance), noise(infor_.noise), power(infor_.power), max_power(infor_.max_power)
{


}
Main_Weapon::~Main_Weapon()
{
}
bool Main_Weapon::InterfaceDraw(Direct_Manager* direct_, coord_def offset_)
{
	if(!equip_texture->Draw(offset_.x+64-600.0f/2, offset_.y-400.0f/2, 1.0f, 0.0f))
		return false;	
	RECT rc={(LONG)offset_.x, (LONG)offset_.y+16, (LONG)offset_.x+128, 1000};
	rc.top+=16;
	d3dx_vprintf(coord_def((float)rc.left+15-600.0f/2, (float)rc.top-400.0f/2+10), 1.0f, D3DCOLOR_XRGB(255,255,255), "%3d/%3d", bullet, (int)max_bullet);

	return true;
}
bool Main_Weapon::InterfaceNameDraw(Direct_Manager* direct_, coord_def offset_)
{
	RECT rc={(LONG)offset_.x, (LONG)(offset_.y+16*direct_->GetHR()), (LONG)(offset_.x+128*direct_->GetWR()), 1000};
	direct_->GetFont()->DrawTextA(NULL, GetName(), -1, &rc, DT_CENTER | DT_NOCLIP, 0xffff0000);
	return true;
}


bool Main_Weapon::InforDraw(Direct_Manager* direct_, coord_def offset_)
{
	if(!equip_texture->Draw(offset_.x+64-600.0f/2, offset_.y-400.0f/2, 1.0f, 0.0f))
		return false;
	return true;
}	
bool Main_Weapon::InforNameDraw(Direct_Manager* direct_, coord_def offset_)
{
	RECT rc={(LONG)offset_.x, (LONG)(offset_.y+16*direct_->GetHR()), (LONG)(offset_.x+128*direct_->GetWR()), 1000};
	direct_->GetFont()->DrawTextA(NULL, GetName(), -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	rc.top+= (LONG)(16*direct_->GetHR());
	direct_->GetFont()->DrawTextA(NULL, "SHIFTŰ�� ������ ��ü", -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	rc.top+= (LONG)(16*direct_->GetHR());
	direct_->GetFont()->DrawTextA(NULL, "CTRLŰ�� ������ ����Ȯ��", -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	return true;
}
bool Main_Weapon::DetailInforDraw(Direct_Manager* direct_, coord_def offset_)
{
	RECT rc={(LONG)offset_.x, (LONG)offset_.y, (LONG)offset_.x+164, 1000};
	string temp;
	temp+="����:";
	temp+=GetTypeStr();
	temp+="\n������:";
	temp+=GetDamage();
	temp+="\n����ӵ�:";
	temp+=GetAtkSpeed();
	temp+="(��/��)";
	temp+="\n��ź��:";
	temp+=GetBulletStr();
	temp+="\n�ӵ��г�Ƽ:";
	temp+=GetSpeedApplyStr();
	if(GetSniperStr())
	{
		temp+="\n";
		temp+=GetSniperStr();
	}
	temp+="\n\n";
	temp+=GetInfor();
	direct_->GetFont()->DrawTextA(NULL, temp.c_str(), -1, &rc, DT_NOCLIP, 0xffffffff);
	return true;
}



const char* Main_Weapon::GetTypeStr()
{
	switch(type)
	{
	case WT_PISTOL:
		return "����";
	case WT_RIFLE:
		return "������";
	case WT_SHOTGUN:
		return "����";
	case WT_BAZOOKA:
		return "����ī";
	case WT_FLAME_THROWER:
		return "����";
	case WT_ECT:
	default:
		return "��Ÿ";
	}
}
const char* Main_Weapon::GetBulletStr()
{	
	sprintf_s(temp_str,32,"%d",(int)max_bullet_static);
	return temp_str;
}
const char* Main_Weapon::GetSpeedApplyStr()
{
	if(GetSpeedApply() == 1.0f)
		sprintf_s(temp_str,32,"����");
	else
		sprintf_s(temp_str,32,"%d%%",(int)(GetSpeedApply()*100));
	return temp_str;

}


bool Main_Weapon::Effect(Game_Manager* gm_, Player* unit_)
{
	Main_Weapon_Kind temp_kind = MWK_NONE;
	if(unit_->GetMainWeapon())
		temp_kind = unit_->GetMainWeapon()->GetWeaponKind();

	unit_->SetMainWeapon(this); //�� �ȿ��� ���� �����ϴ� ���ο����� delete�ȴ�. �� ���� �ɷ�ġ�� �� �ȿ��� ����
	gm_->item_list.remove(this); //�� �������� �÷��̾�� �ٷ� �����ǹǷ� delete�Ǹ� �ȵȴ�.

	if(temp_kind != MWK_NONE) //���� �����ϴ� ���ο����� ������ ���ͼ� �� �ڸ��� �����Ѵ�.(��ü�� �ǹ�)
		gm_->item_list.push_back(New_Main_Weapon(temp_kind, GetPos(), -1/*�������ӽð����߿�*/));
	//���� ������ �ƴ϶� �ܼ� ��ü�� �Ǹ� �ɷ�ġ�� �Ź� ��� �ٰ� �ȴ�. �װ� �����ϱ����� delete�ϰ� ������ �̿��Ѱ�
	return true;
}


void Main_Weapon::PlayReloadSE()
{
	PlaySE(se_pistol_reload);
}