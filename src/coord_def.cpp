//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: coord_def.cpp
//
// 내용: 좌표처리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <d3dx9.h>
#include <math.h>
#include "coord_def.h"


float distan_coord(const coord_def& a, const coord_def& b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));

}


float GetAngleToTarget(coord_def start, coord_def target)
{
	return atan2(target.y - start.y, target.x - start.x);
}
float GetAngleToTarget180(coord_def start, coord_def target)
{
	return atan2(target.y - start.y, target.x - start.x)/180*D3DX_PI;
}