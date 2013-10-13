//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Shot_grenade.cpp
//
// 내용: 수류탄
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "shot_grenade.h"
#include "gamemanager.h"
#include "unit.h"
#include "image.h"
#include "random.h"
#include "effect_piece.h"
#include "Map.h"

Shot_grenade::Shot_grenade(Texture* texture_, Unit* unit_, int time_, float damage_, float power_, float max_power_, float range_, bool pentan_, int team_, coord_def pos_, coord_def target_):
Shot_base(texture_, unit_, team_, pos_, (target_ - pos_)*2.0f/(float)time_), 
damage(damage_), power(power_), max_power(max_power_), range(range_), pentan(pentan_), decel(-GetSpeed()/(float)time_),
time(time_), const_time(time_), angle(rand_float(0,D3DX_PI*2)), angle_inc(rand_int(0,1)*2-1), valid(true), size(1.0f)
{
}
Shot_grenade::~Shot_grenade()
{

}
bool Shot_grenade::Action(Game_Manager* gm_)
{
	if(valid)
	{
		size = sin(time*D3DX_PI/const_time)*1+1.0f;
		angle += angle_inc*0.05f;
		GrenadeMove(gm_);
		UpDownSpeed(decel);
		if(time--<=0)
		{
			Bomb(gm_, power, max_power, damage, range);
			valid = false;
		}
	}


	if(!valid)
	{
		return true;
	}
	return false;
}


bool Shot_grenade::Draw(coord_def offset_, float size_)
{
	if(GetTexture())
		return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size_*size , angle);
	else
		return false;
}

bool Shot_grenade::GrenadeMove(Game_Manager* gm_)
{
	if(!pentan)
	{
		float x_ = GetSpeed().x;
		float y_ = GetSpeed().y;
		bool move_ = false;

		if(!gm_->map->CollutionX(GetX(),coord_def(GetX()+x_,GetY()), 1.0f))
		{
			Move(GetX()+x_,GetY());
			move_ = true;
		}
		else
		{
			ApplySpeedX(-0.5f);
			decel.x *= -0.5f;
		}

		if(!gm_->map->CollutionY(GetY(),coord_def(GetX(),GetY()+y_), 1.0f))
		{
			Move(GetX(),GetY()+y_);
			move_ = true;
		}
		else
		{
			ApplySpeedY(-0.5f);
			decel.y *= -0.5f;
		}
	}
	else
	{
		Move();
	}

	return true;
}
