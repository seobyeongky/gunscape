//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mini_map.cpp
//
// 내용: 미니맵을 저장함
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "mini_map.h"
#include "texture_list.h"
#include "image.h"
#include "profiler.h"
#include "gamemanager.h"
#include "player.h"
#include "item.h"


int DG_MAX_X = 60;
int DG_MAX_Y = 60;

Mini_Map::Mini_Map(int Max_x_, int Max_y_):
Max_x(Max_x_), Max_y(Max_y_), pitch_x(1), pitch_y(1), big(false)
{
	map = new char*[Max_x];
	for(int i=0; i< Max_x; i++)
		map[i] = new char[Max_y];
	for(int i=0; i< Max_x; i++)
		for(int j=0; j< Max_y; j++)
			map[i][j] = 0;
}


Mini_Map::~Mini_Map()
{
	for(int i=0; i< Max_x; i++)
		delete [] map[i];
	delete [] map;
}
void Mini_Map::Init()
{
	for(int i =0; i<Max_x; i++)
		for(int j =0; j<Max_y; j++)
			map[i][j] = 0;

	initMapTexture();
}
void Mini_Map::initMapTexture()
{
	IDirect3DTexture9* pTemp = tex_minimap2.GetTexture();

	D3DLOCKED_RECT lock_rect;

	//락을 걸어 텍스처데이터의 포인터를 얻어온다
	if(SUCCEEDED(pTemp->LockRect(0, &lock_rect, 0, D3DLOCK_DISCARD)))
	{
		//lock_rect의 포인터를 얻어온다
		DWORD* pBuf = (DWORD *)lock_rect.pBits;

		for(int i=0 ; i < 120 ; i++)
		{
			for(int j=0 ; j < 120 ; j++)
			{
				pBuf[i+j*120] &= 0x00ffffff;
			}		
		}
		//락해제
		pTemp->UnlockRect(0);
	}
}
void Mini_Map::MapTextureSight(int x_, int y_)
{
	IDirect3DTexture9* pTemp = tex_minimap2.GetTexture();

	D3DLOCKED_RECT lock_rect;

	//락을 걸어 텍스처데이터의 포인터를 얻어온다
	if(SUCCEEDED(pTemp->LockRect(0, &lock_rect, 0, D3DLOCK_DISCARD)))
	{
		//lock_rect의 포인터를 얻어온다
		DWORD* pBuf = (DWORD *)lock_rect.pBits;

		pBuf[x_+y_*120] |= 0xff000000;
	
		//락해제
		pTemp->UnlockRect(0);
	}
}
void Mini_Map::SetPitch(int width_, int height_)
{
	pitch_x = width_/Max_x;
	pitch_y = height_/Max_y;
}

void Mini_Map::SetMap(int x_,int y_, bool value_)
{
	if(x_<0 || x_ >= Max_x || y_<0 || y_ >= Max_y)
		return;
	if(value_)
		map[x_][y_] |= 1;
	else
		map[x_][y_] &= ~1;
}
void Mini_Map::SetSight(int x_,int y_)
{
	if(x_<0 || x_ >= Max_x || y_<0 || y_ >= Max_y)
		return;
	if(!isSight(x_,y_))
	{
		map[x_][y_] |= 2;
		if(isMove(x_,y_))
			MapTextureSight(x_, y_);
	}
}

void Mini_Map::fogUpdate(int x_, int y_, bool value_)
{
	if(x_<0 || x_ >= Max_x || y_<0 || y_ >= Max_y)
		return;

	if(value_)
		map[x_][y_] |= 4;
	else
		map[x_][y_] &= ~4;

}
void Mini_Map::UpdateSight(coord_def& c, float sight)
{
	int x_ = (int)c.x/pitch_x;
	int y_ = (int)c.y/pitch_y;

	int sight_x = (int)floor(sight/pitch_x+0.5f);
	int sight_y = (int)floor(sight/pitch_y+0.5f);

	for(float i = (float)-sight_x;i<=(float)sight_x;i++)
	{
		for(float j = (float)-sight_y;j<=(float)sight_y;j++)
		{
			if((i)*(i)/(sight_x*sight_x) +(j)*(j)/(sight_y*sight_y) <= 1)
			{
				if(x_+i >= 0 && x_+i < Max_x && y_+j >= 0 && y_+i < Max_y )
				{
					if(!isFog(x_+(int)i,y_+(int)j))
						SetSight(x_+(int)i,y_+(int)j);
					else
					{
						int a= 0;
						a= 4+4;

					}
				}
			}
		}
	}
}
void Mini_Map::map_hack()
{
	for(int i = 0;i<Max_x;i++)
	{
		for(int j = 0;j<Max_y;j++)
		{
			SetSight(i,j);
		}
	}
}

bool Mini_Map::isMove(int x_,int y_)
{
	if(x_<0 || x_ >= Max_x || y_<0 || y_ >= Max_y)
		return 0;
	return !(map[x_][y_] & 1);
};
bool Mini_Map::isSight(int x_,int y_)
{
	if(x_<0 || x_ >= Max_x || y_<0 || y_ >= Max_y)
		return 0;
	return ((map[x_][y_] & 2) != 0);
};
bool Mini_Map::isFog(int x_,int y_)
{
	if(x_<0 || x_ >= Max_x || y_<0 || y_ >= Max_y)
		return 0;
	return ((map[x_][y_] & 4) != 0);
};


bool Mini_Map::MiniMapDraw(Game_Manager* gm_, coord_def offset_)
{
	int x_ = GetMiniX(gm_->player->GetX());
	int y_ = GetMiniY(gm_->player->GetY());
	int x_escape_ = GetMiniX(gm_->next_portal?gm_->next_portal->GetX():0);
	int y_escape_ = GetMiniY(gm_->next_portal?gm_->next_portal->GetY():0);
	if(!big)
	{
		float size_ = 180.0f/Max_x;
		float x_len_ = (60.0f-Max_x)*2;
		float y_len_ = (60.0f-Max_y)*4/3;
		//tex_minimap2.Draw(offset_.x,offset_.y, 2.0f, 2.0f, 0.0f, D3DCOLOR_ARGB(255,255,255,255));
		//tex_gun.Draw(offset_.x+(x_-60)*2+2,offset_.y+(y_-60)*2+1, 2.0f, 2.0f, 0.0f,D3DCOLOR_ARGB(255,255,0,0));
		//if(isSight(x_escape_,y_escape_))
		//{
		//	tex_gun.Draw(offset_.x+(x_escape_-60)*2+2,offset_.y+(y_escape_-60)*2+1, 2.0f, 2.0f, 0.0f,D3DCOLOR_ARGB(255,0,255,0));
		//}
		tex_minimap2.Draw(offset_.x+x_len_,offset_.y+y_len_, size_, size_, 0.0f, D3DCOLOR_ARGB(255,255,255,255));
		tex_gun.Draw(offset_.x+(x_-60)*size_+size_*2/3+x_len_,offset_.y+(y_-60)*size_+size_*2/3+y_len_, size_, size_, 0.0f,D3DCOLOR_ARGB(255,255,0,0));
		if(isSight(x_escape_,y_escape_))
		{
			tex_gun.Draw(offset_.x+(x_escape_-60)*size_+size_*2/3+x_len_,offset_.y+(y_escape_-60)*size_+size_*2/3+y_len_, size_, size_, 0.0f,D3DCOLOR_ARGB(255,0,255,0));
		}
	}
	else
	{
		float size_ = 6.0f;
		tex_minimap2.Draw((-x_+60.0f)*size_,(-y_+60.0f)*size_, size_, size_, 0.0f, D3DCOLOR_ARGB(100,255,255,255));
		tex_gun.Draw(size_*2/3, size_*2/3, size_, size_, 0.0f,D3DCOLOR_ARGB(255,255,0,0));
		
		if(gm_->next_portal && isSight(x_escape_,y_escape_))
		{
			tex_gun.Draw((x_escape_-60)*size_+(-x_+60.0f)*size_+size_*2/3,(y_escape_-60)*size_+(-y_+60.0f)*size_+size_*2/3, size_, size_, 0.0f,D3DCOLOR_ARGB(255,0,255,0));
		}
	}

	return true;
}