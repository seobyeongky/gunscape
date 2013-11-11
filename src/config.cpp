//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: config.h
//
// 내용: 설정파일 열기
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "config.h"
#include "stringconvert.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <locale>
#include <algorithm> 
#include <functional> 
#include <cctype>

using namespace std;

//
// multibyte
//
// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

//
// unicode
//
// trim from start
static inline std::wstring &ltrim(std::wstring &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::wstring &rtrim(std::wstring &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::wstring &trim(std::wstring &s) {
        return ltrim(rtrim(s));
}

namespace config
{
	int width;
	int height;

	gameMode_t gamemode;

	wstring username;
	bool host;
	wstring host_addr;

	vector<wstring> &split(const wstring &s, wchar_t delim, vector<wstring> &elems) {
		wstringstream ss(s);
		wstring item;
		while (getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}


	vector<wstring> split(const wstring &s, wchar_t delim) {
		vector<wstring> elems;
		split(s, delim, elems);
		return elems;
	}

	void SetAttribute(const wstring & key, const wstring & value)
	{
		if(key == L"width")
		{
			int n = stoi(value.c_str());
			if(n > 0)
				width = n;
		}
		else if(key == L"height")
		{
			int n = stoi(value.c_str());
			if(n > 0)
				height = n;
		}
		else if (key == L"gamemode")
		{
			if (value == L"multi")
			{
				gamemode = MULTI_GAME;
			}
			else
			{
				gamemode = SINGLE_GAME;
			}
		}
		else if (key == L"username")
		{
			username = value;
		}
		else if (key == L"host")
		{
			if (value == L"true")
			{
				host = true;
			}
			else
			{
				host = false;
			}
		}
		else if (key == L"host_addr")
		{
			host_addr = value;
		}
	}

	void LoadFromFile()
	{
		ifstream infile;
		infile.open(L"config.txt");

		if(infile.fail())
		{
			return;
		} 

		while (!infile.eof())
		{
			string line;
			getline(infile, line);
			wstring wline;
			multi2uni(line, &wline);
			auto splited = split(wline, '=');
			if (splited.size() >= 2)
			{
				SetAttribute(trim(splited[0]), trim(splited[1]));
			}
		}

		infile.close();
	}
}