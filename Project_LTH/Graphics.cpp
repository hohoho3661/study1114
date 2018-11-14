#include "GameSys.h"
#include "User.h"
#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
}

void Graphics::Init(HWND _hWnd, int _width, int _height, bool _fullScreen)
{
}

void Graphics::ReleaseAll()
{
}

HRESULT Graphics::Reset()
{
	return E_NOTIMPL;
}

HRESULT Graphics::ShowBackBuffer()
{
	return E_NOTIMPL;
}

bool Graphics::isAdapterCompatible()
{
	return false;
}
