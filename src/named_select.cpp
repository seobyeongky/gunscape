//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: named_select.cpp
//
// 내용: 네임드를 추출하는 알고리즘
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "gamemanager.h"

#include "Monster.h"
#include "map.h"
#include "player.h"
#include "random.h"
#include "monster_list.h"



struct named_struct
{
	Monster_Index id; //몬스터
	int mins; //최하층 (0부터)
	int maxs; //최고층
	int percent; //확률
	named_struct(Monster_Index id_, int min_, int max_, int percent_):id(id_), mins(min_),maxs(max_),percent(percent_){}
};


list<named_struct> group;


void InitNamed()
{
	group.clear();
	group.push_back(named_struct(NAMED_ROBOT,15,15,100));
	group.push_back(named_struct(NAMED_ROBOT,15,15,100));
	group.push_back(named_struct(NAMED_ROBOT,15,15,100));
	group.push_back(named_struct(NAMED_JACK,1,3,15));
	group.push_back(named_struct(NAMED_LOOTER,1,3,15));
	
	group.push_back(named_struct(NAMED_BERSERKER,2,5,15));
	group.push_back(named_struct(NAMED_VIRUS,3,6,15));
	group.push_back(named_struct(NAMED_ASSASIN,4,9,15));	
	group.push_back(named_struct(NAMED_DRILL,6,11,15));
	group.push_back(named_struct(NAMED_SCREAM,8,13,15));
	group.push_back(named_struct(NAMED_FLY_BOSS,10,15,15));	
	group.push_back(named_struct(NAMED_SNIPER,10,15,15));	
}


void Game_Manager::NamedMake(int level_)
{
	for(list<named_struct>::iterator it = group.begin(); it != group.end();)
	{
		if(it->mins <= level_ && it->maxs >= level_ && rand_int(1,100)<=it->percent)
		{
			while(1)
			{
				int x_ = rand_int(0,map->GetWidth()-1);
				int y_ = rand_int(0,map->GetHeight()-1);
				if(!map->CollutionPos(x_,y_) && !player->collution(coord_def((float)x_,(float)y_),player->GetView()))
				{
			        unit_list.push_back(New_Named(it->id, coord_def((float)x_, (float)y_), -1, 0));
					break;
				}
			}

			list<named_struct>::iterator temp = it;
			it++;
			group.erase(temp);
		}
		else
		{
			it++;
		}
	}

}


