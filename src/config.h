//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: config.h
//
// ����: �������� ����
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

	extern std::wstring username;
	extern bool host;
	extern std::wstring host_addr;

	void LoadFromFile();
};

#endif // __CONFIG_H__