//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: unit.cpp
//
// 내용: 유닛클래스 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "unit.h"
#include "image.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "map.h"
#include "random.h"
#include "player.h"
#include "map.h"
#include "effect_piece.h"
#include "d3dx_class.h"
#include "effect_message.h"
#include "debug.h"



//Unit::Unit():
//texture(NULL), pos(0, 0), angle(0), size(3.0f), team(0)
//{
//
//}


Unit::Unit(string name_, Texture* texture_, float x_, float y_, int team_, int max_hp_):
name(name_), texture(texture_), pos(x_, y_), angle(rand_float(0,D3DX_PI*2)), move_angle(angle), 
size(3.0f), team(team_), frame(0), hp(max_hp_), max_hp(max_hp_), 
sight(200.0f), sight_width(0.3f), delay(0), max_delay(0), focus(0.0f), speed(1.0f), 
invisible_temp(-1), invisible(0), none_move_count(0), slow(0), bsk_slow(0), atk_apply(1.0f), atk_spd_apply(1.0f),
back_panalty(1.0f), net(0), melee_knock_back(1.0f), blind(0), fog_resist(false),stop(0),angle_stop(0),
fixed(false), immortal(false), warning(0), fog_slow(0), house_in(0), invincible(0), shot_stop(0),poison_damage(0),poison_turn(0),poison_unit(NULL),
x_speed(0.0f), y_speed(0.0f),x_slip(0),	
y_slip(0), slip_count(0), fly()
{
	for(int i = 0; i < DT_MAX ; i++)	
		defense[i] = 1.0f;
	for(int i = 0; i < DT_MAX ; i++)	
		def_resist[i] = false;
	
	for(int i = 0; i < VT_MAX-1 ; i++)	
	{
		for(int j = 0; j < DT_MAX-1 ; j++)	
		{
			vamp[i][j] = 0.0f;
		}
	}
	for(int i = 0; i < VT_MAX-1 ; i++)
		sneak[i] = 1.0f;


	for(int i = 0; i < 8 ; i++)
		detection_player[i] = 0;
}
Unit::~Unit()
{
}


void Unit::Move(float x_, float y_)
{
	if(net)
		return;
	if(fixed && !fly.fly)
		return;
	pos.x = x_;
	pos.y = y_;
}


bool Unit::charDraw(Game_Manager* gm_, coord_def offset, float size_)
{
	float size__ = GetFlySize();
	if(texture)
		return texture->Draw((pos.x-offset.x)*size_, (pos.y-offset.y)*size_, size_*size__, size_*size__, angle, D3DCOLOR_ARGB(GetAlpha(gm_),255,255,255));
	return false;
}
bool Unit::Draw(Game_Manager* gm_, coord_def offset, float size_)
{
	if(!isLive())
		return false;

	if(gm_->GetMonSightView() && !isNonLife() && (Unit*)gm_->player != this && !isSleep() && isViewName())
	{
		//시야선 그리기
		float dis_ = distan_coord(GetPos(),gm_->player->GetPos());
		if(dis_ < gm_->player->GetView())
		{
			for(int i=-1;i<=1;i+=2)
			{
				float angle_ = angle+sight_width*i;
				coord_def sight_pos = GetPos()+coord_def(cos(angle_)*sight,sin(angle_)*sight);
				int len_ = gm_->map->CollutionPosToPos(GetPos(), sight_pos);
				if(len_)
				{
					sight_pos = GetPos()+coord_def(cos(angle_)*len_,sin(angle_)*len_);
				}
				tex_gun.Draw(((GetPos().x+sight_pos.x)/2-offset.x)*size_, ((GetPos().y+sight_pos.y)/2-offset.y)*size_, distan_coord(GetPos(),sight_pos)*size_, size_ , angle_ , D3DCOLOR_ARGB(GetAlpha(gm_)/2,255,100,100));
			}
			if(isBackStabbing() && gm_->player->GetBackStabDamage()>=GetHp())
			{
				tex_backstab.Draw((pos.x-offset.x)*size_,(pos.y-offset.y)*size_,size_, size_, frame/50.0f, D3DCOLOR_ARGB(GetAlpha(gm_)/4,255,100,100));
			}
		}
	}


	charDraw(gm_, offset, size_);

	if(net && isViewName())
		tex_net_cap.Draw((pos.x-offset.x)*size_, (pos.y-offset.y)*size_, size_, size_, 0.0f, D3DCOLOR_ARGB(GetAlpha(gm_)/2,255,255,255));
	if(poison_turn && isViewName())
		tex_poison.Draw((pos.x-offset.x)*size_, (pos.y-offset.y)*size_, size_, size_, 0.0f, D3DCOLOR_ARGB(GetAlpha(gm_),255,255,255));
	
	if(gm_->GetStateView() && !isNonLife() && (Unit*)gm_->player != this && isViewName())
	{
		float y_ = pos.y-offset.y-10;
		switch(GetState())
		{
		case MS_NORMAL:
			{
				if(!warning)
					tex_emotion_normal.Draw((pos.x-offset.x)*size_, y_*size_, size_, size_, 0.0f, D3DCOLOR_ARGB(GetAlpha(gm_)/2,255,255,255));
				else
					tex_emotion_doubt.Draw((pos.x-offset.x)*size_, y_*size_, size_, size_, 0.0f, D3DCOLOR_ARGB(GetAlpha(gm_)/2,255,255,255));
			}
			break;
		case MS_SLEEP:
			tex_emotion_sleep.Draw((pos.x-offset.x)*size_, y_*size_, size_, size_, 0.0f, D3DCOLOR_ARGB(GetAlpha(gm_)/2,255,255,255));
			break;
		case MS_SEARCH:
			tex_emotion_search.Draw((pos.x-offset.x)*size_, y_*size_, size_, size_, 0.0f, D3DCOLOR_ARGB(GetAlpha(gm_)/2,255,255,255));
			break;
		case MS_ATTACK:
			tex_emotion_attack.Draw((pos.x-offset.x)*size_, y_*size_, size_, size_, 0.0f, D3DCOLOR_ARGB(GetAlpha(gm_)/2,255,255,255));
			break;
		default:
			break;
		}
	}


	return true;
}
bool Unit::NameDraw(Game_Manager* gm_, coord_def offset, float size_)
{
	if( isNamed() && !isNonLife() && isViewName())
	{
		float w_ = gm_->direct->GetWR();
		float h_ = gm_->direct->GetHR();

		//시간되면 폰트도 확대
		LONG x_ = (LONG)(((pos.x-((LONG)offset.x))*size_+300)*w_);
		LONG y_ = (LONG)(((pos.y-((LONG)offset.y))*size_+200)*h_);
		RECT rc = {(LONG)(x_-100*w_*size_),(LONG)(y_-15*h_*size_),(LONG)(x_+100*w_*size_),(LONG)(y_-15*h_*size_)};
		gm_->direct->GetFont()->DrawTextA(NULL, name.c_str(), -1, &rc, DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(GetAlpha(gm_),0,0,255));
	}
	return true;
}


bool Unit::Action(Game_Manager* gm_)
{
	bool return_ = Action_in(gm_);


	if(fly.fly)
	{
		Move(GetPos().x + fly.fly_speed.x, GetPos().y + fly.fly_speed.y);
		fly.fly_speed += fly.fly_acc;
		fly.fly--;
	}



	if(invisible_temp != -1)
	{
		invisible = invisible_temp;
	}
	invisible_temp = -1;

	for(list<speed_apply>::iterator it = speed_list.begin();it!=speed_list.end();)
	{
		if(it->turn>0)
		{
			it->turn--;
			it++;
		}
		else
		{
			list<speed_apply>::iterator temp = it;
			it++;
			speed_list.erase(temp);
		}
	}
	for(list<attack_apply>::iterator it = attack_list.begin();it!=attack_list.end();)
	{
		if(it->turn>0)
		{
			it->turn--;
			it++;
		}
		else
		{
			list<attack_apply>::iterator temp = it;
			it++;
			attack_list.erase(temp);
		}
	}
	
	for(list<attack_speed_apply>::iterator it = attack_speed_list.begin();it!=attack_speed_list.end();)
	{
		if(it->turn>0)
		{
			it->turn--;
			it++;
		}
		else
		{
			list<attack_speed_apply>::iterator temp = it;
			it++;
			attack_speed_list.erase(temp);
		}
	}
	


	frame++;

	return return_;
}

void Unit::CommonAction(Game_Manager* gm_)
{
	if(net)
		net--;

	if(blind)
		blind--;

	if(stop)
		stop--;
	if(angle_stop)
		angle_stop--;
	if(fog_slow)
		fog_slow--;
	if(house_in)
		house_in--;
	if(invincible)
		invincible--;
	if(shot_stop>0)
		shot_stop--;
	if(poison_turn)
		poison_turn--;
	if(poison_turn%30 == 1)
	{
		int final_damge_ = SetDamage(gm_, poison_unit?poison_unit->GetPos():GetPos(), DT_POISON, poison_damage, poison_unit?poison_unit->GetTeam():0);
		if(poison_unit)
			poison_unit->GiveDamage(gm_, this, DT_POISON, final_damge_);
	}


	
	none_move_count++;

	for(int i = 0 ; i < 8 ; i++)
	{
		if(detection_player[i]>0)
		{
			detection_player[i]--;
		}
	}
	Friction(gm_);
	if(GetDelay())
		UpDownDelay(-1);
	if(GetSlow())
		UpDownSlow(-1);
	if(GetBskSlow())
		UpDownBskSlow(-1);
}
void Unit::Death(Game_Manager* gm_)
{

}

float Unit::GetFlySize()
{
	return (!fly.fly)?1.0f:(1.0f+sin(fly.fly*D3DX_PI/fly.fly_time));
};
float Unit::GetSightPenalty(Unit* enemy)
{
	float penalty_ = enemy->GetSneak(GetKind());
	penalty_ *= enemy->GetSneak(VT_ALL);
	return penalty_;
}
float Unit::GetFocusSum()
{
	return focus+(slow?0.2f:0.0f);
}
int Unit::GetAlpha(Game_Manager* gm_)
{
	float percent_ =  1.0f;
	if(gm_->player->GetTeam() > 0 && gm_->player->GetTeam() <= 8)
	{
		int detec_ = max(0,detection_player[gm_->player->GetTeam()-1] - 20);
		percent_ = (200 - detec_)/200.0f;

	}
	return (int)(255- (GetInvisible()*percent_/(gm_->player->GetTeam()==GetTeam()?2:1)));
}
float Unit::GetAtkApply()
{
	float panalty_ = 1;
	for(list<attack_apply>::iterator it = attack_list.begin();it!=attack_list.end();it++)
	{
		panalty_ *= it->ratio;
	}
	return atk_apply*panalty_;
}
float Unit::GetAtkSpdApply()
{	
	float panalty_ = 1;
	for(list<attack_speed_apply>::iterator it = attack_speed_list.begin();it!=attack_speed_list.end();it++)
	{
		panalty_ *= it->ratio;
	}
	return atk_spd_apply*panalty_;
}
float Unit::GetSpeed(float angle_)
{
	float panalty_ = cos(angle_ - angle)/5*back_panalty+(1-0.20f*back_panalty);
	
	for(list<speed_apply>::iterator it = speed_list.begin();it!=speed_list.end();it++)
	{
		panalty_ *= it->ratio;
	}
	panalty_ *= GetPlayerSpeed(angle_);
	return speed*(fog_slow?0.5f:1.0f)*(bsk_slow?0.5f:1.0f)*(slow?(1.0f-0.5f*melee_knock_back):1.0f)*panalty_;
}
int Unit::SetDamage(Game_Manager* gm_, coord_def c, Damage_Type type_, float damage_, int team_, float sniper_, int critical_)
{
	if(GetInvincible())
		return 0;





	if(team_ == GetTeam())
	{
		damage_ *= defense[DT_SELF_EXPLOSION];
		if(def_resist[DT_SELF_EXPLOSION])
			damage_ = 0;
	}
	damage_ *= defense[DT_ALL];
	if(def_resist[DT_ALL])
		damage_ = 0;
	damage_ = (damage_*defense[type_]);
	if(def_resist[type_])
		damage_ = 0;

	
	bool backstab_ok_ = false;
	if(critical_ && critical_>rand_int(0,99))
	{
		backstab_ok_ = true;
	}
	if(sniper_ != 1.0f && backstab_ok_)
	{
		damage_ *= sniper_;
		Effect_simple_speak(gm_,"헤드샷!",GetPos());
		backstab_ok_ = true;
	}
	else
		backstab_ok_ = false;



	int final_damage_ = (int)(damage_+rand_float(0,0.99f));

	if(!isNonLife() && final_damage_ && !isNonTarget())
		Effect_blood(gm_, GetPos(), (int)(damage_/5+1), 1.0f);

	hp-=final_damage_;
	if(immortal && hp<1)
	{
		hp = 1;
	}
	if(!isLive())
		Death(gm_);
	return final_damage_;
}
void Unit::GiveDamage(Game_Manager* gm_, Unit* unit_, Damage_Type type_, int damage_)
{
	float vamp_ = GetVamp(unit_->GetKind(),type_);
	if(vamp_>0)
	{
		int heal_ = (int)(damage_*vamp_+rand_float(0,0.99f));
		if(heal_>0)
			Heal(heal_);
	}
}
int Unit::SetDelay(float delay_)
{
	if(delay_ < 0)
		return -1;
	
	if(delay_ && delay > delay_)
		return delay;

	delay = (int)(delay_+rand_float(0,0.99f)); 
	if(delay<1)
		delay = 1;
	max_delay = delay;
	return delay;
};
void Unit::SetInvisible(int invisible_)
{
	invisible_temp = max(invisible_, invisible_temp);
}
void Unit::SetKnockback(float power_, float max_power_, float angle_)
{
	x_speed+= cos(angle_)*power_;
	y_speed+= sin(angle_)*power_;

	power_ = sqrt(x_speed*x_speed+y_speed*y_speed);

	if(power_ > max_power_)
	{
		x_speed*= max_power_/power_;
		y_speed*= max_power_/power_;
	}
}


void Unit::ApplySneak(Vamp_Type type_, float ratio_)
{
	if(type_)
	{
		sneak[type_-1] *= ratio_;
	}
	else
	{
		for(int i = 0; i < VT_MAX-1 ; i++)	
		{
			sneak[i] *= ratio_;
		}
	}
}

void Unit::ApplyDefense(Damage_Type type_, float ratio_)
{
	defense[type_] *= ratio_;
}
void Unit::UpDownVamp(Vamp_Type type_, Damage_Type type2_, float updown_)
{
	if(type_ && type2_)
		vamp[type_-1][type2_-1] += updown_;


	for(int i = 0; i < VT_MAX-1 ; i++)	
	{
		if(!type_ || i == type_-1)
		{
			for(int j = 0; j < DT_MAX-1 ; j++)	
			{
				if(!type2_ || j == type2_-1)
				{
					vamp[i][j] += updown_;
				}
			}
		}
	}
}


void Unit::Insight(Game_Manager* gm_, Player* player_, bool speed_)
{
	if(player_->GetTeam()>0 && player_->GetTeam()<=8)
	{
		if(speed_ && detection_player[player_->GetTeam()-1]< 20)
			detection_player[player_->GetTeam()-1] = 20;
		if(detection_player[player_->GetTeam()-1]<=120)
			detection_player[player_->GetTeam()-1]+=3;
	}
}

void Unit::SlowApply(float ratio_, int turn_, Speed_kind kind_)
{
	if(kind_ != SK_NONE)
	{
		for(list<speed_apply>::iterator it=speed_list.begin();it!=speed_list.end();it++)
		{
			if(it->kind == kind_)
			{
				if(abs(1.0f-it->ratio) < abs(1.0f-ratio_))
					it->ratio = ratio_;
				if(it->turn < turn_)
					it->turn  = turn_;
				return;
			}
		}
	}
	speed_list.push_back(speed_apply(ratio_,turn_,kind_));
}

void Unit::AttackApply(float ratio_, int turn_, Attack_buff_kind kind_)
{
	if(kind_ != SK_NONE)
	{
		for(list<attack_apply>::iterator it=attack_list.begin();it!=attack_list.end();it++)
		{
			if(it->kind == kind_)
			{				
				if(kind_ >= ABK_STACK_OK)
					it->ratio *= ratio_;
				else if(abs(1.0f-it->ratio) < abs(1.0f-ratio_))
				{
					it->ratio = ratio_;
				}
				if(it->turn < turn_)
					it->turn  = turn_;
				return;
			}
		}
	}
	attack_list.push_back(attack_apply(ratio_,turn_,kind_));
}
void Unit::AttackSpeedApply(float ratio_, int turn_, Attack_buff_kind kind_)
{
	if(kind_ != SK_NONE)
	{
		for(list<attack_speed_apply>::iterator it=attack_speed_list.begin();it!=attack_speed_list.end();it++)
		{
			if(it->kind == kind_)
			{				
				if(kind_ >= ABK_STACK_OK)
					it->ratio *= ratio_;
				else if(abs(1.0f-it->ratio) < abs(1.0f-ratio_))
				{
					it->ratio = ratio_;
				}
				if(it->turn < turn_)
					it->turn  = turn_;
				return;
			}
		}
	}
	attack_speed_list.push_back(attack_speed_apply(ratio_,turn_,kind_));
}


int Unit::UnitMove(Game_Manager* gm_, float speed_, float angle_)
{
	float x_ = cos(angle_)*speed_;
	float y_ = sin(angle_)*speed_;
	int move_ = 0;

	if(stop)
		return 0;

	move_ =isCollutionX(gm_, x_);
	if(move_==0)
	{
		Move(GetX()+x_,GetY());
		InitNoneMoveCount();	 
	}

	int temp = isCollutionY(gm_, y_);;
	if(temp==0)
	{
		Move(GetX(),GetY()+y_);
		InitNoneMoveCount();
	}
	else if(!move_ || temp < move_)
		move_ = temp;

	return move_;
}
int Unit::UnitSlipMove(Game_Manager* gm_, float speed_, float angle_)
{	
	float x_ = cos(angle_)*speed_;
	float y_ = sin(angle_)*speed_;
	int x_move = isCollutionX(gm_, x_);
	int y_move = isCollutionY(gm_, y_);
	
	if(stop)
		return 0;
	
	if(!x_move && !y_move) //그냥 이동가능
	{
		x_slip=0;
		y_slip=0;
		slip_count=0;
		Move(GetX()+x_,GetY()+y_);
		return 0;
	}
	else if(!x_move && y_move &&  y_move < 2) //X축으로 움직이고 Y축은 막혔을때
	{
		if(!x_slip)
		{
			angle_ = x_>=0?0:D3DX_PI;
			x_slip = x_>=0?1:-1;
		}
		else
		{
			angle_ = x_slip>=0?0:D3DX_PI;
			if(isCollutionX(gm_, cos(angle_)*speed_) == -1)
			{
				x_move *= -1;
				slip_count++;
				if(slip_count == 4)
					return -1;
			}
		}
	}
	else if(x_move && x_move < 2 && !y_move) //Y축으로 움직이고 X축은 막혔을때
	{
		if(!y_slip)
		{
			angle_ = y_>=0?D3DX_PI/2.0f:D3DX_PI*3.0f/2.0f;
			y_slip = y_>=0?1:-1;
		}
		else
		{
			angle_ = y_slip>=0?D3DX_PI/2.0f:D3DX_PI*3.0f/2.0f;
			if(isCollutionY(gm_, sin(angle_)*speed_) == -1)
			{
				y_slip *= -1;
				slip_count++;
				if(slip_count == 4)
					return -1;
			}
		}
	}
	else if(y_move && x_move) //전부 이동불가
	{
		if(x_move >= 1 || y_move >= 1) //둘중하나라도 몹과의 충돌시
			return 1; //몹 충돌에 의한 이동불가
		slip_count++;
		if(slip_count==4)
			return -1; //아닐땐 벽충돌에 의한 이동불가. 이 경우 아예 이동이 불가능한 상태임을 체크
		else
		{
			UnitMove(gm_, speed_, angle_-D3DX_PI);
			if(x_slip)
			{
				angle_ = x_slip>=0?0:D3DX_PI;
			}
			else if(y_slip)
			{
				angle_ = y_slip>=0?D3DX_PI/2.0f:D3DX_PI*3.0f/2.0f;
			}
			x_slip *= -1;
			y_slip *= -1;
		}
	}
	else
	{
		if(!x_move)
			Move(GetX()+x_,GetY());
		if(!y_move)
			Move(GetX(),GetY()+y_);
		return 0;
	}


	UnitMove(gm_, speed_, angle_);
	return 0;
}

int Unit::isCollutionX(Game_Manager* gm_, float move_)
{
	if(!isCollution())
	{
		if(gm_->map->CollutionMap(GetPos(),  (int)GetSize()))
			return -1;
		return 0;
	}
	if(move_ && !gm_->map->CollutionX(GetX(),coord_def(GetX()+move_,GetY()), GetSize()))
	{	
		for(list<Unit*>::iterator it = gm_->unit_list.begin(); it != gm_->unit_list.end(); it++)
		{
			if((*it) != this && (*it)->isLive() && !(*it)->isNonTarget()  && (*it)->isCollution() && (((*it)->GetX() > pos.x) ^ (move_ < 0)))
			{
				if((*it)->collution(pos, size))
				{
					(*it)->SetKnockback(abs(move_/2), 2.0f, GetAngleToTarget(pos, (*it)->GetPos()));
					return (*it)->GetTeam() != GetTeam()?2:1; //팀이 같으면 1 틀리면 2
				}
			}
		}
		return 0;
	}
	return -1;
}
int Unit::isCollutionY(Game_Manager* gm_, float move_)
{	
	if(!isCollution())
	{
		if(gm_->map->CollutionMap(GetPos(), (int)GetSize()))
			return -1;
		return 0;
	}
	if(move_ && !gm_->map->CollutionY(GetY(),coord_def(GetX(),GetY()+move_), GetSize()))
	{	
		for(list<Unit*>::iterator it = gm_->unit_list.begin(); it != gm_->unit_list.end(); it++)
		{
			if((*it) != this && (*it)->isLive() && !(*it)->isNonTarget()  && (*it)->isCollution() && (((*it)->GetY() > pos.y) ^ (move_ < 0)))
			{
				if((*it)->collution(pos, size))
				{
					(*it)->SetKnockback(abs(move_/2), 2.0f, GetAngleToTarget(pos, (*it)->GetPos()));
					return (*it)->GetTeam() != GetTeam()?2:1; //팀이 같으면 1 틀리면 2
				}
			}
		}
		return 0;
	}
	return -1;
}

bool Unit::collution(coord_def pos_, float radius_)
{
	float x_ = pos_.x - pos.x, y_ = pos_.y - pos.y, r_ = radius_+size;
	return (x_*x_ + y_*y_ <= r_*r_);
}

void Unit::Friction(Game_Manager* gm_)
{
	if(x_speed)
	{
		if(!isCollutionX(gm_, x_speed))
		{
			Move(GetX()+x_speed,GetY());
		}
		x_speed*= 0.8f;
		if(abs(x_speed)<0.1f)
			x_speed = 0;
	}
	if(y_speed)
	{
		if(!isCollutionY(gm_, y_speed))
		{
			Move(GetX(),GetY()+y_speed);
		}
		y_speed*= 0.8f;
		if(abs(y_speed)<0.1f)
			y_speed = 0;
	}
}
bool Unit::TargetLost_unit()
{
	if(poison_unit && !poison_unit->isLive())
		poison_unit = NULL;
	TargetLost();
	return true;
}
bool Unit::Fly(Game_Manager* gm_, coord_def c, int time_)
{
	if(!fly.fly)
	{
		float dis_ = distan_coord(GetPos(), c);
		float angle_ = GetAngleToTarget(GetPos(), c);
		//coord_def speed_pos_ = coord_def(cos(angle_), sin(angle_))*GetSpeed_Pure();

		fly.fly_speed = (c - GetPos())*2.0f/(float)time_;
		fly.fly_acc = -fly.fly_speed/(float)time_;

		//fly_acc =  speed_pos_*speed_pos_*2.0f/3.0f/dis_;
		//fly_speed = fly_acc * dis_ / speed_pos_;
		fly.fly_time = time_;
		fly.fly = time_;
		return true;
	}
	return false;
}