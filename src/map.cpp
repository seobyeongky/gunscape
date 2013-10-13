//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: map.cpp
//
// ����: �� Ŭ������ ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "map.h"
#include "image.h"
#include "bitrect.h"
#include "Shot_base.h"
#include "ai.h"
#include "map_make.h"
#include "mini_map.h"
#include "gamemanager.h"
#include "texture_list.h"
#include "Astar.h"
#include "Unit.h"




Map::Map(Texture* texture_):
texture(texture_), width(texture_->GetWidth()), height(texture_->GetHeight()),
bit(NULL), minimap(NULL)
{
	Map_Rebuild(texture_,60,60);
}	

Map::~Map()
{
	if(bit)
		delete bit;
	if(minimap)
		delete minimap;

	//"Astar.h"�� �ִ� astar_node ������ ���⼭ �����ϱ�. ���⼭ �Ҵ��ϴϱ�
	if(astar_node)
	{
		for(int i = 0; i<DG_MAX_X ; i++)
			delete[] astar_node[i];
		delete[] astar_node;
	}
}
void Map::Map_Rebuild(Texture* texture_, int x_, int y_)
{
	if(bit)
		delete bit;
	if(minimap)
		delete minimap;
	
	texture = texture_;
	width = texture_->GetWidth();
	height = texture_->GetHeight();
	//��Ʈ�ʵ��� �޸𸮸� �׸��� �����ŭ �Ҵ��Ѵ�.
	
	if(astar_node)
	{
		for(int i = 0; i<DG_MAX_X ; i++)
			delete[] astar_node[i];
		delete[] astar_node;
	}

	DG_MAX_X = x_;
	DG_MAX_Y = y_;
	
	astar_node = new searchnode*[DG_MAX_X];
	for(int i = 0; i<DG_MAX_X ; i++)
		astar_node[i] = new searchnode[DG_MAX_Y];

	bit = new BitRect(width, height);
	minimap = new Mini_Map(DG_MAX_X,DG_MAX_Y);

}
bool Map::MapInit()
{
	IDirect3DTexture9* pTemp = texture->GetTexture();

	D3DLOCKED_RECT lock_rect;

	//���� �ɾ� �ؽ�ó�������� �����͸� ���´�
	if(SUCCEEDED(pTemp->LockRect(0, &lock_rect, 0, D3DLOCK_READONLY)))//D3DLOCK_DISCARD�� ��������
	{
		//lock_rect�� �����͸� ���´�
		DWORD* pBuf = (DWORD *)lock_rect.pBits;
	
		for(int i=0 ; i < width ; i++)
		{
			for(int j=0 ; j < height ; j++)
			{
				// 32��Ʈ�� ��ȯ~
				DWORD pixel = pBuf[i+j*width];
				if((pixel & 0xff000000))
				{
					bit->SetBit(i, j);
				}
				else
				{
					bit->UnSetBit(i, j);
				}
			}		
		}
		//������
		pTemp->UnlockRect(0);
		Shot_base::SetMap(this);
		Ai_Manager::SetMap(this);
		return true;
	}
	return false;
}

bool Map::Draw(coord_def offset, float size_)
{
	if(texture)
		return texture->Draw((width/2-offset.x)*size_, (height/2-offset.y)*size_, size_, 0.0f);
	else
		return false;
}

bool Map::CollutionX(float orig_x_ , coord_def pos_, float size_)
{
	if(pos_.x - size_ < 0 && pos_.x + size_ >= width)
		return true;
	int move_ = (int)((pos_.x > orig_x_)?size_:-size_);
	for(int i=(int)-size_; i <(int)size_+1; i++)
	{
		if(bit->GetBit((int)pos_.x+move_, (int)pos_.y + i))
			return true;
	}
	return false;
}

bool Map::CollutionY(float orig_y_, coord_def pos_, float size_)
{
	if(pos_.y - size_ < 0 && pos_.y + size_ >= height)
		return true;
	int move_ =  (int)((pos_.y > orig_y_)?size_:-size_);
	for(int i=(int)-size_; i <(int)size_+1; i++)
	{
		if(bit->GetBit((int)pos_.x + i, (int)pos_.y + move_))
			return true;
	}
	return false;
}

bool Map::CollutionPos(int x_, int y_)
{
	return bit->GetBit(x_, y_);
}
bool Map::Collution(int x_, int y_, int size_)
{	
	if(!size_)
	{
		return CollutionPos(x_, y_);
	}
	else
	{
		for(int i = -size_; i<=size_;i++)
		{
			for(int j = -size_; j<=size_;j++)
			{
				if(i*i+j*j<=size_*size_)
				{
					if(CollutionPos(x_+i, y_+j))
						return true;
				}
			}
		}
		return false;
	}

}
int Map::CollutionPosToPos(coord_def start_, coord_def target_, int max_len_)
{
	float radius_ = distan_coord(start_, target_);
	float x_step = (target_.x-start_.x/*+0.0001f*/)*1/radius_;
	float y_step = (target_.y-start_.y/*+0.0001f*/)*1/radius_;
	max_len_ = max_len_!=-1?min((int)radius_, max_len_):(int)radius_;
	for(int i = 0 ; i<max_len_ ; i++)
	{
		if(CollutionPos((int)start_.x,(int)start_.y))
		{
			return i+1;
		}
		start_.x += x_step;
		start_.y += y_step;
	}
	return 0;
}
bool Map::CollutionMap(coord_def pos_, int size_)
{
	if(pos_.x - size_ < 0 && pos_.x + size_ >= width)
		return true;
	return false;
}
void Map::fogUpdate(int x_, int y_, bool value_)
{
	minimap->fogUpdate(x_,y_,value_);
}
void Map::SwapSize()
{
	minimap->SwapSize();
};
void Map::UpdateSight(Unit* unit_)
{
	minimap->UpdateSight(unit_->GetPos(), unit_->GetView());
}
void Map::UpdateSight(coord_def pos_, float range_)
{
	minimap->UpdateSight(pos_, range_);
}
void Map::map_hack()
{
	minimap->map_hack();
}
bool Map::DrawMinimap(Game_Manager* gm_, coord_def offset_)
{
	return minimap->MiniMapDraw(gm_, offset_);
}
void Map::MapMake(Game_Manager* gm_,int level_,MAP_TYPE type)
{
	if(type == MPT_LAST)
	{
		Map_Rebuild(&tex_map2,120,120);
	}
	else if(level_ == 0)
	{
		Map_Rebuild(&tex_map,60,60);
	}



	minimap->Init();
	map_algorithms(gm_, *minimap, level_, type);

	minimap->SetPitch(width, height);

	IDirect3DTexture9* pTemp = texture->GetTexture();

	D3DLOCKED_RECT lock_rect;

	//���� �ɾ� �ؽ�ó�������� �����͸� ���´�
	if(SUCCEEDED(pTemp->LockRect(0, &lock_rect, 0, D3DLOCK_DISCARD)))
	{
		//lock_rect�� �����͸� ���´�
		DWORD* pBuf = (DWORD *)lock_rect.pBits;

		for(int i=0 ; i < minimap->GetMaxX() ; i++)
		{
			for(int j=0 ; j < minimap->GetMaxY() ; j++)
			{
				int x_ = i*minimap->GetPitchX();
				int y_ = j*minimap->GetPitchY();
				bool wall_ = i==0 || i==minimap->GetMaxX()-1 || j == 0 || j== minimap->GetMaxY() - 1 || !minimap->isMove(i,j);
				for(int k=0;k<minimap->GetPitchX();k++)
				{
					for(int l=0;l<minimap->GetPitchY();l++)
					{
						if(wall_)
							pBuf[x_+k+(y_+l)*width] |= 0xff000000;
						else
							pBuf[x_+k+(y_+l)*width] &= 0x00ffffff;
					}
				}
			}
		}
		//������
		pTemp->UnlockRect(0);
	}
}

int Map::GetMiniX(float x_)
{
	return minimap->GetMiniX(x_);
}
int Map::GetMiniY(float y_)
{
	return minimap->GetMiniX(y_);
}
float Map::GetBigX(int x_)
{
	return minimap->GetBigX(x_);
}
float Map::GetBigY(int y_)
{
	return minimap->GetBigY(y_);
}