//////////////////////////////////////////////////////////////////////////////////////////////////
//
// �����̸�: image.cpp
//
// ����: �̹��� Ŭ���� ����
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "image.h"
#include "texture_const.h"


const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;

IDirect3DDevice9* Texture::direct_device = NULL;
D3DXMATRIX Texture::World;
D3DXMATRIX Texture::Translation;
D3DXMATRIX Texture::Rotation;
D3DXMATRIX Texture::Scaling;


Texture::Texture(Image_File* texture_, long left_, long top_, long right_, long bottom_)
:texture(texture_),vb(NULL)
{	
	rect.left = left_;
	rect.top = top_;
	rect.right = right_;
	rect.bottom = bottom_;
}	
Texture::~Texture()
{
	if(vb)
		vb->Release();
}
void Texture::device_init(IDirect3DDevice9* device_)
{
	direct_device = device_;
}

void Texture::loading()
{
	if(direct_device) //Texture�� ���̷�Ʈ ����̽��� ����־�� �Ѵ�. ����̽��� ���� �����ϸ� �ȵȴ�.
	{//��� ���ڷ� �޴� image_file��ü�� ����̽��� ����־�� ��������. ����̽� ���� ������ ���ɼ��� ����
		float right = (float)rect.right;
		float left = (float)rect.left;
		float top = (float)rect.top;
		float bottom = (float)rect.bottom;
		
		float tex_width = right - left;
		float tex_height = bottom - top;
		float left_tu = left / texture->GetWidth();
		float right_tu = right / texture->GetWidth();
		float top_tv =  top / texture->GetHeight();
		float bottom_tv =  bottom / texture->GetHeight();
		
		direct_device->CreateVertexBuffer(
			4 * sizeof(Vertex),
			NULL,
			Vertex::FVF,
			D3DPOOL_MANAGED,
			&vb,
			NULL);
		Vertex* pVertices;
		if(SUCCEEDED(vb->Lock(0,0, (void**)&pVertices, 0))){
			pVertices[0] = Vertex( tex_width/-2.0f, tex_height/-2.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0xffffffff, left_tu, bottom_tv);
			pVertices[1] = Vertex( tex_width/2.0f, tex_height/-2.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0xffffffff, right_tu, bottom_tv);
			pVertices[2] = Vertex( tex_width/-2.0f, tex_height/2.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0xffffffff, left_tu, top_tv);
			pVertices[3] = Vertex( tex_width/2.0f, tex_height/2.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0xffffffff, right_tu, top_tv);
			vb->Unlock();
		}	
	}
}
void Texture::SetColor(D3DXCOLOR color_)
{
	Vertex *v;
	if(SUCCEEDED(vb->Lock( 0, 0, (void**)&v, 0 )))
	{
		v[0].color = color_;
		v[1].color = color_;
		v[2].color = color_;
		v[3].color = color_;
		vb->Unlock();
	}
}
void Texture::SetVertex(int size_x, int size_y)
{
	if(size_x == rect.right - rect.left && size_y == rect.top - rect.bottom)
		return;
	rect.right = rect.left+size_x;
	rect.bottom = rect.top+size_y;

	float right = (float)rect.right;
	float left = (float)rect.left;
	float top = (float)rect.top;
	float bottom = (float)rect.bottom;

	float tex_width = right - left;
	float tex_height = bottom - top;
	float right_tu = right / texture->GetWidth();
	float bottom_tv =  bottom / texture->GetHeight();

	Vertex *v;
	if(SUCCEEDED(vb->Lock( 0, 0, (void**)&v, 0 )))
	{
		//v[2].y = tex_height/2.0f;
		//v[0].tu = bottom_tv;
		//v[3].y = tex_height/2.0f;
		//v[1].tu = bottom_tv;
		v[0].x = -tex_width/2.0f;
		v[1].x = tex_width/2.0f;
		v[1].tu = right_tu;
		v[2].x = -tex_width/2.0f;
		v[3].x = tex_width/2.0f;
		v[3].tu = right_tu;
		vb->Unlock();
	}
}
bool Texture::Draw(float x_, float y_, float scale_, float rotation_)
{
	return Draw(x_, y_, scale_, scale_, rotation_, D3DCOLOR_ARGB(255,255,255,255));
}
bool Texture::Draw(float x_, float y_, float scale_x_, float scale_y_, float rotation_)
{
	return Draw(x_, y_, scale_x_, scale_y_, rotation_, D3DCOLOR_ARGB(255,255,255,255));
}

bool Texture::Draw(float x_, float y_, float scale_x_, float scale_y_, float rotation_, D3DXCOLOR color_)
{
	if(!direct_device)
		return false;

	/*D3DXMatrixIdentity(&World);	*/
	D3DXMatrixTranslation(&Translation, x_, -y_, 0.0f); //�̵� : ( ���, x, y, z(�Ⱦ�) )
	D3DXMatrixRotationZ(&Rotation, D3DX_PI*2 - rotation_);
	D3DXMatrixScaling(&Scaling, scale_x_, scale_y_, 1.0f); //ũ�� ( ���, x, y, z(�Ⱦ�) )
	D3DXMatrixMultiply(&Scaling, &Scaling, &Rotation); //��İ�
	D3DXMatrixMultiply(&World, &Scaling, &Translation);	//��İ�

	SetColor(color_);
	direct_device->SetTransform(D3DTS_WORLD, &World);
	direct_device->SetTexture(0, texture->GetPointer());
	direct_device->SetStreamSource(0,vb,0,sizeof(Vertex));
	direct_device->SetFVF(Vertex::FVF);

	if(SUCCEEDED(direct_device->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

IDirect3DTexture9* Texture::GetTexture()
{
	return texture->GetTexture();
};