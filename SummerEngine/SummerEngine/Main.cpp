#include <Windows.h>
#include <windowsx.h>
#include "GameEngine.h"
#include "Renderer.h"

//global game variables
HINSTANCE	handleInstance;
HWND	m_HandleWindow;

//global game functions
HRESULT InitializeWindow(_In_ HINSTANCE p_HInstance, _In_ int p_NCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void RunGameEngine();

//game 
GameEngine* m_GameEngine;
#include "CameraSystem.h"
XMFLOAT2 g_LastMousePos;

int WINAPI wWinMain(_In_ HINSTANCE p_HInstance, _In_opt_ HINSTANCE p_HPrevInstance, _In_ LPWSTR p_LpCmdLine, _In_ int p_NCmdShow)
{
	UNREFERENCED_PARAMETER(p_HPrevInstance);
	UNREFERENCED_PARAMETER(p_LpCmdLine);

	InitializeWindow(p_HInstance, p_NCmdShow);
	
	RunGameEngine();


	return 0;
}

void UpdateScene()
{
	CameraSystem* m_Cam = m_Cam->GetInstance();

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_Cam->Walk(1);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_Cam->Walk(-1);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_Cam->Strafe(-1);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_Cam->Strafe(1);
	}
	if (GetAsyncKeyState('E') & 0x8000)
	{
		m_Cam->HoverY(1);
	}
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		m_Cam->HoverY(-1);
	}
}

void OnMouseMove(WPARAM btnStae, int x, int y)
{
	CameraSystem* m_Cam = m_Cam->GetInstance();

	if (btnStae & MK_LBUTTON != 0)
	{
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - g_LastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - g_LastMousePos.y));

		m_Cam->Pitch(dy);
		m_Cam->RotateY(dx);
	}
	
	ScreenManager* t_ScreenManager = t_ScreenManager->GetInstance();
	t_ScreenManager->Update(x, y);

	g_LastMousePos.x = x;
	g_LastMousePos.y = y;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		UpdateScene();
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_MOUSEMOVE:
		OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HRESULT InitializeWindow(_In_ HINSTANCE p_HInstance, _In_ int p_NCmdShow)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = p_HInstance;
	wcex.hIcon = LoadIcon(p_HInstance, (LPCTSTR)107);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); //IDC_ARROW IDC_NO
	//ShowCursor(false);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"SummerEngine";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)107);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	handleInstance = p_HInstance;

	RECT t_rc = { 0, 0, 1920, 1080 };
	AdjustWindowRect(&t_rc, WS_CAPTION, false);


	//AdjustWindowRect( &t_rc, WS_OVERLAPPEDWINDOW, FALSE );
	m_HandleWindow = CreateWindow(wcex.lpszClassName, wcex.lpszClassName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, t_rc.right - t_rc.left, t_rc.bottom - t_rc.top, nullptr, nullptr, p_HInstance,
		nullptr);
	if (!m_HandleWindow)
		return E_FAIL;

	ShowWindow(m_HandleWindow, p_NCmdShow);
	//ChangeDisplaySettingsA(NULL, CDS_FULLSCREEN);

	return S_OK;
}
#include "TransformComponent.h"
void RunGameEngine()
{
	m_GameEngine = m_GameEngine->GetInstance();

	bool SuccessfullStart = m_GameEngine->Start(1920, 1080, m_HandleWindow);
	if (!SuccessfullStart)
	{
		//do something like error message
		PostQuitMessage(0);
	}

	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		//windows peek and gives us messages from the message queue, if not used sends them forward
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else  //no more windows messages, continue game
		{
			m_GameEngine->Update();
		}
	}

	m_GameEngine->Destroy();
}

