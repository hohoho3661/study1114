#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif// #ifdef _DEBUG

#include "Constants.h"
#include "GameError.h"

#define COLOR_ARGB DWORD
#define SETCOLOR_AGRB(a, r, g, b) \
		((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16))|(((g)&0xff)<<8)|(((b)&0xff)))

class Graphics
{
private:
	LPDIRECT3D9				direct3D;
	LPDIRECT3DDEVICE9		device3D;
	D3DPRESENT_PARAMETERS	d3dpp;
	D3DDISPLAYMODE			pMode;

	HRESULT					result;
	HWINEVENTHOOK			hWnd;

	bool					fullScreen;

	int						width;
	int						height;

	COLOR_ARGB				backColor;

	void					InitD3DPP();
public:
	Graphics();
	~Graphics();

	void	Init(HWND _hWnd, int _width, int _height, bool _fullScreen);
	void	ReleaseAll();

	HRESULT	Reset();

	HRESULT	ShowBackBuffer();

	bool	isAdapterCompatible();
};

