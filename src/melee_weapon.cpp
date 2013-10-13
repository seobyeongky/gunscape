//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: melee_weapon.cpp
//
// 내용: 근접무기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "melee_weapon.h"
#include "melee_weapon_list.h"
#include "image.h"
#include "d3dx_class.h"
#include "gamemanager.h"
#include "player.h"
#include "shot_melee.h"
#include "texture_list.h"
#include "unit.h"
#include "sound.h"
#include <stdio.h>



Melee_Weapon::Melee_Weapon(const melee_weapon_infor& infor_, coord_def pos_, int time_):
Item( infor_.texture, infor_.name, infor_.infor, pos_, time_), weapon_kind(infor_.weapon_kind),
equip_texture(infor_.equip_texture), effect_texture(infor_.effect_texture), burst_speed(infor_.burst_speed), damage(infor_.damage),
equip_speed(infor_.equip_speed), distance(infor_.distance), distance_static(infor_.distance), width(infor_.width), 
speed_apply(infor_.speed_apply), burst_speed_apply(infor_.burst_speed_apply),
damage_apply(infor_.damage_apply), power(infor_.power), max_power(infor_.max_power),
back_stab(infor_.back_stab?infor_.back_stab:1.0f), back_stab_static(infor_.back_stab?infor_.back_stab:1.0f),
whirlwind_panalty(infor_.whirlwind_panalty)
{


}

Melee_Weapon::~Melee_Weapon()
{
}
bool Melee_Weapon::InterfaceDraw(Direct_Manager* direct_, coord_def offset_)
{
	if(!equip_texture->Draw(offset_.x+64-600.0f/2, offset_.y-400.0f/2, 1.0f, 0.0f))
		return false;
	return true;
}
bool Melee_Weapon::InterfaceNameDraw(Direct_Manager* direct_, coord_def offset_)
{
	RECT rc={(LONG)offset_.x, (LONG)(offset_.y+16*direct_->GetHR()), (LONG)(offset_.x+128*direct_->GetWR()), 1000};
	direct_->GetFont()->DrawTextA(NULL, GetName(), -1, &rc, DT_CENTER | DT_NOCLIP, 0xffff0000);
	return true;
}
bool Melee_Weapon::InforDraw(Direct_Manager* direct_, coord_def offset_)
{
	if(!equip_texture->Draw(offset_.x+64-600.0f/2, offset_.y-400.0f/2, 1.0f, 0.0f))
		return false;
	return true;
}
bool Melee_Weapon::InforNameDraw(Direct_Manager* direct_, coord_def offset_)
{
	RECT rc={(LONG)offset_.x, (LONG)(offset_.y+16*direct_->GetHR()), (LONG)(offset_.x+128*direct_->GetWR()), 1000};
	direct_->GetFont()->DrawTextA(NULL, GetName(), -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	rc.top+=(LONG)(16*direct_->GetHR());
	direct_->GetFont()->DrawTextA(NULL, "SHIFT키를 누르면 교체", -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	rc.top+=(LONG)(16*direct_->GetHR());
	direct_->GetFont()->DrawTextA(NULL, "CTRL키를 누르면 정보확인", -1, &rc, DT_CENTER | DT_NOCLIP, 0xff0000ff);
	return true;
}
bool Melee_Weapon::DetailInforDraw(Direct_Manager* direct_, coord_def offset_)
{
	RECT rc={(LONG)offset_.x, (LONG)offset_.y, (LONG)offset_.x+164, 1000};
	string temp;
	temp+="\n데미지:";
	temp+=GetDamage();
	temp+="\n연사속도:";
	temp+=GetAtkSpeed();
	temp+="(회/초)";	
	temp+="\n사거리:";
	temp+=GetRangeStr();
	temp+="\n속도패널티:";
	temp+=GetSpeedApplyStr();
	if(GetBackstabStr())
	{
		temp+="\n";
		temp+=GetBackstabStr();
	}
	if(GetWWPannaltyStr())
	{
		temp+="\n";
		temp+=GetWWPannaltyStr();
	}
	temp+="\n\n";
	temp+=GetInfor();
	direct_->GetFont()->DrawTextA(NULL, temp.c_str(), -1, &rc, DT_NOCLIP, 0xffffffff);
	return true;
}
const char* Melee_Weapon::GetDamage()
{
	sprintf_s(temp_str,32,"%d",(int)damage);
	return temp_str;
}
const char* Melee_Weapon::GetAtkSpeed()
{
	sprintf_s(temp_str,32,"%.2g",60.0f/burst_speed);
	return temp_str;
}
const char* Melee_Weapon::GetRangeStr()
{
	sprintf_s(temp_str,32,"%d",(int)distance_static);
	return temp_str;
}

const char* Melee_Weapon::GetSpeedApplyStr()
{
	if(GetSpeedApply() == 1.0f)
		sprintf_s(temp_str,32,"없음");
	else
		sprintf_s(temp_str,32,"%d%%",(int)(GetSpeedApply()*100));
	return temp_str;

}
const char* Melee_Weapon::GetBackstabStr()
{
	if(back_stab_static != 1.0f)
	{
		sprintf_s(temp_str,32,"암살 %.2g배 보너스",back_stab_static);
		return temp_str;
	}
	else
	{
		return NULL;
	}
}
const char* Melee_Weapon::GetWWPannaltyStr()
{
	if(!whirlwind_panalty)
	{
		sprintf_s(temp_str,32,"휠윈드 불가능");
		return temp_str;
	}
	else if(whirlwind_panalty != 1.0f)
	{		
		sprintf_s(temp_str,32,"휠윈드시 공속 %d%%",(int)(100.0f/whirlwind_panalty));
		return temp_str;
	}
	else
	{
		return NULL;
	}
}

bool Melee_Weapon::Effect(Game_Manager* gm_, Player* unit_)
{
	Melee_Kind temp_kind = MK_NONE;
	if(unit_->GetMeleeWeapon())
		temp_kind = unit_->GetMeleeWeapon()->GetWeaponKind();

	unit_->SetMeleeWeapon(this); //이 안에서 원래 착용하던 메인웨폰은 delete된다. 이 템의 능력치도 이 안에서 변함
	gm_->item_list.remove(this); //이 아이템은 플레이어에게 바로 장착되므로 delete되면 안된다.

	if(temp_kind != MK_NONE) //원래 착용하던 메인웨폰은 종류만 따와서 그 자리에 생성한다.(교체의 의미)
		gm_->item_list.push_back(New_Melee_Weapon(temp_kind, GetPos(), -1/*아템지속시간나중에*/));
	//새로 생성이 아니라 단순 교체가 되면 능력치가 매번 배로 뛰게 된다. 그걸 방지하기위해 delete하고 종류만 이용한것
	return true;
}
float Melee_Weapon::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f);
	gm_->shot_list.push_back(new Shot_melee(width<3.0f?effect_texture:&tex_melee2, User_, damage_, GetPower(), GetMaxPower(), burst_speed, team_, start_, angle_, GetDistance(), width, back_stab));
	return burst_speed*(1.0f/(GetBurstSpeedApply()*(User_?User_->GetAtkSpdApply():1.0f)));
}

int Melee_Weapon::GetBackStabDamage(Unit* User_)
{
	float damage_ =  damage*GetDamegeApply()*(User_?User_->GetAtkApply():1.0f)*back_stab;
	return (int)damage_;
}