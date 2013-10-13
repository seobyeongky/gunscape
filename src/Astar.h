//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: Astar.h
//
// 내용: Astar알고리즘
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __ASTAR_H__
#define  __ASTAR_H__

#include <queue>
#include <stack>
#include "rect.h"
#include "map_make.h"

using namespace std;


class Mini_Map;

typedef struct searchnode
{
	coord_int pos;
	int cfs; //cost from start
	int ctg; //cost to goal
	int tc; //토탈 코스트
	char opcl; //0은 없음 1은 오픈 2는 클로즈
	struct searchnode* parent;
	searchnode():pos(0,0), cfs(0), ctg(0), tc(0), parent(NULL)
	{}
	searchnode(const coord_int& pos_,int cfs_, int ctg_,searchnode* parent_)
	{
		pos = pos_;
		cfs = cfs_;
		ctg = ctg_;
		tc = cfs+ctg;
		parent = parent_;
	}
	searchnode* Set(const coord_int& pos_,int cfs_, int ctg_,searchnode* parent_)
	{
		pos = pos_;
		cfs = cfs_;
		ctg = ctg_;
		tc = cfs+ctg;
		parent = parent_;
		return this;
	}
}searchnode;


bool PathSearch(const coord_int& start,const coord_int&  goal, stack<coord_int>& will_move, Mini_Map& map, int limit_ = -1);

extern searchnode** astar_node;



#endif // __ASTAR_H__