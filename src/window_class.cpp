//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: window_class.cpp
//
// 내용: 윈도우와 연관된 함수, 클래스 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////


#include "window_class.h"
#include "profiler.h"

#include <process.h>


int Window_Manager::ThreadCnt = 0;
bool Window_Manager::window_break = false;
unsigned int WINAPI ThreadLoop(void *arg);



Window_Manager::Window_Manager(HINSTANCE hinstance, int width_, int height_):
handle(0), width(width_), height(height_)
{
	timeBeginPeriod(1);
	init(hinstance);
}

Window_Manager::~Window_Manager()
{
	timeEndPeriod(1);
}

bool Window_Manager::init(HINSTANCE hinstance)
{
	WNDCLASS WndClass;
	
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(hinstance, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hinstance, IDI_APPLICATION);
	WndClass.hInstance = hinstance;
	WndClass.lpfnWndProc = proc;
	WndClass.lpszClassName = "Gunscape Ver 0.2";
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	
	if( !RegisterClass(&WndClass) )
	{
		::MessageBox(0, "RegisterClass() - FAILED", 0, 0);
		return false;
	}
	
	handle = CreateWindow(WndClass.lpszClassName, WndClass.lpszClassName, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, NULL, NULL, width + 6, height + 32, NULL, NULL, WndClass.hInstance, NULL);
	
	if( !handle )
	{
		::MessageBox(0, "CreateWindow() - FAILED", 0, 0);
		return false;
	}
	
	
	ShowWindow(handle, SW_NORMAL);	
	UpdateWindow(handle);

	return true;
}

void Window_Manager::SetLoop(void (*loop_func_)(void))
{
	loop_func.push_back(loop_func_);
}
void Window_Manager::SetThreadLoop(void (*loop_func_)(void))
{
	loop_thread_func.push_back(loop_func_);
}
bool Window_Manager::StartLoop()
{
	MSG Message;
	DWORD lastTime = timeGetTime(); 
	DWORD currTime = lastTime;
	ZeroMemory(&Message, sizeof(MSG));
	
#ifdef __PROFILE__
	ProfileInit();
#endif

	unsigned int thid;
	
	for(vector<void (*)(void)>::iterator it = loop_thread_func.begin(); it != loop_thread_func.end(); it++)
	{
		if((*it) != NULL)
		{
			_beginthreadex(NULL, 0, ThreadLoop,(*it),0,&thid);
			ThreadCnt++;
			thread_id.push_back(thid);
		}
	}


	while(Message.message != WM_QUIT)
	{
#ifdef __PROFILE__
		ProfileBegin("Loop");
#endif
		if(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

#ifdef __PROFILE__
		ProfileBegin("Window_Manager::StartLoop()");
#endif
		if(!window_break)
		{
			for(vector<void (*)(void)>::iterator it = loop_func.begin(); it != loop_func.end(); it++)
			{
				if((*it) != NULL)
					(*it)();
			}
		}
#ifdef __PROFILE__
		ProfileEnd("Window_Manager::StartLoop()");
#endif

		currTime  = timeGetTime();
		while(currTime - lastTime < 16)
		{
			currTime = timeGetTime();
			Sleep(1);
		}
		lastTime = currTime;
#ifdef __PROFILE__
		ProfileEnd("Loop");
#endif
#ifdef __PROFILE__
		ProfileDumpOutputToBuffer();
#endif
	}
	
	
	for(vector<unsigned int>::iterator it = thread_id.begin(); it != thread_id.end(); it++)
	{
		PostThreadMessage((*it),WM_QUIT,Message.wParam,Message.lParam);
	}

	int i=0;
	while(ThreadCnt > 0 && i++ <= 50)
		Sleep(200);
	if(i>50)
		::MessageBox(0, "쓰레드 종료 실패", 0, 0);

	return true;
}


LRESULT CALLBACK Window_Manager::proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE) //esc를 누르면 종료되게함
		{
			DestroyWindow(hwnd);
			return 0;
		}
	case WM_ACTIVATEAPP:
		if(wParam)
		{
			window_break = false;
		}
		else
		{
			window_break = true;
		}
		break;
	case WM_SETCURSOR:   
		SetCursor(NULL);  
		break;
	}
	
	return (DefWindowProc(hwnd, msg, wParam, lParam));
}



//무한루프 돌리게 하기. 종료시 스레드 종료도 구현하기

unsigned int WINAPI ThreadLoop(void *arg)
{
	__try
	{
		__try
		{
			DWORD lastTime = timeGetTime(); 
			DWORD currTime = lastTime;	
			MSG msg;
			while(1)
			{
				if(PeekMessage(&msg,0,0,0,PM_REMOVE))
				{					
					if (msg.message==WM_QUIT)
						break;
				}

				((void(*)(void))arg)();

				currTime  = timeGetTime();
				while(currTime - lastTime < 16)
				{
					currTime = timeGetTime();
					Sleep(1);
				}
				lastTime = currTime;
			}
			return 1;
		}
		__except(1)
		{
		}
	}
	__finally
	{
		Window_Manager::ThreadCnt--;
	}
	return 0;
}
