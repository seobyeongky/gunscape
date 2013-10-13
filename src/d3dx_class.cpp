//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: d3dx_class.cpp
//
// ����: ���̷�Ʈ�� ������ �Լ�, Ŭ���� ����
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
	
	PresentParameters.BackBufferWidth = width_; //�ȼ� ������ �ĸ� ���� �ʺ�
	PresentParameters.BackBufferHeight = height_; //�ȼ� ������ �ĸ� ���� ����
	PresentParameters.BackBufferFormat = D3DFMT_A8R8G8B8; //�ĸ� ������ �ȼ� ����
	PresentParameters.BackBufferCount = 1; //�̿��� �ĸ� ������ ��
	PresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE; //�ĸ���ۿ� �̿��� ��Ƽ ���ø� Ÿ��
	PresentParameters.MultiSampleQuality = 0; //��Ƽ ���ø� ����
	PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD; //�ø��� ü���� ���۰� ��ȯ�Ǵ� ���
	PresentParameters.hDeviceWindow = windowhandle_; //��µ� �������� �ڵ�
	PresentParameters.Windowed = true; //â���� ��üȭ���带 ����
	PresentParameters.EnableAutoDepthStencil = true; //���̷�Ʈ�� �ڵ����� ����,���ٽǹ��۸� ���������� ����
	PresentParameters.AutoDepthStencilFormat     = D3DFMT_D24S8;
	PresentParameters.Flags = 0; //�ΰ����� Ư����
	PresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //������� ����
	PresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //D3DPRESENT������ ���
	hr = d3d9 -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowhandle_, vp, &PresentParameters, &device); //����̽� ����

	if(FAILED(hr))
	{
		PresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
		
		hr = d3d9 -> CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowhandle_, vp, &PresentParameters, &device);
		if(FAILED(hr))
		{
			d3d9 -> Release();
			MessageBox(0, "CreateDevice() - FAILED", 0, 0); //���� �����ϸ� �������
			
			return false;
		}
	}
	width = width_;
	height = height_;

	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);  //�յ� ��� �׸���.
	//device->SetRenderState(D3DRS_LIGHTING, FALSE);  //����ȿ���� �����Ѵ�.(���ָ� ���� �Ÿ�)
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
	D3DXMatrixOrthoLH(&proj, 600, 400/*(float)width_ , (float)height_*/, 1.0f, 100.0f); //�ι�°���ڿ� ����°���ڴ� ���� ���μ��� ȭ�鿡 �������� �� ���ؽ�����
	device->SetTransform(D3DTS_PROJECTION,&proj);

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);  //�յ� ��� �׸���.
	device->SetRenderState(D3DRS_LIGHTING, FALSE);  //����ȿ���� �����Ѵ�.(���ָ� ���� �Ÿ�)
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


	d3d9 -> Release(); //����� ���� IDirect3D9��ü�� �� �Ⱦ��� �޸� ������


	Texture::device_init(device); //�ؽ��� Ŭ������ �������� ����� ����̽��� �Ѱ���


	


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