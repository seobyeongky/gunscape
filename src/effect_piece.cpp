//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_piece.cpp
//
// 내용: 이펙트 - 조각효과
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "effect_piece.h"
#include "texture_list.h"
#include "random.h"
#include "gamemanager.h"
#include "image.h"


Effect_Piece::Effect_Piece(Texture* texture_, int time_, int team_, coord_def pos_, float angle_, float speed_, float max_speed_, float size_, float size_inc_, D3DCOLOR color_, int alpha_inc_, int delay_):
Shot_base(texture_, NULL, team_, pos_, coord_def(cos(angle_)*speed_, sin(angle_)*speed_)), 
accel((coord_def(cos(angle_)*max_speed_, sin(angle_)*max_speed_) - GetSpeed())/(float)time_), time(time_), valid(true), angle(angle_),
size(size_), size_inc(size_inc_), alpha_inc(alpha_inc_), color(color_), delay(delay_)
{

}

Effect_Piece::~Effect_Piece()
{

}

bool Effect_Piece::Action(Game_Manager* gm_)
{
	if(valid)
	{
		if(delay)
			delay--;
		else
		{
			Move();
			UpDownSpeed(accel);
			size += size_inc;
			color += alpha_inc << 24;
			
			time--;
			if(time<0)
				valid = false;
		}
	}


	if(!valid)
	{
		return true;
	}
	return false;
}


bool Effect_Piece::Draw(coord_def offset_, float size_)
{
	if(!delay)
	{
		if(GetTexture())
			return GetTexture()->Draw((GetPos().x-offset_.x)*size_, (GetPos().y-offset_.y)*size_, size*size_, size*size_, angle, color);
		else
			return false;
	}
	return false;
}


void Effect_blood(Game_Manager* gm_, coord_def pos_, int num_, float power_)
{
	for(int i = 0; i<num_; i++)
	{
		gm_->shot_list.push_back(new Effect_Piece(&tex_gun, 30, 0, pos_, rand_float(0,360), power_*rand_float(0.1f,2), 0, 1.0f, 0.0f, D3DCOLOR_ARGB(255,255,0,0), 0));
	}
}

void Effect_immortal(Game_Manager* gm_, coord_def pos_, int num_, float power_)
{
	for(int i = 0; i<num_; i++)
	{
		gm_->shot_list.push_back(new Effect_Piece(&tex_gun, 30, 0, pos_, rand_float(0,360), power_*rand_float(0.1f,2), 0, 2.0f, 0.0f, D3DCOLOR_ARGB(255,255,0,0), 0));
	}
}
void Effect_fog(Game_Manager* gm_, coord_def pos_, float size_)
{
	gm_->shot_list.push_back(new Effect_Piece(&tex_gun, 30, 0, pos_, rand_float(0,D3DX_PI*2), 0.0f, 0.0f, 2.0f*size_, 0.1f*size_, D3DCOLOR_ARGB(150,100,100,100), -5));
}
void Effect_switch(Game_Manager* gm_, coord_def pos_, float size_)
{
	gm_->shot_list.push_back(new Effect_Piece(&tex_focus, 30, 0, pos_, rand_float(0,D3DX_PI*2), 0.0f, 0.0f, 1.0f*size_, 0.03f*size_, D3DCOLOR_ARGB(150,0,128,0), -5));
}
void Effect_trap(Game_Manager* gm_, coord_def pos_, float size_)
{
	gm_->shot_list.push_back(new Effect_Piece(&tex_trap_effect, 25, 0, pos_, rand_float(0,D3DX_PI*2), 0.0f, 0.0f, 1.0f*size_, 0.05f*size_, D3DCOLOR_ARGB(255,255,255,255), -10));
}
void Effect_berserker(Game_Manager* gm_, coord_def pos_, float size_)
{
	gm_->shot_list.push_back(new Effect_Piece(&tex_focus, 20, 0, pos_, rand_float(0,D3DX_PI*2), 0.0f, 0.0f, 0.0f, 0.1f*size_, D3DCOLOR_ARGB(240,255,0,0), -12));
}



void Effect_bomb(Game_Manager* gm_, coord_def pos_, int num_,  float size_, float power_)
{
	for(int i = 0; i<num_; i++)
	{
		float temp_size = rand_float(3.0f,7.0f)*size_;
		gm_->shot_list.push_back(new Effect_Piece(&tex_gun, 40, 0, pos_, rand_float(0,D3DX_PI*2), power_*rand_float(0.1f,2), 0, temp_size, temp_size/-40.0f, D3DCOLOR_ARGB(160,255,rand_int(0,255),rand_int(0,50)), -4));
	}
}
void Effect_rockbomb(Game_Manager* gm_, coord_def pos_, int num_,  float size_, float power_)
{
	for(int i = 0; i<num_; i++)
	{
		float temp_size = rand_float(3.0f,7.0f)*size_;
		gm_->shot_list.push_back(new Effect_Piece(&tex_gun, 40, 0, pos_, rand_float(0,D3DX_PI*2), power_*rand_float(0.1f,2), 0, temp_size, temp_size/-40.0f, D3DCOLOR_ARGB(160,125,rand_int(80,125),0), -4));
	}
}

void Effect_dust(Game_Manager* gm_, coord_def pos_, int num_,  float size_, float power_)
{
	for(int i = 0; i<num_; i++)
	{
		float temp_size = rand_float(3.0f,7.0f)*size_;
		gm_->shot_list.push_back(new Effect_Piece(&tex_gun, 80, 0, pos_, rand_float(0,D3DX_PI*2), power_*rand_float(0.1f,1.0f), 0, temp_size, temp_size/-80.0f, D3DCOLOR_ARGB(160,125,rand_int(80,125),0), -2));
	}
}
void Effect_run_afterimage(Game_Manager* gm_, Texture* texture_, coord_def pos_, float angle_, float size_)
{
	gm_->shot_list.push_back(new Effect_Piece(texture_, 50, 0, pos_, angle_, 0.0f, 0.0f, size_, 0.0f, D3DCOLOR_ARGB(153,100,100,255), -3));
}

void Effect_invisible(Game_Manager* gm_, coord_def pos_, int num_,  float size_, float power_)
{
	for(int i = 0; i<num_; i++)
	{
		float temp_size = rand_float(3.0f,6.0f)*size_;
		gm_->shot_list.push_back(new Effect_Piece(&tex_gun, 40, 0, pos_, rand_float(0,D3DX_PI*2), power_*rand_float(0.1f,2), 0, temp_size, temp_size/-40.0f, D3DCOLOR_ARGB(160,0,0,rand_int(100,255)), -4));
	}
}
void Effect_virus(Game_Manager* gm_, coord_def pos_, float size_)
{
	gm_->shot_list.push_back(new Effect_Piece(&tex_virus, 80, 0, pos_, rand_float(0,D3DX_PI*2), 0.0f, 0.0f, 0.5f*size_, 0.025f*size_, D3DCOLOR_ARGB(80,255,255,255), -1));
}
void Effect_smoke(Game_Manager* gm_, coord_def pos_, float size_)
{
	gm_->shot_list.push_back(new Effect_Piece(&tex_smoke, 80, 0, pos_, rand_float(0,D3DX_PI*2), 0.0f, 0.0f, 1.0f*size_, 0.0f, D3DCOLOR_ARGB(80,255,255,255), -1));
}
void Effect_fire(Game_Manager* gm_, coord_def pos_, float size_)
{
	gm_->shot_list.push_back(new Effect_Piece(&tex_gun, 30, 0, pos_, rand_float(0,D3DX_PI*2), 0.0f, 0.0f, 2.0f*size_, 0.15f*size_, D3DCOLOR_ARGB(255,255,rand_int(0,255),rand_int(0,50)), -8));
}
void Effect_noise(Game_Manager* gm_, coord_def pos_, float size_)
{
	gm_->shot_list.push_back(new Effect_Piece(&tex_focus, 50, 0, pos_, 0, 0.0f, 0.0f, 0.0f, 0.2f*size_, D3DCOLOR_ARGB(255,0,128,255), -5));
}
void Effect_alert(Game_Manager* gm_, coord_def pos_, float size_)
{
	gm_->shot_list.push_back(new Effect_Piece(&tex_focus, 20, 0, pos_, 0, 0.0f, 0.0f, 0.0f, 0.2f*size_, D3DCOLOR_ARGB(201,255,0,0), -10));
}
void Effect_cry(Game_Manager* gm_, coord_def pos_, float range_)
{
	for(int i = 0 ; i < 3; i++)
		gm_->shot_list.push_back(new Effect_Piece(&tex_focus, 20, 0, pos_, 0, 0.0f, 0.0f, 0.0f, range_/16.0f/20.0f, D3DCOLOR_ARGB(255,255,255,0), -10, i*5));
}
void Effect_range(Game_Manager* gm_, coord_def pos_, float range_, D3DCOLOR color_)
{
	gm_->shot_list.push_back(new Effect_Piece(&tex_focus, 50, 0, pos_, 0, 0.0f, 0.0f, range_/16.0f, 0.0f, color_, -2));
}