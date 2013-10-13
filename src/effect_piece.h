//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: effect_piece.h
//
// 내용: 이펙트 - 조각효과
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __EFFECT_PIECE_H__
#define  __EFFECT_PIECE_H__

#include <vector>
#include <d3dx9.h>
#include "Shot_base.h"

using namespace std;

class Effect_Piece: public Shot_base
{
	coord_def accel;
	int time;
	bool valid;
	const float angle;
	float size;
	const float size_inc;
	const int alpha_inc;
	D3DCOLOR color;
	int delay;

public:
	Effect_Piece(Texture* texture_, int time_, int team_, coord_def pos_, float angle_, float speed_, float max_speed_, float size_, float size_inc_, D3DCOLOR color_, int alpha_inc_, int delay_ = 0);
	virtual ~Effect_Piece();
	virtual bool Action(Game_Manager* gm_);
	virtual bool Draw(coord_def offset_, float size_);


};

//아래는 이 Effect_Piece로 낼수있는 효과들의 간략한 함수

void Effect_blood(Game_Manager* gm_, coord_def pos_, int num_, float power_);
void Effect_immortal(Game_Manager* gm_, coord_def pos_, int num_, float power_);
void Effect_fog(Game_Manager* gm_, coord_def pos_, float size_);
void Effect_switch(Game_Manager* gm_, coord_def pos_, float size_);
void Effect_trap(Game_Manager* gm_, coord_def pos_, float size_);
void Effect_berserker(Game_Manager* gm_, coord_def pos_, float size_);

void Effect_bomb(Game_Manager* gm_, coord_def pos_, int num_,  float size_, float power_);
void Effect_rockbomb(Game_Manager* gm_, coord_def pos_, int num_,  float size_, float power_);
void Effect_dust(Game_Manager* gm_, coord_def pos_, int num_,  float size_, float power_);

void Effect_run_afterimage(Game_Manager* gm_, Texture* texture_, coord_def pos_, float angle_, float size_);
void Effect_invisible(Game_Manager* gm_, coord_def pos_, int num_,  float size_, float power_);
void Effect_virus(Game_Manager* gm_, coord_def pos_, float size_);
void Effect_smoke(Game_Manager* gm_, coord_def pos_, float size_);
void Effect_fire(Game_Manager* gm_, coord_def pos_, float size_);
void Effect_noise(Game_Manager* gm_, coord_def pos_, float size_);
void Effect_alert(Game_Manager* gm_, coord_def pos_, float size_);
void Effect_cry(Game_Manager* gm_, coord_def pos_, float range_);
void Effect_range(Game_Manager* gm_, coord_def pos_, float range_, D3DCOLOR color_);

#endif // __Shot_fire_H__
