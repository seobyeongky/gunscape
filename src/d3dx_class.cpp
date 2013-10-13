//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: d3dx_class.cpp
//
// 내용: 다이렉트와 연관된 함수, 클래스 정의
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#include "d3dx_class.h"
#include "image.h"
#include "texture_list.h"
#include "profiler.h"



Direct_Manager* Direct_Manager::pInstance = NULL;

Direct_Manager::Direct_Manager():
width(0), height(0), font(NULL), fps(), device(NULL)
{
}
Direct_Manager::~Direct_Manager()
{
	if(device)
		device->Release();
}

Direct_Manager* Direct_Manager::CreateInstance()
{
	if(pInstance == NULL)
		pInstance = new Direct_Manager();
	return pInstance;
}

void Direct_Manager::DestroyInstance(Direct_Manager* pInstance_)
{
	if(pInstance_ == pInstance)
		delete pInstance;
}


bool Direct_Manager::init(HWND windowhandle_, int width_, int height_)
{
	HRESULT hr;	
	IDirect3D9* d3d9;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	d3d9 -> GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	
	int vp = 0;
	
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else	
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	
	D3DPRESENT_PARAMETERS PresentParameters;
	
	PresentParameters.BackBufferWidth = width_; //픽셀 단위의 후면 버퍼 너비
	PresentParameters.BackBufferHeight = height_; //픽셀 단위의 후면 버퍼 높이
	PresentParameters.BackBufferFormat = D3DFMT_A8R8G8B8; //후면 버퍼의 픽셀 포맷
	PresentParameters.BackBufferCount = 1; //이용할 후면 버퍼의 수
	PresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE; //후면버퍼에 이용할 멀티 샘플링 타입
	PresentParameters.MultiSampleQuality = 0; //멀티 샘플링 레벨
	PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD; //플리핑 체인의 버퍼가 교환되는 방법
	PresentParameters.hDeviceWindow = windowhandle_; //출력될 윈도우의 핸들
	PresentParameters.Windowed = true; //창모드와 전체화면모드를 결정
	PresentParameters.EnableAutoDepthStencil = true; //다이렉트가 자동으로 깊이,스텐실버퍼를 관리해줄지 여부
	PresentParameters.AutoDepthStencilFormat     = D3DFMT_D24S8;
	PresentParameters.Flags = 0; //부가적인 특성들
	PresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //재생율을 설정
	PresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //D3DPRESENT집함의 멤버
	hr = d3d9 -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowhandle_, vp, &PresentParameters, &device); //디바이스 만듬

	if(FAILED(hr))
	{
		PresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
		
		hr = d3d9 -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowhandle_, vp, &PresentParameters, &device);
		if(FAILED(hr))
		{
			d3d9 -> Release();
			MessageBox(0, "CreateDevice() - FAILED", 0, 0); //전부 실패하면 에러출력
			
			return false;
		}
	}
	width = width_;
	height = height_;

	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);  //앞뒤 모두 그린다.
	//device->SetRenderState(D3DRS_LIGHTING, FALSE);  //광원효과를 무시한다.(안주면 전부 거매)
 //   device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
 //   device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	D3DXFONT_DESC fontDesc;	
	ZeroMemory(&fontDesc, sizeof(fontDesc));
	fontDesc.Height = 12*width_/600;
	fontDesc.Weight = 400;
	fontDesc.Width = 6*height_/400;
	fontDesc.Italic = false;
	fontDesc.CharSet = DEFAULT_CHARSET;
	//strcpy(fontDesc.FaceName, "Times New Roman");

	D3DXCreateFontIndirect(device, &fontDesc, &font);


	D3DXMATRIX proj;
	D3DXMatrixOrthoLH(&proj, 600, 400/*(float)width_ , (float)height_*/, 1.0f, 100.0f); //두번째인자와 세번째인자는 각각 가로세로 화면에 가득차게 할 버텍스길이
	device->SetTransform(D3DTS_PROJECTION,&proj);

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);  //앞뒤 모두 그린다.
	device->SetRenderState(D3DRS_LIGHTING, FALSE);  //광원효과를 무시한다.(안주면 전부 거매)
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
    device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);


	device->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	device->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	device->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

	device->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE ); 
	device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );


	d3d9 -> Release(); //사용이 끝난 IDirect3D9객체는 더 안쓰니 메모리 해제함


	Texture::device_init(device); //텍스쳐 클래스에 공용으로 사용할 디바이스를 넘겨줌


	


	RECT rect;
	GetWindowRect(windowhandle_, &rect);
	
	D3DDISPLAYMODE display;
	ZeroMemory(&display, sizeof(D3DDISPLAYMODE));
	
	device -> GetDisplayMode(0, &display);
	
	int WindowLeft, WindowTop;
	
	WindowLeft = ((int)display.Width - rect.right) / 2;
	WindowTop = ((int)display.Height - rect.bottom) / 2;
	SetWindowPos(windowhandle_, NULL, WindowLeft, WindowTop, 0, 0, SWP_NOSIZE);
	UpdateWindow(windowhandle_);



	TextureLoading();
	return true;
}


void Direct_Manager::SetLoop(bool (*draw_func_)(void))
{
	draw_func.push_back(draw_func_);
}



void Direct_Manager::DrawLoop()
{
#ifdef __PROFILE__
	ProfileBegin("Direct_Manager::DrawLoop()");
#endif
	if( pInstance && pInstance->device ) 
	{
		pInstance->device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);

		if(SUCCEEDED(pInstance->device->BeginScene())){
	
			for(vector<bool (*)(void)>::iterator it = pInstance->draw_func.begin(); it != pInstance->draw_func.end(); it++)
			{
				if((*it) != NULL)
					(*it)();
			}

#ifdef __PROFILE__
	ProfileBegin("fontdraw");
#endif

			char FPSString[1024];
			sprintf_s(FPSString, 1024, "%02.2fFPS", pInstance->fps.GetFps());
			RECT rc={0, 0, 200, 200};
			pInstance->font->DrawTextA(NULL, FPSString, -1, &rc, DT_SINGLELINE | DT_NOCLIP, 0xff00ff00);

#ifdef __PROFILE__
			sprintf_s(FPSString, 1024, "%s", ProfileGetBuffer());
			rc.top = 32;
			pInstance->font->DrawTextA(NULL, FPSString, -1, &rc, DT_NOCLIP, 0xffff0000);
#endif

#ifdef __PROFILE__
	ProfileEnd("fontdraw");
#endif
			pInstance->device->EndScene();	

		}
		pInstance->device->Present(0, 0, 0, 0);
	}
#ifdef __PROFILE__
	ProfileEnd("Direct_Manager::DrawLoop()");
#endif
}