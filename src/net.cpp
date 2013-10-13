//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: net.cpp
//
// 내용: 서브아이템. 그물
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "net.h"
#include "texture_list.h"
#include "player.h"
#include "gamemanager.h"
#include "shot_net.h"

Sub_Net::Sub_Net(Player* user_, coord_def pos_, int time_):
Sub_Weapon(&tex_item_unknown, "그물", "맞은 상대를 잠깐동안\n속박하는 그물", pos_, time_, user_, &tex_inter_net, 5, 5.0f)
{

}
Sub_Net::~Sub_Net()
{

}

float Sub_Net::Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_)
{
	float angle_ = GetAngleToTarget(start_, pos_);
	gm_->shot_list.push_back(new Shot_net(&tex_net, User_, 200, team_, start_, angle_, 5, 100));
	if(!UpDownNum(-1))
	{
		GetPlayer()->DeleteSubWeapon(this, -1);
		delete this; //끝나면 이걸 지움. 제대로 동작되나?
	}
	return 0;
}