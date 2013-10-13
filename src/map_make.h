//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: map_make.h
//
// 내용: 지형제작 알고리즘
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MAP_MAKE_H__
#define  __MAP_MAKE_H__

#include "rect.h"
#include "mini_map.h"
#include "map.h"



class map_dummy
{
public:
	coord_int pos;
	int size_x;
	int size_y;
	coord_int m_entrance;
	coord_int m_exit;
	bool connect_enter;
	bool connect_exit;

	map_dummy(coord_int pos_,int size_x_,int size_y_);
	~map_dummy();
	bool collution(const coord_int& point,int size_x_ = 0,int size_y_ = 0);
	bool plus_collution(const coord_int& point,int size_x_,int size_y_);
	void make_map(Mini_Map& map_, bool wall_);
	void mask(Mini_Map& map);
	//void SetEnter(coord_int c);
	//void SetExit(coord_int c);
	coord_int GetEntrance(){return m_entrance;};
	coord_int GetExit(){return m_exit;};
	void SetConnectEnter(bool ok_){connect_enter=ok_;};
	void SetConnectExit(bool ok_){connect_exit=ok_;};
	bool GetConnect(){return (connect_exit||connect_enter);};
};

void map_algorithms(Game_Manager* gm_, Mini_Map& map_, int level_, MAP_TYPE type);

#endif // __MAP_MAKE_H__