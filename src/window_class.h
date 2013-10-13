//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: window_class.h
//
// 내용: 윈도우와 연관된 함수, 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __WINDOW_CLASS_H__
#define  __WINDOW_CLASS_H__

#include <windows.h>
#include <vector>

using namespace std;

class Window_Manager
{
	HWND handle;
	int width;
	int height;
	static bool window_break;
	vector<void (*)(void)> loop_func;
	vector<void (*)(void)> loop_thread_func;
	vector<unsigned int> thread_id;

	bool init(HINSTANCE hinstance);
public:
	static int ThreadCnt;

	Window_Manager(HINSTANCE hinstance, int width_, int height_);
	~Window_Manager();

	HWND GetHandle(){return handle;};
	int GetWidth(){return width;};
	int GetHeight(){return height;};

	void SetLoop(void (*loop_func_)(void));
	void SetThreadLoop(void (*loop_func_)(void));
	bool StartLoop();
	

	static LRESULT CALLBACK proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


};


#endif // __WINDOW_CLASS_H__