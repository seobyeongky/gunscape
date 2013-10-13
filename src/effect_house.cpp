//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_house.cpp
//
// 내용: 인간의 마을의 집은 밖에선 안보인다.
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "effect_house.h"
#include "gamemanager.h"
#include "unit.h"
#include "player.h"
#include "image.h"
#include "effect_piece.h"
#include "random.h"


Effect_house::Effect_house(Texture* texture_, coord_def pos_, float width_, float height_):
Shot_base(texture_, NULL, 0, pos_, coord_def(), STP_FOG), width(width_), height(height_), alpha(255)
{
}
Effect_house::~Effect_house()
{

}


bool Effect_house::Action(Game_Manager* gm_)
{
	if(gm_ && alpha == 255)
	{
		for(list<Unit*>::iterator it = gm_->unit_list.begin();it != gm_->unit_list.end();it++)
		{
			if((*it)->isLive() && !(*it)->isNonTarget() )
			{
				if((*it)->GetPos().x >= GetPos().x - width/2 && (*it)->GetPos().x <= GetPos().x + width/2 && (*it)->GetPos().y >= GetPos().y - height/2 && (*it)->GetPos().y <= GetPos().y + height/2)
				{
					(*it)->SetHouseIn(2);
				}
			}
		}
	}

	coord_def temp_ = gm_->player->GetPos();
	if(temp_.x >= GetPos().x - width/2 && temp_.x <= GetPos().x + width/2 && temp_.y >= GetPos().y - height/2 && temp_.y <= GetPos().y + height/2)
	{
		if(alpha>5)
			alpha-=10;
		if(alpha == 245){
			for(int x_ = gm_->map->GetMiniX(GetPos().x - width/2)+1; x_<= gm_->map->GetMiniX(GetPos().x + width/2)-1; x_++)
			{
				for(int y_ = gm_->map->GetMiniY(GetPos().y - height/2)+1; y_<= gm_->map->GetMiniY(GetPos().y + height/2)-1; y_++)
				{
					gm_->map->fogUpdate(x_,y_,false);
				}
			}
		}
	}
	else
	{
		if(alpha<255)
			alpha+=10;
		if(alpha == 255){
			for(int x_ = gm_->map->GetMiniX(GetPos().x - width/2)+1; x_<= gm_->map->GetMiniX(GetPos().x + width/2)-1; x_++)
			{
				for(int y_ = gm_->map->GetMiniY(GetPos().y - height/2)+1; y_<= gm_->map->GetMiniY(GetPos().y + height/2)-1; y_++)
				{
					gm_->map->fogUpdate(x_,y_,true);
				}
			}
		}
	}
	return false;
}

bool Effect_house::Draw(coord_def offset_, float size_)
{
	if(GetTexture() && alpha>5)
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, width*size_, height*size_,0.0f,D3DCOLOR_ARGB(alpha,128,128,128));
	else
		return false;
	return false;
}

bool Effect_house::HouseCollution(const coord_def& c)
{
	if(c.x >= GetPos().x - width/2 && c.x <= GetPos().x + width/2 && c.y >= GetPos().y - height/2 && c.y <= GetPos().y + height/2)
	{
		return true;
	}
	return false;
}