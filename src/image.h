//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: image.h
//
// 내용: 이미지 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __IMAGE_H__
#define  __IMAGE_H__

#include <d3dx9.h>

class Image_File;

struct Vertex{
	Vertex(float x_, float y_, float z_, float nx_, float ny_, float nz_, DWORD color_, float tu_, float tv_):
	x(x_), y(y_), z(z_), nx(nx_), ny(ny_), nz(nz_), color(color_), tu(tu_), tv(tv_)
	{}
	float x, y, z;
	float nx, ny, nz;
	DWORD color;
	float tu, tv;

	static const DWORD FVF;
};


class Texture
{
	Image_File* texture;
	IDirect3DVertexBuffer9* vb;
	RECT rect;

	static IDirect3DDevice9* direct_device;

	static D3DXMATRIX World; //월드매트릭스
	static D3DXMATRIX Translation; //위치
	static D3DXMATRIX Rotation; //회전
	static D3DXMATRIX Scaling; //크기
public:
	Texture(Image_File* texture_, long left_, long top_, long right_, long bottom_);
	~Texture();
	static void device_init(IDirect3DDevice9* device_); //텍스쳐클래스에 사용할 다렉디바이스 받는 함수

	void loading();
	void SetColor(D3DXCOLOR color_);
	void SetVertex(int size_x, int size_y);
	bool Draw(float x_, float y_, float scale_, float rotation_);
	bool Draw(float x_, float y_, float scale_x_, float scale_y_, float rotation_);
	bool Draw(float x_, float y_, float scale_x_, float scale_y_, float rotation_, D3DXCOLOR color_);
	int GetWidth(){return rect.right - rect.left;};
	int GetHeight(){return rect.bottom - rect.top;};
	IDirect3DTexture9* GetTexture();
};






#endif // __IMAGE_H__