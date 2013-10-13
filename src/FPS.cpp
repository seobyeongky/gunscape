//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: FPS.h
//
// 내용: FPS계산 클래스 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////
 
#include <windows.h>
#include "FPS.h"



Fps::Fps():
current_fps(0.0f), time_elapsed(0.0f), prev_time((float)timeGetTime()), frame_cnt(0)
{


}


float Fps::GetFps()
{
	float cur_time = (float)timeGetTime();
	frame_cnt++;
	time_elapsed += cur_time-prev_time;
	prev_time = cur_time;
	if(time_elapsed >= 1000)
	{
		 current_fps = (float)frame_cnt * 1000 / time_elapsed;

		 time_elapsed = 0.0f;
		 frame_cnt = 0;
	}
	return current_fps;
}