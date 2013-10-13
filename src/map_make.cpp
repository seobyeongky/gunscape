//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: map_make.cpp
//
// 내용: 지형제작 알고리즘
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <stack>
#include "map_make.h"
#include "gamemanager.h"
#include "effect_house.h"
#include "Astar.h"
#include "player.h"
#include "random.h"
#include "map.h"
#include "portal.h"
#include "mini_map.h"
#include "texture_list.h"

using namespace std;


map_dummy::map_dummy(coord_int pos_,int size_x_,int size_y_):
pos(pos_),size_x(size_x_),size_y(size_y_), m_entrance(0,0),m_exit(0,0),
connect_enter(false),connect_exit(false)
{
	if(randA(1))
	{
		m_entrance.x = rand_int(-size_x+1,size_x-1);
		m_entrance.y = (randA(1)?-size_y:size_y);
	}
	else
	{
		m_entrance.x = (randA(1)?-size_x:size_x);
		m_entrance.y = rand_int(-size_y+1,size_y-1);
	}
	if(randA(1))
	{
		m_exit.x = rand_int(-size_x+1,size_x-1);
		m_exit.y = (randA(1)?-size_y:size_y);
	}
	else
	{
		m_exit.x = (randA(1)?-size_x:size_x);
		m_exit.y = rand_int(-size_y+1,size_y-1);
	}
	m_entrance+=pos;
	m_exit+=pos;
}
map_dummy::~map_dummy()
{
}

bool map_dummy::collution(const coord_int& point,int size_x_,int size_y_)
{
	return ( abs(point.x-pos.x) <= size_x_ + size_x + 1 && abs(point.y-pos.y) <= size_y_ + size_y + 1 );
}
bool map_dummy::plus_collution(const coord_int& point,int size_x_,int size_y_)
{
	return ((abs(point.x-pos.x) <= size_x_ + size_x + -1 && abs(point.y-pos.y) == size_y_ + size_y + 1 ) || (abs(point.x-pos.x) == size_x_ + size_x + 1 && abs(point.y-pos.y) <= size_y_ + size_y + -1 ));
}
void map_dummy::make_map(Mini_Map& map_, bool wall_)
{
	{
		for(int i = -size_x+1;i<=size_x-1;i++)
		{
			for(int j = -size_y+1;j<=size_y-1;j++)
			{		
				map_.SetMap(i+pos.x,j+pos.y,0);
			}
		}
	}
	
	if(wall_ == true)
	{
		for(int i = -size_x;i<=size_x;i++)
		{
			for(int j = -size_y;j<=size_y;j++)
			{		
				if(i == -size_x || i == size_x || j == -size_y || j == size_y)
					map_.SetMap(i+pos.x,j+pos.y,1);
			}
		}
	}
	map_.SetMap(m_entrance.x,m_entrance.y,0);
	if(wall_ == false)
		map_.SetMap(m_exit.x,m_exit.y,0);
}
void map_dummy::mask(Mini_Map& map_)
{
	for(int i = -size_x;i<=size_x;i++)
	{
		for(int j = -size_y;j<=size_y;j++)
		{
			map_.SetMap(i+pos.x,j+pos.y,1);
		}
	}
	map_.SetMap(m_entrance.x,m_entrance.y,0);
	map_.SetMap(m_exit.x,m_exit.y,0);
}



void map_algorithms01(Game_Manager* gm_, Mini_Map& map_, int m_size_, bool path_sum, bool room_sum, int min_num, int max_num, int min_siz, int max_size);
void map_algorithms02(Game_Manager* gm_, Mini_Map& map_);
void map_algorithms03(Game_Manager* gm_, Mini_Map& map_);


void map_algorithms(Game_Manager* gm_, Mini_Map& map_, int level_, MAP_TYPE type)
{
	switch(type){
	case MPT_NOMAL:
		{
			//map_algorithms01(gm_, map_, true,false);
			if(level_ == 0 || rand_int(0,2))
				map_algorithms01(gm_, map_, 10,false, false,12,20,3,5);
			else 
			{
				switch(rand_int(1,3))
				{
				case 1:
					map_algorithms01(gm_, map_, 10,true, false,10,15,4,5);
					break;
				case 2:
					map_algorithms01(gm_, map_, 10,true, false,40,40,1,1);
					break;
				case 3:
					map_algorithms01(gm_, map_, 10,false, false,20,20,1,2);
					break;
				}
			}
			//map_algorithms01(gm_, map_, 10,true, false,20,20,1,2);
			//map_algorithms01(gm_, map_, 10,true, false,10,15,2,5);
			/*bool one_ = rand_int(0,1)?true:false;
			bool two_ = (one_ && rand_int(0,1))?true:false;
			map_algorithms01(gm_, map_, 10,one_,two_,12,20,3,5);*/
			break;
		}
	case MPT_ZOMBIE:
		map_algorithms01(gm_, map_, 15, true, true,12,20,3,5);
		break;
	case MPT_HUMAN:
		map_algorithms02(gm_, map_);
		break;		
	case MPT_BUG:
		map_algorithms03(gm_, map_);
		break;
	case MPT_LAST:
		//map_algorithms01(gm_, map_, true,false);
		map_algorithms01(gm_, map_, 20,false, false,20,30,3,8);
		break;
	}
	//map_algorithms02(num,randA(10));
}

void map_algorithms01(Game_Manager* gm_, Mini_Map& map_, int m_size_, bool path_sum, bool room_sum, int min_num, int max_num, int min_siz, int max_size)
{
	vector<map_dummy*> vec_map;
	

	vec_map.reserve(32);

	if(path_sum == true)
		room_sum = true;

	

	int rand_dummy = rand_int(min_num,max_num);
	for(int i=0;i<rand_dummy;i++) //rand_dummy만큼의 맵더미를 생산
	{
		int repeat = 10;
		for(int j=0;j<repeat;j++) //무한반복 제거용
		{
			bool success= true;
			int r_size_x = rand_int(min_siz,max_size);
			int r_size_y = rand_int(min_siz,max_size);
			int m_size=m_size_;
			coord_int temp_coord(randA(map_.GetMaxX()-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size,randA(map_.GetMaxY()-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size);		
			map_dummy* temp = new map_dummy(temp_coord, r_size_x, r_size_y); //랜덤한 맵더미
			
			vector<map_dummy*>::iterator it;
			for (it=vec_map.begin();it!=vec_map.end();it++) 
			{
				if(!room_sum && (*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //맵더미충돌시엔 만들지 않음
				{
					success = false;
					break;
				}
			}	
			if(success) //겹치지 않을때 맵더미푸쉬
			{
				vec_map.push_back(temp);
				break;
			}
			else
			{
				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
				continue;
			}
		}
	}
	
	vector<map_dummy*>::iterator it;
	if(!path_sum){
		for(it=vec_map.begin();it!=vec_map.end();it++)  //방들을 마스크주기
			(*it)->mask(map_);
	}


	stack<coord_int> path_stack;

	map_dummy* temp = vec_map.back();
	for(it=vec_map.begin();it!=vec_map.end();it++) 
	{
		if(PathSearch(temp->GetEntrance(),(*it)->GetExit(),path_stack,map_))//방에 걸린 마스크를 피해서 경로저장
		{
			(*it)->SetConnectExit(true);
			temp->SetConnectEnter(true);
		}
		temp = (*it);
	}

	{
		vector<map_dummy*>::iterator it2 = vec_map.begin();
		for(it=vec_map.begin();it!=vec_map.end();it++)  //연결이 안된 방들을 다시 연결시도
		{
			for(;!(*it)->GetConnect() && it2 != vec_map.end();it2++)
			{
				if(it == it2)
					continue;
				if(PathSearch((*it)->GetEntrance(),(*it2)->GetExit(),path_stack,map_))//방에 걸린 마스크를 피해서 경로저장
				{
					(*it)->SetConnectEnter(true);
					temp->SetConnectExit(true);
				}				
			}
		}
	}


	for(int i = 0;i<map_.GetMaxX();i++)
		for(int j = 0;j<map_.GetMaxY();j++)
			map_.SetMap(i,j,1); //다시 전부 벽으로


	while(!path_stack.empty())
	{
		coord_int path_temp = path_stack.top();
		map_.SetMap(path_temp.x,path_temp.y,0); //저장한 도로를 칠하기
		path_stack.pop();
	}

	for(it=vec_map.begin();it!=vec_map.end();it++) 
	{
		(*it)->make_map(map_, false);
	}

	for (it=vec_map.begin();it!=vec_map.end();it++)
		delete *it;
}

void map_algorithms02(Game_Manager* gm_, Mini_Map& map_)
{

	vector<map_dummy*> vec_map;
	

	vec_map.reserve(32);


	

	int rand_dummy = rand_int(20,30);
	for(int i=0;i<rand_dummy;i++) //rand_dummy만큼의 맵더미를 생산
	{
		int repeat = 15;
		for(int j=0;j<repeat;j++) //무한반복 제거용
		{
			bool success= true;
			int r_size_x = rand_int(2,5);
			int r_size_y = rand_int(2,5);
			int m_size=10;
			coord_int temp_coord(randA(map_.GetMaxX()-(r_size_x+2)*2-1-m_size*2)+r_size_x+2+m_size,randA(map_.GetMaxY()-(r_size_y+2)*2-1-m_size*2)+r_size_y+2+m_size);		
			map_dummy* temp = new map_dummy(temp_coord, r_size_x, r_size_y); //랜덤한 맵더미
			
			vector<map_dummy*>::iterator it;
			for (it=vec_map.begin();it!=vec_map.end();it++) 
			{
				if((*it)->collution(temp_coord,r_size_x,r_size_y) || (*it)->plus_collution(temp_coord,r_size_x,r_size_y)) //맵더미충돌시엔 만들지 않음
				{
					success = false;
					break;
				}
			}	
			if(success) //겹치지 않을때 맵더미푸쉬
			{
				vec_map.push_back(temp);
				break;
			}
			else
			{
				delete temp; //겹치면 메모리 해제하고 다시 맵더미 생성
				continue;
			}
		}
	}

	for(int i = 0;i<map_.GetMaxX();i++)
		for(int j = 0;j<map_.GetMaxY();j++)
			map_.SetMap(i,j,1); //다시 전부 벽으로

	for(int i = 10;i<map_.GetMaxX()-10;i++)
		for(int j = 10;j<map_.GetMaxY()-10;j++)
			map_.SetMap(i,j,0); //키우기
	
	vector<map_dummy*>::iterator it;
	for(it=vec_map.begin();it!=vec_map.end();it++) 
	{
		(*it)->make_map(map_, true);
		gm_->shot_list.push_back(new Effect_house(&tex_gun,coord_def(((float)(*it)->pos.x+0.5f)*map_.GetPitchX(),((float)(*it)->pos.y+0.5f)*(float)map_.GetPitchY()),((*it)->size_x*2)*(float)map_.GetPitchX(),((*it)->size_y*2)*(float)map_.GetPitchY()));
		for(int x_=(*it)->pos.x-(*it)->size_x+1;x_<(*it)->pos.x+(*it)->size_x;x_++)
			for(int y_=(*it)->pos.y-(*it)->size_y+1;y_<(*it)->pos.y+(*it)->size_y;y_++)
				map_.fogUpdate(x_,y_,true);
	}

}
void map_algorithms03(Game_Manager* gm_, Mini_Map& map_)
{

	while(1)
	{
		for(int i = 0;i<map_.GetMaxX();i++)
			for(int j = 0;j<map_.GetMaxY();j++)
				map_.SetMap(i,j,1); //다시 전부 벽으로

		bool ok_= false;

		float angle_tic = 6*D3DX_PI/100.0f;
		float length_tic = (((float)map_.GetMaxX()+(float)map_.GetMaxY())/6.0f-3)/100.0f;
		float angle_ = rand_float(0,2*D3DX_PI), length_ = 0;
		for(int i=0;i<100;i++)
		{
			angle_ += angle_tic;
			length_ += length_tic;

			int x_ = (int)(map_.GetMaxX()/2.0f+length_*cos(angle_));
			int y_ = (int)(map_.GetMaxY()/2.0f+length_*sin(angle_));


			for(int j=-1;j<=1;j++)
				for(int k=-1;k<=1;k++)
					map_.SetMap(x_+j,y_+k,0);

			for(int j=-2;j<=2;j+=4)
				if(rand_int(0,9) == 0)
					map_.SetMap(x_+j,y_,0);
			for(int k=-2;k<=2;k+=4)
				if(rand_int(0,5) == 0)
					map_.SetMap(x_,y_+k,0);

			if(i == 99)
			{
				gm_->player->Move((float)(x_)*map_.GetPitchX(),(float)(y_)*map_.GetPitchX());
				stack<coord_int> path_stack;
				if(PathSearch(coord_int((x_),(y_)),coord_int(map_.GetMaxX()/2,map_.GetMaxY()/2),path_stack,map_))//방에 걸린 마스크를 피해서 경로저장
				{
					ok_ = true;
				}
			}

		}

		if(ok_)
			break;

		//제대로 길이 이어졌나 테스트
	}
	
	Item* portal_ = new Portal(&tex_potal, coord_def(map_.GetMaxX()*map_.GetPitchX()/2.0f,map_.GetMaxY()*map_.GetPitchX()/2.0f),false);
	gm_->item_list.push_back(portal_);
	gm_->next_portal = portal_;

}