//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: monster.cpp
//
// 내용: 플레이어를 다루는 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "monster.h"
#include "gamemanager.h"
#include "main_weapon.h"
#include "item_heal.h"
#include "item_bullet.h"
#include "shot_bomb.h"
#include "random.h"
#include "player.h"
#include "ai.h"
#include "FSM.h"
#include "image.h"
#include "effect_message.h"
#include "debug.h"


Monster::Monster(monster_infor& infor_, float x_, float y_, int team_, int time_):
Unit(infor_.name, infor_.texture, x_, y_, team_, infor_.hp), index(infor_.index), ai(NULL), weapon(NULL),
minimum_distans(infor_.minimum_distans), maximum_distans(infor_.maximum_distans), panalty(infor_.panalty), damage(infor_.damage),
exp(infor_.exp), flag(infor_.flag), nonmove_delay(time_), target_continue(0), item_drop(true)
{
	SetSize(infor_.size);
	SetSpeed(infor_.speed);
	SetSight(infor_.sight);
}

Monster::~Monster()
{
	if(ai)
		delete ai;
	if(weapon)
		delete weapon;
}


bool Monster::charDraw(Game_Manager* gm_, coord_def offset, float size_)
{
	float size__ = GetFlySize();
	if(GetTexture())
		return GetTexture()->Draw((GetX()-offset.x)*size_,( GetY()-offset.y)*size_, size_*size__, size_*size__, GetAngle(), D3DCOLOR_ARGB(GetAlpha(gm_),255,255,255));
	return false;
}



void Monster::SetAi(monster_state state_, Unit* head_, int level_)
{
	if(!ai)
	{
		ai = new Ai_Manager(state_, this, head_, level_);
	}
}
void Monster::SetWeapon(Main_Weapon* weapon_)
{
	weapon = weapon_;
}
Vamp_Type Monster::GetKind()
{
	if(CheckFlag(MF_HUMAN))
		return VT_HUMAN;
	else if(CheckFlag(MF_ZOMBIE))
		return VT_ZOMBIE;
	else if(CheckFlag(MF_BUG))
		return VT_BUG;
	else if(CheckFlag(MF_ROBOT))
		return VT_ROBOT;
	else
		return VT_ETC;
}

bool Monster::CheckFlag(Monster_Flag flag_)
{
	return ((flag & flag_) != 0);
}
int Monster::SetDamage(Game_Manager* gm_, coord_def c, Damage_Type type_, float damage_, int team_, float sniper_, int critical_)
{
	if(!isLive() /*|| isNonTarget() */)
		return 0;
	
	bool backstab_ok_ = false;
	if(critical_ && critical_>rand_int(0,99))
	{
		backstab_ok_ = true;
	}
	if(sniper_ != 1.0f && (backstab_ok_ || isBackStabbing()))
	{
		damage_ *= sniper_;
		Effect_simple_speak(gm_,"헤드샷!",GetPos());
		backstab_ok_ = true;
	}
	else
		backstab_ok_ = false;


	int final_damage_ = Unit::SetDamage(gm_, c, type_, damage_, team_);

	if(final_damage_)
		ai->Damage(c);

	if(gm_ && !isLive())
	{
		gm_->GiveExp(team_, exp);
		gm_->KillMonster(team_, this, type_, damage_, backstab_ok_);

		//이 부분은 네트워크시에 바꿔야함. 플레이어캐릭터 의존
		//if(gm_->player->GetTeam() == team_)
		//{
		//	bomb_apply bomb_ = gm_->player->GetDeathBomb();
		//	if(bomb_.damage)
		//		gm_->shot_list.push_back(new Shot_bomb(gm_->player, GetPos(), bomb_.damage, 1.0f, 2.0f, bomb_.range, team_));			
		//}
	}

	return final_damage_;
}
void Monster::SetNoise(Game_Manager* gm_, int team_, coord_def pos_)
{
	ai->Noise(pos_);
}
bool Monster::isBackStabbing()
{
	if(ai)
	{
		switch(ai->GetState())
		{
		case MS_NORMAL:
		case MS_SLEEP:
			return true;
		case MS_ATTACK:
		case MS_SEARCH:
			return false;
		default:
			return false;
		}
	}
	return false;
}
bool Monster::isSleep()
{
	if(ai)
	{
		return ai->GetState() == MS_SLEEP;
	}
	return false;
}
bool Monster::Action_in(Game_Manager* gm_)
{
	if(!isLive())
	{	
		DropItem(gm_);
		return true;
	}
	if(GetWarning()>0)
		UpDownWarning(-5);

	if(weapon && GetFocus()>0)
	{
		UpDownFocus(-weapon->GetFocusCalm());
		if(GetFocus()<0)
			SetFocus(0);
	}
	
	if(!nonmove_delay && !GetFly()/*!fly.fly*/)
	{
		if(ai)
			ai->Action();
	}
	else
	{
	
		if(nonmove_delay)
			nonmove_delay--;
	}

	if(target_continue>0)
		target_continue--;
	
	if(weapon) //현재 주아이템이 있다.
		weapon->Passive(gm_, NULL, true);//발휘되는 패시브 효과		

	Special_Action(gm_);
	CommonAction(gm_);
	return false;
}
bool Monster::TargetLost()
{
	if(ai)
		return ai->TargetLost();
	return false;
}
bool Monster::TargetBlinding()
{
	if(ai)
		return ai->TargetBilnding();
	return false;
}
bool Monster::InvisibleLost(coord_def c)
{
	
	if(ai)
	{
		if(!(flag & MF_INVISIBLE_RESIST))
		{
			return ai->InvisibleLost(c);
		}
	}
	return false;
}
void Monster::Sleep()
{
	if(CanSpeeing())
	{
		if(ai)
			ai->StateChange(MSI_SLEEP);
	}
}
bool Monster::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetShotStop())
		return false;
	if(GetStop())
		return false;
	if(!GetDelay() && weapon)
	{
		focus_ += weapon->GetFocusBase()+GetFocusSum();
		while(SetDelay(weapon->Shot(gm_, this, GetTeam(), GetPos(), c, focus_)*panalty) < 0)
		{
			SetDelay(0.0f);
			weapon->Reload(); //몬스터는 무한 리로드한다.
		}
		if(GetFocus() < weapon->GetFocusMaxReact())
			UpDownFocus(weapon->GetFocusReact());
		return true;
	}
	return false;
}
bool Monster::DropItem(Game_Manager* gm_)
{
	if(!item_drop || !isItemOk())
		return false;

	if(gm_->Heal_percent(false))
	{
		gm_->item_list.push_back(new Item_heal(GetPos(), 1000));
		return true;
	}
	if(gm_->GetCurrentStage() != MPT_NOMAL && gm_->GetCurrentStage() != MPT_LAST)
	{
		if(rand_int(0,2) < 1)
		{
			gm_->item_list.push_back(new Item_bullet(GetPos(), 1000));
			return true;
		}
	}
	else
	{
		if(flag & MF_DROP_BULLET)
		{
			gm_->item_list.push_back(new Item_bullet(GetPos(), 1000));
			return true;
		}
	}
	return false;
}


bool Monster::Melee(Game_Manager* gm_)
{
	if(!GetDamage())
		return false;
	bool ok_ = false;
	if(GetStop())
		return false;
	for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
	{
		if((*it)->isLive() && !(*it)->isNonTarget()  && GetTeam() != (*it)->GetTeam())
		{
			if(GetSize()+(*it)->GetSize()+5.0f > distan_coord(GetPos(), (*it)->GetPos()))
			{
				//if(각도가 맞으면)
				MeleeDamage(gm_,(*it));
				SetDelay(30.0f);
				ok_ = true;
			}
		}
	}
	return ok_;
}
void Monster::MeleeDamage(Game_Manager* gm_, Unit* target_)
{
	int damage_ = target_->SetDamage(gm_, GetPos(), DT_MELEE, GetDamage()*GetAtkApply(), GetTeam());
	GiveDamage(gm_, target_, DT_MELEE, damage_);
	target_->SetSlow(20);
	if(target_->GetMirrorDamage())
	{
		SetDamage(gm_, target_->GetPos(), DT_MIRROR, target_->GetMirrorDamage(), target_->GetTeam());
	}
	if(target_->GetMirrorKnockback())
	{
		SetKnockback(target_->GetMirrorKnockback(), target_->GetMirrorKnockback()*2, GetAngleToTarget(target_->GetPos(),GetPos()));
	}
}
