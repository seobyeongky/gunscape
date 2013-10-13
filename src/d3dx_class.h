//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: d3dx_class.h
//
// 내용: 다이렉트와 연관된 함수, 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __D3DX_CLASS_H__
#define  __D3DX_CLASS_H__

#include <windows.h>
#include <d3dx9.h>
#include "FPS.h"
#include <vector>

using namespace std;

class Direct_Manager
{
	int width;
	int height;
	ID3DXFont* font; //폰트 클래스 제작할것


	Fps fps;
	IDirect3DDevice9* device;//다이렉트 디바이스
	vector<bool (*)(void)> draw_func;

	static Direct_Manager* pInstance;
	Direct_Manager();
	Direct_Manager(const Direct_Manager* rhs);
	~Direct_Manager();
public:
	static Direct_Manager* CreateInstance();
	static void DestroyInstance(Direct_Manager* pInstance_);
	
	int GetWidth(){return width;};
	int GetHeight(){return height;};
	float GetWR(){return width/600.0f;};
	float GetHR(){return height/400.0f;};
	ID3DXFont* GetFont(){return font;};

	bool init(HWND windowhandle_, int width_, int height_);
	void SetLoop(bool (*draw_func_)(void));
	static void DrawLoop();

	void TextureLoading(); //texture_const.cpp에 정의해둠

};


#endif // __D3DX_CLASS_H__