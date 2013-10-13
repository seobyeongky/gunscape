//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: dart.h
//
// 내용: 독침
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __DART_H__
#define  __DART_H__

#include "rifle.h"

class Dart: public Rifle
{

public:
	Dart(const main_weapon_infor& infor_, coord_def pos_, int time_);

	
	virtual float Shot(Game_Manager* gm_, Unit* User_, int team_, const coord_def& start_, const coord_def& pos_, float focus_);
	
	virtual void PlayReloadSE(){};
};

#endif // __DART_H__