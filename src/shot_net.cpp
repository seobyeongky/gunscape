//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_net.cpp
//
// 내용: 그물 총알
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_net.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"

Shot_net::Shot_net(Texture* texture_, Unit* unit_, int net_time_, int team_, coord_def pos_, float angle_, float speed_, float distance_):
Shot_base(texture_, unit_, team_, pos_, coord_def(cos(angle_)*speed_, sin(angle_)*speed_)), 
net_time(net_time_), distance(distance_), valid(true), angle(angle_), const_speed(speed_)
{
}
Shot_net::~Shot_net()
{

}
bool Shot_net::Action(Game_Manager* gm_)
{
	if(valid)
	{
		if(gm_)
		{
			for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
			{
				if((*it)->isLive() && !(*it)->isNonTarget()  && (*it)->GetTeam() != GetTeam() && (*it)->isCollution())
				{
					if((*it)->collution(GetPos(), 5.0f))
					{
						(*it)->SetNet(net_time);
						(*it)->StateApply("그물",net_time);
						valid = false;
					}
				}
			}
		}


		if(collution(3))
		{
			valid = false;
		}
		else
			Move();


		distance -= const_speed;
		if(distance<0)
			valid = false;
	}


	if(!valid)
	{
		return true;
	}
	return false;
}


bool Shot_net::Draw(coord_def offset_, float size_)
{
	if(GetTexture())
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size_, angle);
	else
		return false;
}