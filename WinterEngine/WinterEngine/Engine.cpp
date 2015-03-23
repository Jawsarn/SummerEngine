#include <Windows.h>
#include "GraphicEngineInterface.h"

// this is just test at the moment, to get things started, will be sorting this when it comes important.
//global game variables
HINSTANCE	handleInstance;
HWND	m_HandleWindow;

HRESULT InitializeWindow(_In_ HINSTANCE p_HInstance, _In_ int p_NCmdShow);
#define OEMRESOURCE


int WINAPI wWinMain(_In_ HINSTANCE p_HInstance, _In_opt_ HINSTANCE p_HPrevInstance, _In_ LPWSTR p_LpCmdLine, _In_ int p_NCmdShow)
{
	UNREFERENCED_PARAMETER(p_HPrevInstance);
	UNREFERENCED_PARAMETER(p_LpCmdLine);
	
	HRESULT hr = InitializeWindow(p_HInstance, p_NCmdShow);
	if (FAILED(hr))
		return 0;

	GraphicEngineInterface* m_Engine = m_Engine->GetInstance();
	m_Engine->Initialize(m_HandleWindow,1024,1024);

	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		//windows peek and gives us messages from the message queue, if not used sends them forward
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
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
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_MOUSEMOVE:
		//OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
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

	RECT t_rc = { 0, 0, 1024, 1024 };
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