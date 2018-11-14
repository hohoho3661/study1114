#include "GameSys.h"
#include "User.h"


// ================================================================================================

HWND		g_hWnd;
HINSTANCE	g_hInst;

// ================================================================================================
int		WINAPI	WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT WINAPI	WinProc(HWND, UINT, WPARAM, LPARAM);

bool			CreateMainWindow(HWND&, HINSTANCE, int);

// ================================================================================================
int		WINAPI	WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;
	HWND	hWnd;

	if (!CreateMainWindow(hWnd, hInstance, nCmdShow))
		return 1;

	try
	{
		// Graphics 객체 생성 위치

		// Game 관련 시스템 객체 생성 및 초기화 위치

		ZeroMemory(&msg, sizeof(msg));

		while (true)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// 게임 루프 처리
			}
		}
	}
	catch (const GameError &err)
	{
		MessageBox(NULL, err.getMessage(), "Error", MB_OK);
	}
	catch (...)
	{
		MessageBox(NULL, "Unknown Error Occured in Game.", "Error", MB_OK);
	}

	return (int)msg.wParam;
}

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool CreateMainWindow(HWND& hWnd, HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	wcx.cbSize = sizeof(wcx);

	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcx.hIconSm = NULL;
	wcx.hInstance = hInstance;
	wcx.lpfnWndProc = (WNDPROC)WinProc;
	wcx.lpszClassName = CLASS_NAME;
	wcx.lpszMenuName = NULL;
	wcx.style = CS_HREDRAW | CS_VREDRAW;

	if (RegisterClassEx(&wcx) == 0)
		return false;

	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	hWnd = CreateWindow(
		CLASS_NAME,
		GAME_TITLE,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GAME_WIDTH,
		GAME_HEIGHT,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
		return false;

	if (!FULLSCREEN)
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		MoveWindow(hWnd, 0, 0, GAME_WIDTH + (GAME_WIDTH - clientRect.right),
			GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom), TRUE);
	}


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return true;
}