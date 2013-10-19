#include <windows.h>//winapi를 위해

#include <stdio.h>
#include <d3dx9.h> //다이렉트위해서
#include <time.h>
#include <vld.h>

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

#ifdef _DEBUG
	#pragma comment(lib, "opznet-client-d.lib")
	#pragma comment(lib, "opznet-server-d.lib")
#else
	#pragma comment(lib, "opznet-client.lib")
	#pragma comment(lib, "opznet-server.lib")
#endif

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

	config::LoadFromFile();

	Window_Manager wnd(hinstance, config::width, config::height);

	InitSound(wnd.GetHandle());
	wnd.SetThreadLoop(UpdateBGM);

	Direct_Manager* drt = Direct_Manager::CreateInstance();
	drt->init(wnd.GetHandle(),wnd.GetWidth(),wnd.GetHeight());
	wnd.SetLoop(drt->DrawLoop);

	Key_Manager* kym = Key_Manager::CreateInstance(hinstance, wnd.GetHandle(),wnd.GetWidth(),wnd.GetHeight());
	wnd.SetLoop(kym->Loop);

	Game_Manager* gmm = Game_Manager::CreateInstance();
	gmm->SetHandle(wnd.GetHandle());
	gmm->SetKeyClass(kym);
	gmm->SetDirectClass(drt);
	wnd.SetLoop(gmm->Loop);

	drt->SetLoop(gmm->Draw);

	wnd.StartLoop();

	Direct_Manager::DestroyInstance(drt);
	Game_Manager::DestroyInstance(gmm);
	Key_Manager::DestroyInstance(kym);

//	_CrtDumpMemoryLeaks();

	return 0;
}






