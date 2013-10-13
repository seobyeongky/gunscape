//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: mini_map.h
//
// 내용: 미니맵을 저장함
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __MINI_MAP_H__
#define  __MINI_MAP_H__


#include "coord_def.h"

extern int DG_MAX_X;
extern int DG_MAX_Y;

class Player;
class Game_Manager;


class Mini_Map
{
	const int Max_x;
	const int Max_y;

	int pitch_x;
	int pitch_y;

	char** map;

	bool big;
public:
	Mini_Map(int Max_x_, int Max_y_);
	~Mini_Map();

	void Init();

	void initMapTexture();
	void MapTextureSight(int x_, int y_);

	const int GetMaxX(){return Max_x;};
	const int GetMaxY(){return Max_y;};
	int GetPitchX(){return pitch_x;};
	int GetPitchY(){return pitch_y;};
	
	void SetPitch(int width_, int height_);
	void SetMap(int x_,int y_, bool value_);
	void SetSight(int x_,int y_);
	
	void SwapSize(){big = !big;};

	void fogUpdate(int x_, int y_, bool value_);

	void UpdateSight(coord_def& c, float sight);
	void map_hack();

	bool isMove(int x_,int y_);
	bool isSight(int x_,int y_);
	bool isFog(int x_,int y_);

	bool MiniMapDraw(Game_Manager* gm_, coord_def offset_);

	int GetMiniX(float x_){return (int)x_/pitch_x;};
	int GetMiniY(float y_){return (int)y_/pitch_y;};
	float GetBigX(int x_){return (float)(x_*pitch_x+pitch_x/2);};
	float GetBigY(int y_){return (float)(y_*pitch_y+pitch_y/2);};
};





#endif // __MINI_MAP_H__