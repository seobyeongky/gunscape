//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: config.h
//
// 내용: 설정파일 열기
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef  __CONFIG_H__
#define  __CONFIG_H__

#include <string>

enum gameMode_t
{
	SINGLE_GAME,
	MULTI_GAME
};

namespace config
{
	extern int width;
	extern int height;

	extern gameMode_t gamemode;

	extern std::string username;
	extern bool host;
	extern std::string host_addr;

	void LoadFromFile();
};

#endif // __CONFIG_H__