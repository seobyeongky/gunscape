
#ifdef _DEBUG
#define CRTDBG_MAP _ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif



#include <windows.h>//winapi를 위해

#include <stdio.h>
#include <d3dx9.h> //다이렉트위해서
#include <time.h>
#include "window_class.h"
#include "d3dx_class.h"
#include "gamemanager.h"
#include "keyinput.h"
#include "profiler.h"
#include "sound.h"
#include "config.h"


//필요한 라이브러리
#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")
#pragma comment(lib, "winmm")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "dinput8")
#pragma comment(lib, "audiere.lib")
#pragma comment(lib, "user32.lib")
#pragma comment (lib, "gdi32")

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void DeviceRelease();
void LoadTexture(char* TextureFileName, IDirect3DTexture9** texture_);

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

	//_CrtSetBreakAlloc(166);
	//_CrtSetBreakAlloc(165);
	//_CrtSetBreakAlloc(164);
	//_CrtSetBreakAlloc(158);

	srand((unsigned int)time(NULL));

	Config config_;
	config_.init();
	//Window_Manager wnd(hinstance, 600, 400);
	Window_Manager wnd(hinstance, config_.GetWidth(), config_.GetHeight());
	InitSound(wnd.GetHandle());
	Direct_Manager* drt = Direct_Manager::CreateInstance();
	drt->init(wnd.GetHandle(),wnd.GetWidth(),wnd.GetHeight());
	Key_Manager* kym = Key_Manager::CreateInstance(hinstance, wnd.GetHandle(),wnd.GetWidth(),wnd.GetHeight());	
	Game_Manager* gmm = Game_Manager::CreateInstance();


	gmm->SetHandle(wnd.GetHandle());

	gmm->SetKeyClass(kym);
	gmm->SetDirectClass(drt);


	wnd.SetLoop(kym->Loop);
	wnd.SetLoop(gmm->Loop);
	wnd.SetLoop(drt->DrawLoop);
	wnd.SetThreadLoop(UpdateBGM);

	drt->SetLoop(gmm->Draw);


	wnd.StartLoop();

	Direct_Manager::DestroyInstance(drt);
	Game_Manager::DestroyInstance(gmm);
	Key_Manager::DestroyInstance(kym);

	_CrtDumpMemoryLeaks();

	return true;
}






