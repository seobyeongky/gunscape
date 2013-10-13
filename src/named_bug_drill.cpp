//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_bug_drill.cpp
//
// 내용: 비행충
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <d3dx9.h>
#include <math.h>
#include "named_bug_drill.h"
#include "ai_fly_bug.h"
#include "texture_list.h"

#include "image.h"
#include "random.h"
#include "gamemanager.h"
#include "map.h"
#include "effect_message.h"
#include "effect_piece.h"
#include "shot_bug.h"


Named_bug_drill::Named_bug_drill(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
fly_speed(GetSpeed_Pure()), fly_angle(0),
count(1), accel(0), drill_delay(0), drill_count(0), driil_pos()
{

}
Named_bug_drill::~Named_bug_drill()
{

}
void Named_bug_drill::SetAi(monster_state state_, Unit* head_, int level_)
{
	if(!ai)
	{
		ai = new Ai_Fly_bug(state_, this, head_, level_);
	}

}

bool Named_bug_drill::charDraw(Game_Manager* gm_, coord_def offset, float size_)
{
	//float size__ = GetFlySize();
	//if(GetTexture())
	//	return GetTexture()->Draw((GetX()-offset.x)*size_, (GetY()-offset.y)*size_, size_*size__, size_*size__, fly_angle, D3DCOLOR_ARGB((GetFly()?GetAlpha(gm_):GetAlpha(gm_)/2),255,255,255));
	return false;
}

bool Named_bug_drill::Action_in(Game_Manager* gm_)
{
	if(!isLive())
	{
		DropItem(gm_);
		return true;
	}
	if(drill_count)
	{
		drill_count--;
		if(drill_count%5==0)
			Effect_dust(gm_, GetPos(), 2,  1.5f, 0.5f);
		if(drill_count == 0)
		{
			float dis2_ = distan_coord(GetPos(), driil_pos);
			Fly(gm_, driil_pos, (int)(dis2_/1.5f));
			for(int i =0;i<6;i++)
			{
				gm_->unit_list.push_back(new Shot_bug(i==0?&tex_mon_bug_drill_head:(i!=5?&tex_mon_bug_drill_body:&tex_mon_bug_drill_tail), this, 15,GetPos(), driil_pos, (int)(dis2_/1.5f), GetTeam(),(i)*20));
			}
			drill_delay = 300;
		}
	}
	else
	{
		if(GetWarning()>0)
			UpDownWarning(-5);
		if(ai)
		{
			if(!GetFly())
			{
				if(ai->GetState() == MS_NORMAL)
				{			
					ai->Noise(coord_def((float)rand_int(0,gm_->map->GetWidth()),(float)rand_int(0,gm_->map->GetHeight())));
				}
				ai->Action();
			}	
		}
		
		if(drill_delay)
			drill_delay--;
		
		
		
		count--;
		fly_speed+=accel;
		if(count<=0)
		{
			count = rand_int(50, 200);
			accel = (rand_float(0.5f,2.0f) - fly_speed)/count;
		}
	}
	CommonAction(gm_);
	return false;
}

int Named_bug_drill::UnitMove(Game_Manager* gm_, float speed_, float angle_)
{
	fly_angle+=(sin(angle_-fly_angle)>0)?0.03f:-0.03f;


	float x_ = cos(fly_angle)*fly_speed;
	float y_ = sin(fly_angle)*fly_speed;

	Move(GetX()+x_,GetY()+y_);

	return 0;
}
int Named_bug_drill::UnitSlipMove(Game_Manager* gm_, float speed_, float angle_)
{
	UnitMove(gm_,speed_,angle_);
	for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
	{
		if((*it)->isLive() && !(*it)->isNonTarget()  && GetTeam() != (*it)->GetTeam())
		{
			if(GetSize()+(*it)->GetSize() > distan_coord(GetPos(), (*it)->GetPos()))
			{
				return 1;
			}
		}
	}
	return 0;
}
bool Named_bug_drill::isCollution()
{
	return false;
}


//void Named_bug_drill::Approach(Game_Manager* gm_, coord_def c, Unit* target_)
bool Named_bug_drill::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num )
{
	if(!drill_delay && !GetDelay() && !nonmove_delay && !drill_count)
	{
		
		float dis_ = distan_coord(GetPos(), c);
		if(dis_<30 || dis_>60)
		{
			drill_delay = 50;
			return false;	
		}

		coord_def start = GetPos();
		int ii=0;
		for(ii=0;ii<10;ii++)
		{
			float angle__ = rand_float(0,D3DX_PI*2);
			float range__ = rand_float(0,50.0f);
			coord_def c_p_ = coord_def(cos(angle__)*range__, sin(angle__)*range__);
			int i=-1;
			int j=-1;
			for(i=-1;i<=1;i++){
				for(j=-1;j<=1;j++){
					if(!i || !j){
						if(gm_->map->CollutionPos((int)(start.x + c_p_.x+i*3),(int)(start.y + c_p_.y+j*3)))
						{
							i=3;
							j=3;
						}
					}
				}
			}
			if(i == 2 && j == 2)
			{
				start += c_p_;
				break;
			}
		}
		if(ii == 10)
		{
			drill_delay = 50;
			return false;	
		}

		Move(start.x, start.y);
		
		float dis2_ = 0;
		coord_def goal_ = c;
		for(ii=0;ii<7;ii++)
		{
			dis2_ = distan_coord(GetPos(), c)+60.0f-ii*10;
			float angle_ = GetAngleToTarget(GetPos(), c);

			goal_ = GetPos()+coord_def(cos(angle_)*dis2_, sin(angle_)*dis2_);
			
			float angle__ = rand_float(0,D3DX_PI*2);
			float range__ = rand_float(0,30.0f);
			coord_def c_p_ = coord_def(cos(angle__)*range__, sin(angle__)*range__);
			
			int i=-1;
			int j=-1;
			for(i=-1;i<=1;i++){
				for(j=-1;j<=1;j++){
					if(!i || !j){
						if(gm_->map->CollutionPos((int)(goal_.x + c_p_.x+i*3),(int)(goal_.y + c_p_.y+j*3)))
						{
							i=3;
							j=3;
						}
					}
				}
			}
			if(i == 2 && j == 2)
			{
				goal_ += c_p_;
				break;
			}
		}
		if(ii == 10)
		{
			drill_delay = 50;
			return false;	
		}
		
		float angle22_ = GetAngleToTarget(GetPos(), goal_);
		dis2_ = distan_coord(GetPos(), goal_);
		if(dis2_ < 50)
		{
			drill_delay = 50;
			return false;	
		}

		SetAngle(angle22_);
		fly_angle = angle22_;

		drill_count = 20;
		driil_pos = goal_;
	}
	return true;	
}

bool Named_bug_drill::Melee(Game_Manager* gm_)
{
	return false;
}