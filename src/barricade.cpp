//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: barricade.cpp
//
// 내용: 서브아이템. 바리케이트
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "barricade.h"
#include "obj_barricade.h"
#include "texture_list.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_grenade.h"

Sub_Barricade::Sub_Barricade(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "바리케이트", "이동과 공격을 막는\n바리케이트를 설치", pos_, time_, user_, &tex_inter_block, 3, 5.0f)
{

}
Sub_Barricade::~Sub_Barricade()
{

}

float Sub_Barricade::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	float x_ = start_.x + cos(angle_)*15.0f;
	float y_ = start_.y + sin(angle_)*15.0f;



	gm_->unit_list.push_back(new Barricade(&tex_barricade, coord_def(x_,y_), 1000, 400, team_));
	if(!UpDownNum(-1))
	{
		GetPlayer()->DeleteSubWeapon(this, -1);
		delete this; //끝나면 이걸 지움. 제대로 동작되나?
	}
	return 0;
}