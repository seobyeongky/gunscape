//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: ability.cpp
//
// 내용: 능력 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <algorithm>
#include <list>
#include "ability.h"
#include "player.h"
#include "gamemanager.h"
#include "random.h"

#include "abil_pistol.h"
#include "abil_rifle.h"
#include "abil_flame.h"
#include "abil_fire.h"
#include "abil_shot_gun.h"
#include "abil_health.h"
#include "abil_dex.h"
#include "abil_bullet.h"
#include "abil_sight.h"
#include "abil_bazooka.h"
#include "abil_antiexplosion.h"
#include "abil_moonwalk.h"
#include "abil_fast_portal.h"
#include "abil_knowledge.h"
#include "abil_run.h"
#include "abil_invisible.h"
#include "abil_berserker.h"
#include "abil_knife.h"
#include "abil_state_view.h"
#include "abil_live.h"
#include "abil_see_sight.h"
#include "abil_bare.h"
#include "abil_marathoner.h"
#include "abil_vampire.h"
#include "abil_antibug.h"
#include "abil_immortal.h"
#include "abil_escape_forget.h"
#include "abil_speedreload.h"
#include "abil_bulletup.h"
#include "abil_bulletbonus.h"
#include "abil_dash.h"
#include "abil_stealth.h"
#include "abil_shadow.h"
#include "abil_map.h"
#include "abil_killstamina.h"
#include "abil_deathbomb.h"
#include "abil_instant_heal.h"
#include "abil_instant_bullet.h"
#include "abil_mirror_damage.h"
#include "abil_bloodreload.h"
#include "abil_bulletbonus.h"
#include "abil_whirlwind.h"
#include "abil_critical.h"
#include "abil_chaininvi.h"
#include "abil_vaccine.h"
#include "abil_hack_slash.h"
#include "abil_repress.h"
#include "abil_post.h"
#include "abil_cry.h"
#include "abil_antizombie.h"
#include "abil_murder.h"
#include "abil_sleep.h"





int Ability::abil_num = 0;
map<string,Ability*> Ability::ability_list;

Ability::Ability(const char* name_, int level_, int max_level_, int percent_, int need_level_, Ability_Type type_):
name(name_), id(-1), level(level_), max_level(max_level_), percent(percent_), need_level(need_level_), type(type_)
{

}
Ability::~Ability()
{
}
void Ability::InitAbility(Game_Manager* gm_)
{//static함수
	//AddAbility(new Abil_pistol(1));
	//AddAbility(new Abil_rifle(1));
	//AddAbility(new Abil_flame(1));
	AddAbility(new Abil_fire(1));
	//AddAbility(new Abil_shot_gun(1));
	AddAbility(new Abil_health(1));
	AddAbility(new Abil_dex(1));
	AddAbility(new Abil_bullet(1));
	AddAbility(new Abil_sight(1));
	//AddAbility(new Abil_bazooka(1));
	AddAbility(new Abil_antiexplosion(1));
	AddAbility(new Abil_moonwalk(1));
	AddAbility(new Abil_fast_portal(1));
	AddAbility(new Abil_knowledge(1));
	AddAbility(new Abil_run(1));
	AddAbility(new Abil_invisible(1));
	AddAbility(new Abil_berserker(1));
	AddAbility(new Abil_knife(1));
	AddAbility(new Abil_state_view(1));
	AddAbility(new Abil_live(1));
	//AddAbility(new Abil_see_sight(1));
	AddAbility(new Abil_bare(1));
	AddAbility(new Abil_marathoner(1));
	AddAbility(new Abil_vampire(1));
	AddAbility(new Abil_antibug(1));
	AddAbility(new Abil_immortal(1));
	AddAbility(new Abil_Escape_Forget(1));
	//AddAbility(new Abil_map(1));
	AddAbility(new Abil_speedreload(1));
	AddAbility(new Abil_bulletup(1));
	AddAbility(new Abil_dash(1));
	AddAbility(new Abil_stealth(1));
	AddAbility(new Abil_kill_stamina(1));
	AddAbility(new Abil_deathbomb(1));
	AddAbility(new Abil_Instant_heal(1));
	AddAbility(new Abil_Instant_bullet(1));
	AddAbility(new Abil_mirror_damage(1));
	AddAbility(new Abil_shadow(1));
	AddAbility(new Abil_bloodreload(1));
	AddAbility(new Abil_bulletbonus(1));
	AddAbility(new Abil_whirlwind(1));
	AddAbility(new Abil_critical(1));
	AddAbility(new Abil_chaininvi(1));
	AddAbility(new Abil_vaccine(1));
	AddAbility(new Abil_hack_slash(1));
	AddAbility(new Abil_repress(1));
	AddAbility(new Abil_post(1));
	AddAbility(new Abil_cry(1));
	AddAbility(new Abil_antizombie(1));
	AddAbility(new Abil_murder(1));
	AddAbility(new Abil_sleep(1));


	
}
void Ability::ReleaseAbility()
{
	for(map<string,Ability*>::iterator it = ability_list.begin(); it != ability_list.end(); it++)
	{
		delete it->second;
	}
	ability_list.clear();
}
bool Ability::AddAbility(Ability* ability_)
{//static함수
	map<string,Ability*>::iterator it;
	it=ability_list.find(ability_->GetName());
	if(it == ability_list.end())
	{
		ability_->SetId(abil_num);
		ability_list[ability_->GetName()] = ability_;
		abil_num++;
		return true;
	}
	else
		return false;
}
bool Ability::GetAbility(Player* player_, int num)
{//static함수
	if(player_->select_abil_list.empty())
	{
		int sum_percent_ = 0;
		list<Ability*> temp_list;
		for(map<string,Ability*>::iterator it = ability_list.begin(); it != ability_list.end(); it++)
		{
			if(it->second->Possible(player_))
			{
				temp_list.push_back(it->second);
				sum_percent_ += it->second->GetPercent();
			}
		}
		for(int i = 0; i < num ; i++)
		{
			int select_ = rand_int(1,sum_percent_);

			for(list<Ability*>::iterator it = temp_list.begin(); it != temp_list.end(); it++)
			{
				if(select_<=(*it)->GetPercent())
				{
					player_->select_abil_list.push_back((*it)->Clone((*it)->Possible(player_)));
					sum_percent_ -= (*it)->GetPercent();
					temp_list.erase(it);
					break;
				}
				else
					select_-=(*it)->GetPercent();
			}
		}
		return true;
	}
	return false;
}
bool Ability::Learn(Game_Manager* gm_, Player* player_)
{
	if(type == AT_PASSIVE)
	{
		return Active(gm_, player_);
	}
	else if(type == AT_INSTANCE)
	{
		return InstanceActive(player_);
	}
	return false;
}	
bool Ability::UnLearn(Game_Manager* gm_, Player* player_)
{
	if(type == AT_PASSIVE)
	{
		return UnActive(gm_, player_);
	}
	return false;
}
bool Ability::Active(Game_Manager* gm_, Player* player_)
{
	bool ok_ = false;
	
	ok_ &= ActiveGame(gm_,player_);
	ok_ &= ActivePlayer(player_);
	if(player_->GetMainWeapon())
		ok_ &= ActiveMainWeapon(player_->GetMainWeapon());
	if(player_->GetSubWeapon(0))
		ok_ &= ActiveSubWeapon(player_->GetSubWeapon(0));
	if(player_->GetSubWeapon(1))
		ok_ &= ActiveSubWeapon(player_->GetSubWeapon(1));
	if(player_->GetMeleeWeapon())
		ok_ &= ActiveMeleeWeapon(player_->GetMeleeWeapon());
	return ok_;
}
bool Ability::UnActive(Game_Manager* gm_, Player* player_)
{
	bool ok_ = false;
	ok_ &= UnActiveGame(gm_,player_);
	ok_ &= UnActivePlayer(player_);
	if(player_->GetMainWeapon())
		ok_ &= UnActiveMainWeapon(player_->GetMainWeapon());
	if(player_->GetSubWeapon(0))
		ok_ &= UnActiveSubWeapon(player_->GetSubWeapon(0));
	if(player_->GetSubWeapon(1))
		ok_ &= ActiveSubWeapon(player_->GetSubWeapon(1));
	if(player_->GetMeleeWeapon())
		ok_ &= UnActiveMeleeWeapon(player_->GetMeleeWeapon());
	return ok_;
}
bool Ability::UseOnOff(Game_Manager* gm_, Player* player_)
{
	if(isUsing())
	{
		UnUse(gm_,player_);
		return false;
	}
	else
	{
		Use(gm_,player_);
		return true;
	}
}
int Ability::Possible(Player* player_)
{
	if(player_->GetLevel()<need_level)
		return 0;


	//이미 사용능력을 1개 배웠을 경우
	if(GetType() == AT_USE)
	{
		for(vector<Ability*>::iterator it = player_->abil_list.begin(); it != player_->abil_list.end(); it++)
		{
			if((*it)->GetType() == AT_USE && strcmp((*it)->GetName(),GetName()))
			{
				return 0;
			}
		}
	}


	//여기는 필요한 능력이 존재하는지
	if(!need_abil.empty())
	{
		for(vector<abil_level>::iterator it = need_abil.begin(); it != need_abil.end(); it++)
		{
			bool need_ = false;
			for(vector<Ability*>::iterator it2 = player_->abil_list.begin(); it2 != player_->abil_list.end(); it2++)
			{
				if(!strcmp(it->name.c_str(),(*it2)->GetName()))
				{
					if(it->level <= (*it2)->GetLevel())
					{
						need_ = true;
						break;
					}
				}
			}
			if(!need_)
				return 0;
		}
	}

	//있어서안될능력이 존재하는지
	if(!oppose_abil.empty())
	{
		for(vector<Ability*>::iterator it = player_->abil_list.begin(); it != player_->abil_list.end(); it++)
		{
			for(vector<abil_level>::iterator it2 = oppose_abil.begin(); it2 != oppose_abil.end(); it2++)
			{
				if(!strcmp(it2->name.c_str(),(*it)->GetName()))
				{
					if(it2->level <= (*it)->GetLevel())
					{
						return 0;
					}
				}
			}
		}
	}

	for(vector<Ability*>::iterator it = player_->abil_list.begin(); it != player_->abil_list.end(); it++)
	{
		if(!strcmp(GetName(),(*it)->GetName()))
		{
			if((*it)->GetLevel() >= max_level)
			{
				return 0;
			}
			return (*it)->GetLevel()+1;
		}	
	}

	return 1;
}