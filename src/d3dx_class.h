//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: d3dx_class.h
//
// ����: ���̷�Ʈ�� ������ �Լ�, Ŭ����
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
	ID3DXFont* font; //��Ʈ Ŭ���� �����Ұ�


	Fps fps;
	IDirect3DDevice9* device;//���̷�Ʈ ����̽�
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

	void TextureLoading(); //texture_const.cpp�� �����ص�

};


#endif // __D3DX_CLASS_H__