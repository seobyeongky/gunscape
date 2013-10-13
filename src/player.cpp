//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: player.cpp
//
// 내용: 플레이어를 다루는 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "player.h"
#include "main_weapon.h"
#include "melee_weapon.h"
#include "texture_list.h"
#include "image.h"
#include "sub_weapon.h"
#include "gamemanager.h"
#include "d3dx_class.h"
#include "item.h"
#include "font.h"
#include "ability.h"
#include "effect_piece.h"
#include "effect_message.h"
#include "debug.h"


#include "sound.h"

//아래 테스ㅡㅌ
#include "main_weapon_list.h"
#include "rifle.h"

//Player::Player():
//Unit()
//{
//
//}
Player::Player(Texture* texture_, float x_, float y_):
Unit("플레이어",texture_, x_, y_, 1, 100), focus_pos(),
sub_change(0), current_weapon_num(1), current_weapon(0), main_weapon(0), melee_weapon(0), 
no_weapon(0),no_sub_weapon(0),pist(0),
level(1), exp(0),stamina(100.0f), max_stamina(100.0f), stamina_delay(0), speed_delay(0), remain_ability(0), 
select_ability_num(3), ability_select_count(0), ability_select_num(0),
bullet(4), max_bullet(4), ability_select(false), quick_select(false), quick_menu(1), portal_time(1), state_view(false),
mon_sight_view(false), berserker(false), blood_reload(0), forget_count(600), 
warning_time(1000), temp_invisible_turn(0), 
mirror_damage(0), mirror_knockback(0), sniper(false), map_hack(false/*false*/), critical(0), your_switch(3),silencer(1.0f)
{
	for(int i =0 ;i<2;i++)
		sub_weapon[i] = NULL;
	SetSight(100.0f);
	no_weapon = New_Main_Weapon(MWK_NO_WEAPON, coord_def(), -1);
	ApplyDefense(DT_SELF_EXPLOSION, 0.5f);
	//테스트
}

Player::~Player()
{
	if(main_weapon)
		delete main_weapon;
	for(int i =0 ;i<2;i++){
		if(sub_weapon[i])
			delete sub_weapon[i];
	}
	if(melee_weapon)
		delete melee_weapon;
	if(no_weapon)
		delete no_weapon;
	if(no_sub_weapon)
		delete no_sub_weapon;
	if(pist)
		delete pist;
	for(vector<Ability*>::iterator it = abil_list.begin(); it != abil_list.end(); it++)
	{
		delete (*it);
	}	
	for(vector<Ability*>::iterator it = select_abil_list.begin(); it != select_abil_list.end(); it++)
	{
		delete (*it);
	}
}

int Player::GetNeedExp(int level_)
{
	switch(level_)
	{
	case 1: return 0;
	case 2: return 50;
	case 3: return 100;
	case 4: return 180;
	case 5: return 270;
	case 6: return 400;
	case 7: return 550;
	case 8: return 700;
	case 9: return 1000;
	case 10: return 1300;
	case 11: return 1600;
	case 12: return 2000;
	case 13: return 2400;
	case 14: return 2800;
	case 15: return 3300;
	case 16: return -1;
	}
	return -1;
}
Item* Player::GetEmptyWeapon()
{
	switch(current_weapon_num)
	{
	case 1:
		return no_weapon;
	case 2:
	case 3:
	//	return no_sub_weapon; 곧수정
	case 4:
	//	return pist;
	default:
		return no_weapon;
	}
};
float Player::GetExpPercent()
{
	if(GetNeedExp(level+1) == -1)
		return 1.0f;
	return ((float)(exp - GetNeedExp(level)))/(GetNeedExp(level+1)-GetNeedExp(level));
}
int Player::GetBackStabDamage()
{
	if(current_weapon)
		return current_weapon->GetBackStabDamage(this);
	return 0;
}
bool Player::StartAbility()
{
	if(quick_select)
		quick_select = false;

	ability_select = true;

	return ability_select;
}
void Player::SelectAbilityBefore(int i)
{
	if(!ability_select_num)
	{		
		ability_select_count = 100;
		ability_select_num = i;
	}
}
bool Player::SelectAbility(Game_Manager* gm_, int i)
{

	int num_ = select_abil_list.size();
	if(num_ && i <= num_+1)
	{
		vector<Ability*>::iterator it = select_abil_list.begin();
		for(int j=0;j<i-1;j++)
			it++;

		GetAbility(gm_, *it);

		select_abil_list.erase(it);
		for(it = select_abil_list.begin();it!=select_abil_list.end();it++)
			delete (*it);
		select_abil_list.clear();
		remain_ability--;
		if(remain_ability)
			Ability::GetAbility(this, select_ability_num);
		ability_select = false;
		return true;
	}
	return false;
}	
bool Player::StartQuickStart()
{
	if(!ability_select)
	{
		if(quick_select)
			quick_select = false;
		else
			quick_select = true;
	}
	return quick_select;
}
bool Player::SetQuickmenu(int i)
{
	quick_menu = i;
	quick_select = false;
	return true;
}
bool Player::GetAbility(Game_Manager* gm_, Ability* abil_)
{
	for(vector<Ability*>::iterator it = abil_list.begin(); it != abil_list.end(); it++)
	{
		if(!strcmp((*it)->GetName(),abil_->GetName()))
		{
			(*it)->UnLearn(gm_, this);
			(*it)->SetLevel(abil_->GetLevel());
			(*it)->Learn(gm_, this);
			delete abil_;
			return true;
		}
	}
	switch(abil_->GetType())
	{
	case AT_PASSIVE:
		abil_list.push_back(abil_);
		abil_->Learn(gm_, this);
		break;
	case AT_USE:
		use_abil_list.push_back(abil_);
		abil_list.push_back(abil_);
		abil_->Learn(gm_, this);
		break;
	case AT_INSTANCE:
		abil_->Learn(gm_, this);
		break;
	}
	return false;
}
bool Player::UseAbility(Game_Manager* gm_, unsigned int i)
{
	if(i < use_abil_list.size())
	{
		return use_abil_list[i]->UseOnOff(gm_,this);
	}
	return false;
}


bool Player::Swap(int i)
{ //여기서 무기바꾸는 딜레이를 넣어야한다.
	if(sniper)
		return false;
	if(berserker)
		return false;
	switch(i)
	{
	case 1:
		current_weapon = main_weapon;
		current_weapon_num = 1;
		return true;
	case 2:
		current_weapon = sub_weapon[0];
		current_weapon_num = 2;
		return true;
	case 3:
		current_weapon = sub_weapon[1];
		current_weapon_num = 3;
		return true;
	case 4:
		current_weapon = melee_weapon;
		current_weapon_num = 4;
		return true;
	default:
		break;
	}
	return false;
}
bool Player::SetMainWeapon(Main_Weapon* main_weapon_)
{
	float bullet_ = 0.0f;
	if(main_weapon)
	{
		bullet_ = main_weapon->GetBullet() / main_weapon->GetMaxBullet();
		DeleteMainWeapon();
	}

	for(vector<Ability*>::iterator it = abil_list.begin(); it != abil_list.end(); it++)
	{
		(*it)->ActiveMainWeapon(main_weapon_);
	}

	main_weapon_->SetBullet((int)(bullet_*main_weapon_->GetMaxBullet()));

	ApplySpeed(main_weapon_->GetSpeedApply());

	main_weapon = main_weapon_;
	if(!current_weapon)
		current_weapon = main_weapon;
	
	UpDownDelay((int)main_weapon_->GetEquipSpeed());
	return true;
}
int Player::SetSubWeapon(Sub_Weapon* sub_weapon_)
{
	int cur_sub_ = sub_change;
	
	//여기서 바꾸는 알고리즘
	//보조무기중 한개가 비어있는 경우: 비어있는 곳과 바꾼다.
	//만약 보조무기를 들고있는경우: 해당 보조무기와 바꾼다.
	//첫번째와 두번쨰 서브웨폰을 번갈아 가면서 돌린다.
	if(!sub_weapon[0] || !sub_weapon[1]){
		if(!sub_weapon[0])
			cur_sub_ = 0;
		else if(!sub_weapon[1])
			cur_sub_ = 1;
	}
	else if(current_weapon_num == 2 || current_weapon_num == 3){		
		if(current_weapon_num == 2)
			cur_sub_ = 0;
		else if(current_weapon_num == 3)
			cur_sub_ = 1;
	}
	else{
		sub_change = !sub_change;
	}
	

	if(sub_weapon[cur_sub_])
	{
		DeleteSubWeapon(NULL, cur_sub_);
	}

	for(vector<Ability*>::iterator it = abil_list.begin(); it != abil_list.end(); it++)
	{
		(*it)->ActiveSubWeapon(sub_weapon_);
	}


	sub_weapon[cur_sub_] = sub_weapon_;
	if(!current_weapon)
		current_weapon = sub_weapon[cur_sub_];
	
	if(sub_weapon_->isEquip()){
		sub_weapon_->Shot(NULL, this, GetTeam(), GetPos(), coord_def(), 0.0f);
	}

	UpDownDelay((int)sub_weapon_->GetEquipSpeed());
	return cur_sub_;
}
bool Player::SetMeleeWeapon(Melee_Weapon* melee_weapon_)
{
	if(melee_weapon)
	{
		DeleteMeleeWeapon();
	}

	for(vector<Ability*>::iterator it = abil_list.begin(); it != abil_list.end(); it++)
	{
		(*it)->ActiveMeleeWeapon(melee_weapon_);
	}

	melee_weapon = melee_weapon_;
	if(!current_weapon)
		current_weapon = melee_weapon;

	UpDownDelay((int)melee_weapon_->GetEquipSpeed());
	return true;
}
bool Player::UseStamina(float value_)
{
	if(value_<=stamina)
	{
		stamina -= value_;
		return true;
	}
	return false;
}
void Player::DeleteMainWeapon()
{
	if(!main_weapon)
		return;
	if(current_weapon == main_weapon)
		current_weapon = NULL;
	ApplySpeed(1/(main_weapon->GetSpeedApply()));
	delete main_weapon;
	main_weapon = NULL;
}
void Player::DeleteSubWeapon(Item* it_, int num)
{
	if(num == -1){ //현재 장비한 무기를 지우기
		if(it_)
		{
			if(sub_weapon[0] == it_)
				num = 0;
			else if(sub_weapon[1] == it_)
				num = 1;
			else
				return; //이건 나와선 안되는데... 에러에러
		}
		else
		{
			if(current_weapon_num == 2)
				num = 0;
			else if(current_weapon_num == 3)
				num = 1;
			else
				return;//에러. 실패
		}
	}


	if(!sub_weapon[num])
		return;
	if(sub_weapon[num]->GetEquip())
		sub_weapon[num]->UnEquip();
	if(current_weapon == sub_weapon[num])
		current_weapon = NULL;
	//delete sub_weapon;  *서브웨폰은 지워지지않는다 주의!
	sub_weapon[num] = NULL;
}
void Player::DeleteMeleeWeapon()
{
	if(!melee_weapon)
		return;
	if(current_weapon == melee_weapon)
		current_weapon = NULL;
	delete melee_weapon;
	melee_weapon = NULL;
}
bool Player::Action_in(Game_Manager* gm_)
{
	if(GetFocus()>0) //반동이 줄어듬
	{
		UpDownFocus(-main_weapon->GetFocusCalm());
		if(GetFocus()<0)
			SetFocus(0);
	}
	{ //여기서 에임을 맞춘곳이나 근접한 적의 투명을 탐지한다.
		for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
		{
			if(!(*it)->isPlayer())
				
				{
					if(distan_coord(GetPos(),(*it)->GetPos()) < 30.0f)		//근접탐지 : 30  (나중에 변수로 고침. 능력을 위해서)				
					{
						(*it)->Insight(gm_, this, true);

					}
						
					if(distan_coord(GetFocusPos(),(*it)->GetPos()) < 20.0f ) //에임으로 적을 탐지하는 범위 : 20. (나중에 변수로 고침. 능력을 위해서)
					{
						(*it)->Insight(gm_, this, false);
					}
			}
		}
	}

	for(list<Item*>::iterator it = gm_->item_list.begin();it != gm_->item_list.end();it++) //아이템을 줍는다.
	{
		if((*it)->isValid() && (*it)->GetItemType() == IT_INSTANT)
		{
			if(collution((*it)->GetPos(), 10.0f))
			{
				(*it)->Effect(gm_, this);
				(*it)->Erase();
			}
		}
	}
	if(main_weapon) //현재 주아이템이 있다.
		main_weapon->Passive(gm_, this, (main_weapon == current_weapon));//발휘되는 패시브 효과		
	if(sub_weapon[0])//현재 보조아이템이 있다.
		sub_weapon[0]->Passive(gm_, this, (sub_weapon[0] == current_weapon));//발휘되는 패시브 효과		
	if(sub_weapon[1])//현재 보조아이템이 있다.
		sub_weapon[1]->Passive(gm_, this, (sub_weapon[1] == current_weapon));//발휘되는 패시브 효과		
	if(melee_weapon) //현재 근접아이템이 있다.
		melee_weapon->Passive(gm_, this, (melee_weapon == current_weapon));//발휘되는 패시브 효과		

	for(vector<Ability*>::iterator it = abil_list.begin() ; it != abil_list.end() ; it++) //능력이 사용된다.
	{
		(*it)->Action(gm_, this);
	}
	
	if(temp_invisible_turn)
	{
		temp_invisible_turn--;
		if(temp_invisible_turn)
			SetInvisible(255);
		else
			SetInvisible(0);
	}

	//상태그리기
	for(list<state_name>::iterator it = state_list.begin();it != state_list.end();)
	{
		if(it->turn>0)
		{
			it->turn--;
			it++;
		}
		else
		{
			list<state_name>::iterator temp = it;
			it++;
			state_list.erase(temp);
		}
	}




	if(speed_delay)
		speed_delay--;
	if(stamina_delay)  //스테미나가 회복하지않는 딜레이
		stamina_delay--;
	else  //스테미나의 자연회복
	{
		stamina+=1.0f;
		if(stamina > max_stamina)
			stamina = max_stamina;
		if(remain_ability)
		{
			Ability::GetAbility(this, select_ability_num);
			StartAbility();
		}
	}

	CommonAction(gm_); //유닛 공통의 행동들
	return false;
}
void Player::SelectAction(Game_Manager* gm_)
{	
	if(ability_select_count)
	{
		ability_select_count--;
		if(!ability_select_count)
		{
			SelectAbility(gm_,ability_select_num);
			ability_select_num = 0;
			ability_select_count = 0;
		}
	}
}

float Player::GetFocusSum()
{
	float focus_ = GetFocus()+(GetSlow()?0.2f:0.0f);
	if(current_weapon && (current_weapon == main_weapon))
		focus_ += main_weapon->GetFocusBase();
	return focus_;
}
float Player::GetPlayerSpeed(float angle_)
{
	float panalty_ = 1.0f;
	if(!speed_delay)
		panalty_ *= 1.5f;
	return panalty_;
}
void Player::StateApply(const char* name_, int turn_)
{
	for(list<state_name>::iterator it=state_list.begin();it!=state_list.end();it++)
	{
		if(!it->name.compare(name_))
		{
			if(it->turn < turn_)
				it->turn  = turn_;
			return;
		}
	}
	state_list.push_back(state_name(name_,turn_));
}
bool Player::GiveExp(Game_Manager* gm_, int value_)
{
	if(GetNeedExp(level+1) == -1)
		return false;



	exp+=value_;
	if(exp >= GetNeedExp(level+1))
	{
		LevelUp(gm_);
	}
	return false;
}
bool Player::KillMonster(Game_Manager* gm_, int team_, Monster* monster_, Damage_Type type_, float damage_, bool back_stab_)
{
	for(vector<Ability*>::iterator it = abil_list.begin(); it != abil_list.end(); it++)
	{
		(*it)->KillMonster(gm_, monster_, this, type_, damage_, back_stab_);
	}
	return false;
}
bool Player::EnterMap(Game_Manager* gm_, int level_)
{
	for(vector<Ability*>::iterator it = abil_list.begin(); it != abil_list.end(); it++)
	{
		(*it)->EnterMap(gm_, this, level_);
	}
	return false;
}
bool Player::LevelUp(Game_Manager* gm_)
{
	level++;
	remain_ability++;
	Effect_simple_speak(gm_, "레벨업!",GetPos());
	return true;
}
bool Player::HpDraw(coord_def offset_)
{
	d3dx_vprintf(offset_, 1.0f, D3DCOLOR_XRGB(150,150,255), "%2d", level);
	offset_.x+=30.0f;
	tex_system_heart.Draw(offset_.x, offset_.y, 1.0f, 0.0f);
	offset_.x+=30.0f;
	d3dx_vprintf(offset_, 1.0f, D3DCOLOR_XRGB(255,100,100), "%3d/%3d", GetHp()>0?GetHp():0, GetMaxHp());
	
	return true;
}
bool Player::StaminaDraw(coord_def offset_)
{
	//tex_system_exp.Draw(offset_.x, offset_.y, 1.0f, 0.0f);
	tex_system_gauge_border.Draw(offset_.x+70.0f,  offset_.y, 1.0f, 0.0f);
	float pecen_ = stamina/max_stamina;
	tex_system_gauge.Draw(offset_.x+23.0f + 47*pecen_,  offset_.y, pecen_, 1.0f, 0.0f, D3DCOLOR_ARGB(255,255,255,0));
	return true;
}
bool Player::ExpDraw(coord_def offset_)
{
	tex_system_exp.Draw(offset_.x, offset_.y, 1.0f, 0.0f);
	tex_system_gauge_border.Draw(offset_.x+70.0f,  offset_.y, 1.0f, 0.0f);
	float pecen_ = GetExpPercent();
	tex_system_gauge.Draw(offset_.x+23.0f + 47*pecen_,  offset_.y, pecen_, 1.0f, 0.0f);
	return true;
}
bool Player::PickUpDraw(Game_Manager* gm_, coord_def offset_)
{
	for(list<Item*>::iterator it = gm_->item_list.begin();it != gm_->item_list.end();it++)
	{
		if((*it)->isValid() && (*it)->GetItemType() != IT_INSTANT)
		{
			if(collution((*it)->GetPos(), 10))
			{
				(*it)->InforDraw(gm_->direct, offset_);
				return true;
			}
		}
	}
	return false;
}
bool Player::PickUpNameDraw(Game_Manager* gm_, coord_def offset_)
{
	for(list<Item*>::iterator it = gm_->item_list.begin();it != gm_->item_list.end();it++)
	{
		if((*it)->isValid() && (*it)->GetItemType() != IT_INSTANT)
		{
			if(collution((*it)->GetPos(), 10))
			{
				(*it)->InforNameDraw(gm_->direct, offset_);
				return true;
			}
		}
	}
	return false;
}

bool Player::DetailInforDraw(Game_Manager* gm_, coord_def L_offset_, coord_def R_offset_)
{	
	for(list<Item*>::iterator it = gm_->item_list.begin();it != gm_->item_list.end();it++)
	{
		if((*it)->isValid() && (*it)->GetItemType() != IT_INSTANT)
		{
			if(collution((*it)->GetPos(), 10))
			{
				(*it)->DetailInforDraw(gm_->direct, L_offset_);
				break;
			}
		}
	}
	if(GetCurrentWeapon())
		GetCurrentWeapon()->DetailInforDraw(gm_->direct, R_offset_);
	return true;
}
bool Player::AbilityUpDraw(Game_Manager* gm_, coord_def offset_)
{
	if(remain_ability)
	{
		RECT rc={0, (LONG)offset_.y, (LONG)offset_.x, 1000};
		gm_->direct->GetFont()->DrawTextA(NULL, "레벨업! 잠시후 능력을 선택합니다.", -1, &rc, DT_RIGHT | DT_NOCLIP, 0xffffffff);
	}
	return true;
}
bool Player::TestDraw(Game_Manager* gm_, coord_def offset_)
{
	char temp[128];
	sprintf_s(temp,128,"공속적용은 %g인것이다.",main_weapon->GetBurstSpeedApply());
	RECT rc={0, (LONG)offset_.y, (LONG)offset_.x, 1000};
	gm_->direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_RIGHT | DT_NOCLIP, 0xff0000ff);
	
	return true;
}
bool Player::AbilitySelectDraw(Game_Manager* gm_, coord_def offset_)
{
	if(remain_ability && ability_select)
	{
		int i=1;
		char temp[256];
		RECT rc={(LONG)(offset_.x+gm_->direct->GetWidth()/2.0f), (LONG)(offset_.y+gm_->direct->GetHeight()/2.0f), 1000, 1000};
		gm_->direct->GetFont()->DrawTextA(NULL, "레벨업했습니다! 배우고 싶은 능력의 숫자키를 선택해주세요.", -1, &rc, DT_LEFT | DT_NOCLIP, 0xff0090ff);
		for(vector<Ability*>::iterator it = select_abil_list.begin(); it != select_abil_list.end(); it++)
		{
			rc.top += (LONG)(16*gm_->direct->GetHR());
			D3DCOLOR color_ = (*it)->GetType() == AT_INSTANCE?0xff00ff00:((*it)->GetType() == AT_USE?0xffc000c0:0xff0090ff);
			if(ability_select_count && ability_select_num == i)
			{
				color_ =0xffff0000;
			}
			sprintf_s(temp,256,"%d.%s(%d레벨)-%s",i++,(*it)->GetName(),(*it)->GetLevel(),(*it)->GetInfor());

			gm_->direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_NOCLIP, color_);
		}
	}
	return true;
}
bool Player::AbilityDraw(Game_Manager* gm_, coord_def offset_)
{
	if(!abil_list.empty())
	{
		int i=1;
		char temp[256];
		RECT rc={(LONG)(offset_.x+gm_->direct->GetWidth()/2.0f), (LONG)(offset_.y+gm_->direct->GetHeight()/2.0f), 1000, 1000};
		gm_->direct->GetFont()->DrawTextA(NULL, "<현재 배운 능력들>", -1, &rc, DT_LEFT | DT_NOCLIP, 0xffff0000);
		for(vector<Ability*>::iterator it = abil_list.begin(); it != abil_list.end(); it++)
		{
			rc.top += (LONG)(16*gm_->direct->GetHR());
			sprintf_s(temp,256,"%d.%s(%d레벨)",i++,(*it)->GetName(),(*it)->GetLevel());
			gm_->direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_NOCLIP, 0xffff0000);
		}
	}
	return true;
}
bool Player::QuickMenuDraw(Game_Manager* gm_, coord_def offset_)
{
	if(quick_select)
	{
		int i=1;
		char temp[256];
		RECT rc={(LONG)(offset_.x+gm_->direct->GetWidth()/2.0f), (LONG)(offset_.y+gm_->direct->GetHeight()/2.0f), 1000, 1000};
		gm_->direct->GetFont()->DrawTextA(NULL, "마우스 오른쪽버튼으로 퀵메뉴화할 기능을 골라주세요.", -1, &rc, DT_LEFT | DT_NOCLIP, 0xffff0000);

		
		rc.top += (LONG)(32*gm_->direct->GetHR());
		if(main_weapon && main_weapon->is_Special())
			sprintf_s(temp,256,"1 - %s",main_weapon->is_Special());
		else
			sprintf_s(temp,256,"1 - 없음");
		gm_->direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_NOCLIP, 0xffff0000);

		
		rc.top += (LONG)(16*gm_->direct->GetHR());
		if(sub_weapon[0])
			sprintf_s(temp,256,"2 - %s",sub_weapon[0]->GetName());
		else
			sprintf_s(temp,256,"2 - 없음");
		gm_->direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_NOCLIP, 0xffff0000);

		
		rc.top += (LONG)(16*gm_->direct->GetHR());
		if(sub_weapon[1])
			sprintf_s(temp,256,"3 - %s",sub_weapon[1]->GetName());
		else
			sprintf_s(temp,256,"3 - 없음");
		gm_->direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_NOCLIP, 0xffff0000);

		
		rc.top += (LONG)(16*gm_->direct->GetHR());
		if(melee_weapon)
			sprintf_s(temp,256,"4 - %s",melee_weapon->GetName());
		else
			sprintf_s(temp,256,"4 - 없음");
		gm_->direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_NOCLIP, 0xffff0000);

		rc.top += (LONG)(16*gm_->direct->GetHR());
		if(0 < use_abil_list.size())
			sprintf_s(temp,256,"z - %s",use_abil_list[0]->GetName());
		else
			sprintf_s(temp,256,"z - 없음");
		gm_->direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_NOCLIP, 0xffff0000);

/*		rc.top += 16*gm_->direct->GetHR();
		if(1 < use_abil_list.size())
			sprintf_s(temp,256,"x - %s",use_abil_list[1]->GetName());
		else
			sprintf_s(temp,256,"x - 없음");
		gm_->direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_NOCLIP, 0xffff0000);*/		
	}
	return true;
}
bool Player::UseAbilityDraw(Game_Manager* gm_, coord_def offset_)
{
	if(!use_abil_list.empty())
	{
		int i=1;
		char temp[256];
		RECT rc={(LONG)(offset_.x+gm_->direct->GetWidth()/2.0f), (LONG)(offset_.y+gm_->direct->GetHeight()/2.0f), 1000, 1000};
		for(vector<Ability*>::iterator it = use_abil_list.begin(); it != use_abil_list.end(); it++)
		{
			rc.top += (LONG)(16*gm_->direct->GetHR());
			char char_[32];
			sprintf_s(char_,32,"%s",i==1?"z":"x");
			if((*it)->isUsing())
				sprintf_s(temp,256,"%s키 - %s(사용중)",char_,(*it)->GetName());
			else if((*it)->GetUseBullet())
				sprintf_s(temp,256,"%s키 - %s(탄창%g개 소모)",char_,(*it)->GetName(),(*it)->GetUseBullet());
			else
				sprintf_s(temp,256,"%s키 - %s",char_,(*it)->GetName());

			gm_->direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_NOCLIP, 0xffff0000);
			i++;
		}
	}
	return true;
}
bool Player::StateDraw(Game_Manager* gm_, coord_def offset_)
{
	char temp[256];
	RECT rc={(LONG)(offset_.x+gm_->direct->GetWidth()/2.0f), (LONG)(offset_.y+gm_->direct->GetHeight()/2.0f), 1000, 1000};

	for(list<state_name>::iterator it = state_list.begin(); it != state_list.end(); it++)
	{
		sprintf_s(temp,256,"%s",it->name.c_str());
		gm_->direct->GetFont()->DrawTextA(NULL, temp, -1, &rc, DT_LEFT | DT_NOCLIP, 0xffffffff);
		rc.top += (LONG)(16*gm_->direct->GetHR());
	}
	return true;
}
bool Player::StateGaugeDraw(Game_Manager* gm_, coord_def offset_)
{
	float y_ = 0;
	for(list<state_name>::iterator it = state_list.begin(); it != state_list.end(); it++)
	{
		float size_ = it->turn*60.0f/it->max_turn;
		tex_gun.Draw((offset_.x+size_/2),(offset_.y+y_)+14,size_,3.0f,0.0f);
		y_ += 16.0f;
	}
	return true;
}


bool Player::DelayDraw(coord_def offset_, float size_)
{
	if(GetDelay() && GetMaxDelay())
	{
		float size__ = (float)GetDelay()*24.0f/GetMaxDelay();
		tex_gun.Draw((offset_.x+size__/2-12)*size_,(offset_.y)*size_,size_*size__,size_,0.0f);
	}
	return true;
}
bool Player::BulletDraw(coord_def offset_)
{
	int i = 0;
	for(i = 0;i<(int)bullet;i++)
	{
		tex_item_bullet.Draw(offset_.x+i*16,offset_.y,1.0f,0.0f);
	}
	float surplus = bullet - (int)bullet;
	if(surplus)
	{
		tex_item_bullet.SetVertex((int)(surplus*12), 9);
		tex_item_bullet.Draw(offset_.x+i*16,offset_.y,1.0f,0.0f);
		tex_item_bullet.SetVertex(12, 9);
	}
	return true;	
}
bool Player::FogDraw(coord_def offset_, coord_def window_size_)
{
	bool ok_ = false;
	float size_ = GetView()/50.0f;

	if(berserker && tex_gun.Draw(offset_.x,offset_.y,window_size_.x,window_size_.x,0,D3DCOLOR_ARGB(100,255,0,0)))
		ok_ = true;

	if(tex_fog.Draw(offset_.x,offset_.y,size_,0.0f))
		ok_ = true;
	return ok_;
}
bool Player::SniperDraw(coord_def offset_, coord_def window_size_)
{
	bool ok_ = false;
	if(tex_sniper.Draw(offset_.x,offset_.y,1.5f,0.0f))
		ok_ = true;
	return ok_;
}
bool Player::PickUp(Game_Manager* gm_)
{
	for(list<Item*>::iterator it = gm_->item_list.begin();it != gm_->item_list.end();it++)
	{
		if((*it)->isValid() && (*it)->GetItemType() != IT_INSTANT && (*it)->GetItemType() != IT_DOOR)
		{
			if(collution((*it)->GetPos(), 10))
			{
				(*it)->Effect(gm_, this);
				//(*it)->Erase(); Erase되면 안됨. 착용한 템은 플레이어에게 간다.
				return true;
			}
		}
	}
	return false;
}
bool Player::is_Click_Hold()
{
	if(current_weapon)
	{
		return current_weapon->is_Click_Hold();
	}
	return false;
}

bool Player::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetStop())
		return false;
	Item* item_ = NULL;
	switch(item_num)
	{
	case 0:
		item_ = current_weapon;
		break;
	case 1:
		item_ = main_weapon;
		break;
	case 2:
		item_ = sub_weapon[0];
		break;
	case 3:
		item_ = sub_weapon[1];
		break;
	case 4:
		item_ = melee_weapon;
		break;
	}
	if(!GetDelay() && item_)
	{
		focus_ += GetFocusSum();
		InitNoneMoveCount();
		if(SetDelay(item_->Shot(gm_, this, GetTeam(), GetPos(), c, focus_)) == -1)
		{
			SetDelay(0);
			if(item_ == main_weapon)
			{
				Reload();
			}
			return false;
		}
		else
		{
			if(item_ == main_weapon)
			{
				if(GetFocus() < main_weapon->GetFocusMaxReact())
					UpDownFocus(main_weapon->GetFocusReact());
			}
			return true;
		}
	}
	return false;
}
bool Player::Special(Game_Manager* gm_, coord_def c, float focus_)
{
	if(GetStop())
		return false;
	if(current_weapon)
	{
		//focus_ += GetFocusSum();
		//InitNoneMoveCount();
		if(SetDelay(current_weapon->special(gm_, this, GetTeam(), GetPos(), c, focus_)) == -1)
		{
			//이 부분은 미구현
			//SetDelay(0);
			return false;
		}
		else
		{
			//이 부분도 미구현
			return true;
		}
	}
	return false;
}
bool Player::Quick(Game_Manager* gm_, coord_def c, float focus_)
{
	if(GetStop())
		return false;
	if(berserker)
		return false;
	switch(quick_menu)
	{
	case 1:
		Special(gm_, c, focus_);
		break;
	case 2:
		Shot(gm_, c, focus_, 2);
		break;
	case 3:
		Shot(gm_, c, focus_, 3);
		break;
	case 4:
		Shot(gm_, c, focus_, 4);
		break;
	case 5:
		UseAbility(gm_, 0);
		break;
	case 6:
		UseAbility(gm_, 1);
		break;
	default:
		return false;
	}
	return true;
}
bool Player::Reload()
{//나중에 bullet의 갯수에 의해서 리로딩하게 하자
	if(current_weapon && current_weapon == main_weapon)
	{
		float need_bullet = 1.0f-((float)main_weapon->GetBullet()/(int)main_weapon->GetMaxBullet());
		if(need_bullet && bullet > 0.0f)
		{
			main_weapon->PlayReloadSE();
			need_bullet = min(need_bullet,bullet);
			bullet -= need_bullet;
			SetDelay(main_weapon->Reload(need_bullet));
		}
		else if(blood_reload && GetHp()>blood_reload)
		{
			main_weapon->PlayReloadSE();
			UpDownHp(-(int)(blood_reload*need_bullet+0.99f));
			SetDelay(main_weapon->Reload(need_bullet));
		}
	}
	return true;
}
bool Player::UseBullet(float bullet_)
{
	if(bullet >= bullet_)
	{
		bullet -= bullet_;
		return true;
	}
	else
		return false;

}