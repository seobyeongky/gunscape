//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: keyinput.h
//
// 내용: 키입력담당하는 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "keyinput.h"
#include "profiler.h"


Key_Manager* Key_Manager::pInstance = NULL;

Key_Manager::Key_Manager(HINSTANCE hinstance, HWND handle_, int width_, int height_):
width(width_), height(height_), handle(handle_)
{
	DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&input, NULL);
	input -> CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	input -> CreateDevice(GUID_SysMouse, &mouse, NULL);


	//DISCL_BACKGROUND : 창이 비활성화일때도 입력을 받는다.
	//DISCL_FOREGROUND : 창이 활성화일때만 입력을 받는다.

	keyboard -> SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	keyboard -> SetDataFormat(&c_dfDIKeyboard);
	keyboard -> Acquire();

	mouse -> SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	mouse -> SetDataFormat(&c_dfDIMouse);
	mouse -> Acquire();

	keyboard -> GetDeviceState(sizeof(char) * 256, &CurrentKeyboardState);
	mouse -> GetDeviceState(sizeof(DIMOUSESTATE), &CurrentMouseState);
}


Key_Manager::~Key_Manager()
{
	if(keyboard != NULL)
	{
		keyboard -> Unacquire();
		keyboard -> Release();
		keyboard = NULL;
	}

	if(mouse != NULL)
	{
		mouse -> Unacquire();
		mouse -> Release();
		mouse = NULL;
	}

	if(input != NULL)
	{
		input -> Release();
		input = NULL;
	}
}

Key_Manager* Key_Manager::CreateInstance(HINSTANCE hinstance, HWND handle, int width_, int height_)
{
	if(pInstance == NULL)
		pInstance = new Key_Manager(hinstance, handle, width_, height_);
	return pInstance;
}

void Key_Manager::DestroyInstance(Key_Manager* pInstance_)
{
	if(pInstance_ == pInstance)
		delete pInstance;
}




void Key_Manager::Update()
{
	keyboard -> Acquire();
	mouse -> Acquire();

	CopyMemory(PreviousKeyboardState, CurrentKeyboardState, sizeof(char) * 256);
	keyboard -> GetDeviceState(sizeof(char) * 256, &CurrentKeyboardState);

	PreviousMouseState = CurrentMouseState;
	mouse -> GetDeviceState(sizeof(DIMOUSESTATE), &CurrentMouseState);

	GetCursorPos(&MousePoint);
	ScreenToClient(handle, &MousePoint);
	MousePoint.x -= width/2;
	MousePoint.y -= height/2;
}

void Key_Manager::Loop()
{
	if(pInstance != NULL)
	{
		pInstance->Update();
	}
}


bool Key_Manager::GeyKeyState(int key_,	Key_State state_)
{
	switch(state_)
	{
	case KEY_DOWN:
		return (PreviousKeyboardState[key_] == 0x00 && CurrentKeyboardState[key_] == -0x80);
		break;
	case KEY_HOLD:
		return (CurrentKeyboardState[key_] == -0x80);
		break;
	case KEY_UP:
		return (PreviousKeyboardState[key_] == -0x80 && CurrentKeyboardState[key_] == 0x00);
		break;
	}
	return false;
}
bool Key_Manager::GetMouseState(Mouse_State state_)
{
	switch(state_)
	{
	case MOUSE_LEFT_DOWN:
		return (PreviousMouseState.rgbButtons[0] == 0x00 && CurrentMouseState.rgbButtons[0] == 0x80);
		break;
	case MOUSE_LEFT_HOLD:
		return (CurrentMouseState.rgbButtons[0] == 0x80);
		break;
	case MOUSE_LEFT_UP:
		return (PreviousMouseState.rgbButtons[0] == 0x80 && CurrentMouseState.rgbButtons[0] == 0x00);
		break;
	case MOUSE_RIGHT_DOWN:
		return (PreviousMouseState.rgbButtons[1] == 0x00 && CurrentMouseState.rgbButtons[1] == 0x80);
		break;
	case MOUSE_RIGHT_HOLD:
		return (CurrentMouseState.rgbButtons[1] == 0x80);
		break;
	case MOUSE_RIGHT_UP:
		return (PreviousMouseState.rgbButtons[1] == 0x80 && CurrentMouseState.rgbButtons[1] == 0x00);
		break;
	}
	return false;
}

float Key_Manager::GetMouseX()
{
	return MousePoint.x*600.0f/width;
}
float Key_Manager::GetMouseY()
{
	return MousePoint.y*400.0f/height;
}