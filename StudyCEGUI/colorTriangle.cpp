//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: colorTriangle.cpp
// 
// Author: Frank Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0 
//
// Desc: Renders two colored triangles, one shaded with flat shading and the
//       other shaded with Gouraud shading.  Demontrates vertex colors and,
//       the shading render states.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"

#include "GUI.h"

using namespace HaroEngine;

GUI g_gui;

//
// Globals
//

IDirect3DDevice9* Device = 0; 

const int Width  = 640;
const int Height = 480;

D3DXMATRIX WorldMatrix;

IDirect3DVertexBuffer9* Triangle = 0;



//
// Classes and Structures
//
struct ColorVertex
{
	ColorVertex(){}

	ColorVertex(float x, float y, float z, D3DCOLOR c)
	{
		_x = x;	 _y = y;  _z = z;  _color = c;
	}

	float _x, _y, _z;
	D3DCOLOR _color;

	static const DWORD FVF;
};
const DWORD ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

//
// Framework Functions
//
bool Setup()
{
	//
	// Create the vertex buffer.
	//

	Device->CreateVertexBuffer(
		3 * sizeof(ColorVertex), 
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF,
		D3DPOOL_MANAGED,
		&Triangle,
		0);

	//
	// Fill the buffer with the triangle data.
	//

	ColorVertex* v;
	Triangle->Lock(0, 0, (void**)&v, 0);

	v[0] = ColorVertex(-1.0f, 0.0f, 2.0f, D3DCOLOR_XRGB(255,   0,   0));
	v[1] = ColorVertex( 0.0f, 1.0f, 2.0f, D3DCOLOR_XRGB(  0, 255,   0));
	v[2] = ColorVertex( 1.0f, 0.0f, 2.0f, D3DCOLOR_XRGB(  0,   0, 255));

	Triangle->Unlock();

	//
	// Set the projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
			&proj,
			D3DX_PI * 0.5f, // 90 - degree
			(float)Width / (float)Height,
			1.0f,
			1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	//
	// Turn off lighting.
	//

	Device->SetRenderState(D3DRS_LIGHTING, false);


/*
	INT							m_iNx;					// X축 의 정점 수
	INT							m_iNy;					// Y축 의 정점 수
	INT							m_iNv;					// 전체 정점 수
	LPDIRECT3DVERTEXBUFFER9		m_pVB;					// Vertex Buffer

	INT							m_iNfc;					// 삼각형의 수
	LPDIRECT3DINDEXBUFFER9		m_pIB;					// Index Buffer
*/

/*
	m_iNx = 8+1;
	m_iNy = 8+1;
	m_iNv = m_iNx * m_iNy;
*/

/*
	int x, y;

	m_pDev	= pDev;

	m_iNx = 8+1;
	m_iNy = 8+1;
	m_iNv = m_iNx * m_iNy;
	m_iNfc = (m_iNx-1) * (m_iNy-1) * 2;				// 삼각형의 수

	if(FAILED(m_pDev->CreateVertexBuffer(
		m_iNv * sizeof(VtxD)
		, 0
		, VtxD::FVF
		, D3DPOOL_MANAGED
		, &m_pVB,0)))
		return -1;


	// Fill Vertex buffer

	VtxD* pVtx;
	m_pVB->Lock(0, 0, (void**)&pVtx, 0);

	for(y=0; y<m_iNy; ++y)
	{
		for(x=0; x<m_iNx; ++x)
		{
			int idx = y * m_iNx + x;

			pVtx[idx] = VtxD( (x-m_iNx/2) * 4.f
							, (y-m_iNy/2) * 4.f
							, 20.f
							, D3DCOLOR_XRGB(56, 56, 56)
								+ D3DCOLOR_XRGB(rand()%200, rand()%200, rand()%200)
							);
		}
	}

	m_pVB->Unlock();




	

	if(FAILED(m_pDev->CreateIndexBuffer(
		m_iNfc * sizeof(VtxIdx)
		, 0
		, D3DFMT_INDEX16
		, D3DPOOL_MANAGED
		, &m_pIB, 0)))
		return -1;


	// Fill Index buffer

	VtxIdx* pIdx;
	m_pIB->Lock(0, 0, (void**)&pIdx, 0);

	int k=0;
	for(y=0; y<m_iNy-1; ++y)
	{
		for(x=0; x<m_iNx-1; ++x)
		{
			int idx0 = (y+1) * m_iNx + x;

			pIdx[k] = VtxIdx(idx0, idx0+1, idx0-m_iNx);
			++k;

			int idx1 = (y+0) * m_iNx + x+1;
			pIdx[k] = VtxIdx(idx1, idx1-1, idx1+m_iNx);
			++k;
		}
	}

	m_pIB->Unlock();
*/



/*
	m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNv, 0, m_iNfc);
*/




	g_gui.Init(Device, "GUI");
	g_gui.LoadScheme("TaharezLook.scheme");
	g_gui.LoadScheme("AlfiskoSkin.scheme");
	g_gui.SetFont("DejaVuSans-10");
	g_gui.CreateWidget("AlfiskoSkin/FrameWindow", D3DXVECTOR4(0.1f, 0.1f, 0.2f, 0.5f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), "TestFrameWindow");
	CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(g_gui.CreateWidget("AlfiskoSkin/Button", D3DXVECTOR4(0.5f, 0.5f, 0.2f, 0.1f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), "TestButton"));
	testButton->setText("Hello World!");

	g_gui.SetMouseCursor("TaharezLook/MouseArrow");
	g_gui.ShowMouseCursor();

	return true;
}

void Cleanup()
{
	d3d::Release<IDirect3DVertexBuffer9*>(Triangle);
}

bool Display(float timeDelta)
{
	if( Device )
	{
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
		
		Device->BeginScene();

		Device->SetFVF(ColorVertex::FVF);
		Device->SetStreamSource(0, Triangle, 0, sizeof(ColorVertex));

		// draw the triangle to the left with flat shading
		D3DXMatrixTranslation(&WorldMatrix, -1.25f, 0.0f, 0.0f);
		Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

		Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

		// draw the triangle to the right with gouraud shading
		D3DXMatrixTranslation(&WorldMatrix, 1.25f, 0.0f, 0.0f);
		Device->SetTransform(D3DTS_WORLD, &WorldMatrix);

		Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

		
		Device->EndScene();		
		g_gui.Draw();

		Device->Present(0, 0, 0, 0);
	}
	return true;
}


//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
		
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE prevInstance, 
				   PSTR cmdLine,
				   int showCmd)
{
	if(!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}
		
	if(!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop( Display );

	Cleanup();

	Device->Release();

	return 0;
}