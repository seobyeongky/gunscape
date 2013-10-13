//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: char_make.h
//
// 내용: 캐릭터만들기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __CHAR_MAKE_H__
#define  __CHAR_MAKE_H__


#include <vector>
#include "coord_def.h"
using namespace std;

class Player;
class Direct_Manager;
class Game_Manager;
class Job_base;


class Character_Maker
{
	Player* player;

	int num;
	vector<Job_base*> job_list;

public:
	Character_Maker();
	~Character_Maker();
	void SetPosition(coord_def pos_);
	
	bool SelectDraw(Direct_Manager* direct_);

	unsigned int GetCharNum();
	bool Select(unsigned int i);
	Player* GetPlayer(Game_Manager* gm_);
};


#endif // __GAME_MANAGER_H__

