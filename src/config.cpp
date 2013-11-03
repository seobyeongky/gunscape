//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: config.h
//
// 내용: 설정파일 열기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "config.h"
#include <fstream>
using namespace std;

namespace config
{
	int width;
	int height;

	gameMode_t gamemode;

	string username;
	bool host;
	string host_addr;

	void LoadFromFile()
	{
		ifstream infile;
		infile.open("config.txt");
		if(infile.fail())
		{
			return;
		} 
		char name[1024];
		char value[1024];
		while(1)
		{
			int index = 0;
			while(1)
			{
				name[index] = infile.get();
				if(name[index] == -1)
				{
					infile.close();
					return;
				}
				if(name[index] == ' '  || name[index] == '=' ||  name[index] == '\n')
				{
					if(index == 0)
						continue;
					else
					{
						name[index] = '\0';
						break;
					}
				}
				index++;
			}
			index = 0;
			while(1)
			{
				value[index] = infile.get();
				if(value[index] == -1)
				{
					infile.close();
					return;
				}			
				if(value[index] == ' '  || value[index] == '=' ||  value[index] == '\n')
				{
					if(index == 0)
					{
						continue;
					}
					else
					{
						value[index] = '\0';
						break;
					}
				}
				index++;
			}
			int value2 = atoi(value);
			_strlwr_s(name);
			if(!strcmp(name,"width"))
			{
				if(value2>0)
					width = value2;
			}
			else if(!strcmp(name,"height"))
			{
				if(value2>0)
					height = value2;
			}
			else if (!strcmp(name, "gamemode"))
			{
				if (!strcmp(value, "multi"))
				{
					gamemode = MULTI_GAME;
				}
				else
				{
					gamemode = SINGLE_GAME;
				}
			}
			else if (!strcmp(name, "username"))
			{
				username = username;
			}
			else if (!strcmp(name, "host"))
			{
				if (!strcmp(value, "true"))
				{
					host = true;
				}
				else
				{
					host = false;
				}
			}
			else if (!strcmp(name, "host_addr"))
			{
				host_addr = value;
			}
		}

		infile.close();
	}
}