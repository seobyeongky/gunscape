//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: keyinput.h
//
// 내용: 키입력을 담당하는 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __KEY_INPUT_H__
#define  __KEY_INPUT_H__

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "coord_def.h"

enum Key_State
{
	KEY_DOWN,
	KEY_HOLD,
	KEY_UP	
};
enum Mouse_State
{
	MOUSE_LEFT_DOWN,
	MOUSE_LEFT_HOLD,
	MOUSE_LEFT_UP,
	MOUSE_RIGHT_DOWN,
	MOUSE_RIGHT_HOLD,
	MOUSE_RIGHT_UP,
};
class Key_Manager
{


	int width;
	int height;
	HWND handle;

	IDirectInput8* input;
	IDirectInputDevice8* keyboard;
	IDirectInputDevice8* mouse;

	char PreviousKeyboardState[256];
	char CurrentKeyboardState[256];
	DIMOUSESTATE PreviousMouseState;
	DIMOUSESTATE CurrentMouseState;
	POINT MousePoint;
	
	static Key_Manager* pInstance;
	Key_Manager(HINSTANCE hinstance, HWND handle_, int width_, int height_);
	Key_Manager(const Key_Manager* rhs);
	~Key_Manager();
	void Update();
public:
	static Key_Manager* CreateInstance(HINSTANCE hinstance, HWND handle, int width_, int height_);
	static void DestroyInstance(Key_Manager* pInstance_);
	static void Loop();

	bool GeyKeyState(int key_,	Key_State state_);
	bool GetMouseState(Mouse_State state_);
	float GetMouseX();
	float GetMouseY();
	coord_def GetMousePos(){return coord_def(GetMouseX(),GetMouseY());};
};

#endif // __KEY_INPUT_H__