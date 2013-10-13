//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_bug_ant_lion.cpp
//
// 내용: 개미지옥. 플레이어를 빨아들인다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_bug_ant_lion.h"

#include "texture_list.h"
#include "gamemanager.h"
#include "shot_virus_shot.h"
#include "image.h"
#include "map.h"

Mon_bug_ant_lion::Mon_bug_ant_lion(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
tongue_delay(0), tongue()
{

}
Mon_bug_ant_lion::~Mon_bug_ant_lion()
{

}
bool Mon_bug_ant_lion::charDraw(Game_Manager* gm_, coord_def offset, float size_)
{
	if(tongue.state)
	{
		coord_def temp_pos = GetPos();
		coord_def step = (tongue.pos - GetPos())/10.0f;
		for(int i =0 ; i<10 ; i++)
		{
			temp_pos += step;
			tex_gun.Draw((temp_pos.x-offset.x)*size_, (temp_pos.y-offset.y)*size_,3.0f*size_,0);
		}
		tex_gun.Draw((tongue.pos.x-offset.x)*size_, (tongue.pos.y-offset.y)*size_,5.0f*size_,0);
	}
	float size__ = GetFlySize();
	if(GetTexture())
		return GetTexture()->Draw((GetX()-offset.x)*size_, (GetY()-offset.y)*size_, size_*size__, size_*size__, GetAngle(), D3DCOLOR_ARGB(GetAlpha(gm_),255,255,255));
	return false;
}
bool Mon_bug_ant_lion::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num )
{
	if(GetShotStop())
		return false;
	if(!GetDelay())
	{
		if(!tongue_delay)
		{
			tongue.state = 1;
			tongue.speed = 3;
			tongue.angle = GetAngleToTarget(GetPos(), c);
			tongue.pos = GetPos();
			tongue.count = 50;



			tongue_delay = 150;
		}
		else
		{
			Monster::Shot(gm_, c, focus_);
		}
		return true;
	}
	return false;
}
bool Mon_bug_ant_lion::TargetLost()
{
	bool ok_=false;
	if(ai->TargetLost())
		ok_ = true;
	if(tongue.target && !tongue.target->isLive())
	{
		tongue.target = NULL;
		tongue.state = 2;
		ok_ = true;
	}
	return ok_;

}


bool Mon_bug_ant_lion::Special_Action(Game_Manager* gm_)
{
	if(tongue.state == 1 || tongue.state == 2)
	{
		float angle_ = (tongue.state == 1)?tongue.angle:GetAngleToTarget(tongue.pos, GetPos());
		tongue.pos.x += cos(angle_)*tongue.speed;
		tongue.pos.y += sin(angle_)*tongue.speed;

		SetStop(2);
		SetAngleStop(2);

		for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
		{
			if((*it)->isLive() && !(*it)->isNonTarget()  && GetTeam() != (*it)->GetTeam())
			{
				if(distan_coord(tongue.pos, (*it)->GetPos()) < 8.0f)
				{
					tongue.state = 3;	
					tongue.target = (*it);
					tongue.count = 100;	
					break;
				}
			}
		}


		if(tongue.state == 1)
		{
			if(gm_->map->CollutionPos((int)tongue.pos.x, (int)tongue.pos.y) || !(tongue.count--))
			{
				tongue.state = 2;

			}
		}
		else if(tongue.state == 2 && distan_coord(tongue.pos, GetPos()) < 3.0f)
		{
			tongue.state = 0;
		}
	}
	else if(tongue.state == 3)
	{	
		SetStop(2);
		SetAngleStop(2);

		if(tongue.target)
		{
			tongue.pos = tongue.target->GetPos();
			tongue.target->SetKnockback(0.7f, 2.0f, GetAngleToTarget(tongue.pos, GetPos()));
			if(distan_coord(tongue.pos, GetPos()) < GetSize()+tongue.target->GetSize()+3.0f)
			{
				tongue.state = 0;
			}
			if(tongue.count-- <= 0)
				tongue.state = 0;
		}
		else
		{
			tongue.state = 2;
		}	

	}
	else if(tongue_delay)
	{
		tongue_delay--;
	}
	return true;
}