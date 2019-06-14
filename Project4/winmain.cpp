#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"
#include "dxgraphics.h"
#include "dxinput.h"
#include "dxsound.h"
#include "Game.h"

bool paused = false;

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Game_End(hWnd);
		PostQuitMessage(0);
		return 0;
	case WM_CHAR:
		if (wParam == 'p')
		{
			playSound(pause_sound);
			paused = !paused;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	//create window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	//Initialize
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPTITLE;
	wc.hIconSm = NULL;

	//Register Window
	return RegisterClassEx(&wc);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	//Register class Window
	MyRegisterClass(hInstance);

	DWORD style;
	if (FULLSCREEN)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else style = WS_TILEDWINDOW;

	//Skip InitApp
	HWND hWnd;

	//Create Window
	hWnd = CreateWindow(
		APPTITLE,									//Window Class
		APPTITLE,									//title bar
		style,										//window style
		CW_USEDEFAULT,								//x position of Window
		CW_USEDEFAULT,								//y position of Window
		SCREEN_WIDTH + BLANK_DISTANCE_WIDTH,	//width of Window
		SCREEN_HEIGHT + BLANK_DISTANCE_HEIGHT,	//height of window
		NULL,										//Parent Window
		NULL,										//Menu
		hInstance,									//app instance
		NULL);										//window Parameters
	
	/*RECT rc;
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	GetWindowRect(hWnd, &rc);
	SetWindowPos(hWnd, 0, (screenWidth - rc.right) / 2, (screenHeight - rc.bottom) / 2, 0, 0, SWP_NOZORDER | SWP_NOSIZE);*/

	
	//check error when create Window
	if (!hWnd)
		return FALSE;

	//show Window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	if (!Init_DirectInput(hWnd))
	{
		MessageBox(hWnd, "Error Initializing Direct Input", "Error", MB_OK);
		return 0;
	}
	if (!Init_Direct3D(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN))
	{
		MessageBox(hWnd, "Error Initializing Direct3D", "Error", MB_OK);
		return 0;
	}

	if (!Init_Mouse(hWnd))
	{
		MessageBox(hWnd, "Error Initializing Mouse", "Error", MB_OK);
		return 0;
	}

	if (!Init_Keyboard(hWnd))
	{
		MessageBox(hWnd, "Error Initializing Keyboard", "Error", MB_OK);
		return 0;
	}

	if (!init_SoundManager(hWnd))
	{
		MessageBox(hWnd, "Error Initializing Sound", "Error", MB_OK);
		return 0;
	}

	//Create Game
	if (!Game_Init(hWnd))
	{
		MessageBox(hWnd, "Error Initializing Game", "Error", MB_OK);
		return 0;

	}

	//loop Game
	int done = 0;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//Quit???
			if (msg.message == WM_QUIT)
				done = 1;

			//decode message, transfer to WinProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);
		else if (!paused)
			Game_Run(hWnd); //game process

	}
	return msg.wParam;

}
