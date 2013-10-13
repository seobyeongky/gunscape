//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: font.cpp
//
// 내용: 폰트출력
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdarg.h>
#include "font.h"
#include "d3dx_class.h"
#include "image.h"
#include "texture_list.h"
#include "debug.h"


void d3dx_vprintf(coord_def offset_, float scale_, D3DCOLOR color_, const char* str, ...)
{
	va_list va;
	int len;
	char* buf;
	
	va_start(va, str);
	len = _vscprintf(str, va)+1;
	buf = new char[len * sizeof(char)];
	vsprintf_s(buf, len, str, va);


	float x = offset_.x, y = offset_.y;
	for(int i=0;i<len;i++)
	{
		if(buf[i] >= '0' && buf[i] <= '9')
			tex_font[buf[i]-'0'].Draw(x,y, scale_, scale_, 0.0f, color_);
		else if(buf[i] == '/')
			tex_font[10].Draw(x,y, scale_, scale_, 0.0f, color_);
		x += 14.0f*scale_;
	}
	va_end(va);
	delete[] buf;
}