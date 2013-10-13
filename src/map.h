//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: map.h
//
// 내용: 맵을 저장함
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MAP_H__
#define  __MAP_H__

#include "coord_def.h"

class Texture;
class BitRect;
class Mini_Map;
class Unit;
class Player;
class Game_Manager;


enum MAP_TYPE
{
	MPT_NOMAL,
	MPT_ZOMBIE,
	MPT_HUMAN,
	MPT_BUG,
	MPT_LAST,
	MPT_MAX
};


class Map
{
	Texture* texture;

	int width;
	int height;
	BitRect* bit;
	
public:
	Mini_Map* minimap;


	Map(Texture* texture_);
	~Map();

	
	void Map_Rebuild(Texture* texture_, int x_, int y_);

	bool Draw(coord_def offset, float size_);
	bool CollutionX(float orig_x_ , coord_def pos_, float size_);
	bool CollutionY(float orig_y_ , coord_def pos_, float size_);
	bool CollutionPos(int x_, int y_);
	bool Collution(int x_, int y_, int size_);
	int CollutionPosToPos(coord_def start_, coord_def target_, int max_len_ = -1);
	bool CollutionMap(coord_def pos_, int size_);

	int GetWidth(){return width;};
	int GetHeight(){return height;};

	void fogUpdate(int x_, int y_, bool value_);

	void SwapSize();
	void UpdateSight(Unit* unit_);
	void UpdateSight(coord_def pos_, float range_);
	void map_hack();
	bool DrawMinimap(Game_Manager* gm_, coord_def offset_);

	void MapMake(Game_Manager* gm_, int level_, MAP_TYPE type);
	bool MapInit();

	
	int GetMiniX(float x_);
	int GetMiniY(float y_);

	
	float GetBigX(int x_);
	float GetBigY(int y_);
};


#endif // __MAP_H__