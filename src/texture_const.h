//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: texture_const.h
//
// 내용: 텍스쳐파일, 버텍스 상수등
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __TEXTURE_CONST_H__
#define  __TEXTURE_CONST_H__

#include <d3dx9.h>
#include <string>
using namespace std;

class Image_File
{
	string name;
	IDirect3DTexture9* texture;
	float width;
	float height;
public:
	Image_File(const char* name_);
	~Image_File();

	void loading(IDirect3DDevice9* device_);
	IDirect3DTexture9* GetPointer();
	float GetWidth(){return width;};
	float GetHeight(){return height;};
	IDirect3DTexture9* GetTexture(){return texture;};
};


#endif // __TEXTURE_CONST_H__