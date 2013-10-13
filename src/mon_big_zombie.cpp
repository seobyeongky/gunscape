//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mon_big_zombie.cpp
//
// 내용: 돌을 던진다. 아니면 몹을!
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "mon_big_zombie.h"

#include <math.h>
#include "texture_list.h"
#include "gamemanager.h"
#include "shot_rock.h"
#include "random.h"
#include "image.h"

Mon_big_zombie::Mon_big_zombie(monster_infor& infor_, float x_, float y_, int team_, int time_):
Monster(infor_, x_, y_, team_, time_),
throws(true), count(0), throw_count(0), frame(0)
{
	SetTargetContinue(-1);

}
Mon_big_zombie::~Mon_big_zombie()
{

}

bool Mon_big_zombie::Shot(Game_Manager* gm_, coord_def c, float focus_, int item_num)
{
	if(GetStop())
		return false;
	if(GetShotStop())
		return false;
	if(!GetDelay())
	{
		frame++;


		if(throws)
		{			
			int plus_sec_ = (int)(distan_coord(GetPos(),c)/2);
			if(plus_sec_>20)
			{				
				if(Throw(gm_, c))
				{
					throws = false;
					count = 150;
					SetDelay(50.0f);
				}
				else
				{
					float angle__ = rand_float(0,D3DX_PI*2);
					float range__ = rand_float(0,35.0f);
					c += coord_def(cos(angle__)*range__, sin(angle__)*range__);
					gm_->shot_list.push_back(new Shot_rock(&tex_rock, this, 20+plus_sec_, 30, 4, 2.0f, 2.0f, 15, true, GetTeam(), GetPos(), c));
					throws = false;
					count = 150;
					SetDelay(50.0f);
				}
			}
			else
			{
				throws = false;
				count = 80;
			}
		}
		else
		{
			Monster::Shot(gm_, c, focus_);
		}
		return true;
	}
	return false;
}



bool Mon_big_zombie::Special_Action(Game_Manager* gm_)
{
	if(throw_count)
		throw_count--;
	
	if(count)
	{
		count--;
		if(count <= 0)
			throws = true;
	}
	return true;
}

bool Mon_big_zombie::Throw(Game_Manager* gm_, coord_def c)
{
	for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
	{
		if((*it)->isThrowable())
		{
			if(!(*it)->isPlayer())
			{
				if((*it)->collution(GetPos(), 30.0f))
				{
					if(!gm_->map->CollutionPosToPos(GetPos(), (*it)->GetPos()))
					{
						while(1)
						{
							float angle__ = rand_float(0,D3DX_PI*2);
							float range__ = rand_float(0,35.0f);
							coord_def c_p_ = coord_def(cos(angle__)*range__, sin(angle__)*range__);
							int i=-1;
							int j=-1;
							for(i=-1;i<=1;i++){
								for(j=-1;j<=1;j++){
									if(!i || !j){
										if(gm_->map->CollutionPos((int)(c.x + c_p_.x+i*3),(int)(c.y + c_p_.y+j*3)))
										{
											i=3;
											j=3;
										}
									}
								}
							}
							if(i == 2 && j == 2)
							{
								c += c_p_;
								break;
							}
						}
						int plus_sec_ = (int)(distan_coord(GetPos(),c)/2);
						if((*it)->Fly(gm_, c, 20+plus_sec_))
							return true;
					}
				}
			}
		}
	}
	return false;
}
void Mon_big_zombie::Approach(Game_Manager* gm_, coord_def c, Unit* target_)
{
	if(!throw_count && throws && !GetDelay() && !nonmove_delay)
	{
		if((int)(distan_coord(GetPos(),c)/2)<30)
		{
			throw_count = 10;
			return;
		}
		if(Throw(gm_, c))
		{
			throws = false;
			count = 150;
			SetDelay(50.0f);
		}
		else
		{
			throw_count = 10;
		}
	}
}