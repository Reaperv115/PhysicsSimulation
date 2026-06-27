#include "epch.h"
#include "AppWindow.h"

// AppWindow Implementation
Engine::AppWindow::AppWindow(HINSTANCE inst, const WindowProperties& windowprops)
	: windowProperties(windowprops)
{
	_instance = inst;
}



Engine::AppWindow::~AppWindow()
{
	std::fclose(stdout);
	FreeConsole();
}

bool Engine::AppWindow::RegisterWindowClass(const std::wstring& classname, HINSTANCE inst)
{
	WNDCLASSEXW wcex;

	LPCWSTR className = classname.c_str();

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = inst;
	wcex.hIcon = LoadIcon(inst, MAKEINTRESOURCE(IDI_ENGINE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ENGINE);
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	if (!RegisterClassExW(&wcex))
		return false;

	return true;
}


void Engine::AppWindow::Create()
{

	RegisterWindowClass(windowProperties.className.c_str(), _instance);
	InitInstance(_instance);

	// Allocate a console for debugging
	AllocConsole();
	if (!std::freopen("CONOUT$", "w", stdout))
		throw std::runtime_error("Failed to redirect stdout to console.");
	else
		std::cout << "Console allocated!" << std::endl;
}


void Engine::AppWindow::Update()
{
	HACCEL hAccelTable = LoadAccelerators(_instance, MAKEINTRESOURCE(IDC_ENGINE));
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			isRunning = false;
			break;
		}


		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
}

bool Engine::AppWindow::InitInstance(HINSTANCE hInst)
{

	windowHandle = CreateWindowW(windowProperties.className.c_str(), windowProperties.windowName.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, windowProperties.width, windowProperties.height, nullptr, nullptr, _instance, nullptr);

	if (!windowHandle)
	{
		return FALSE;
	}

	ShowWindow(windowHandle, SW_SHOW);
	SetFocus(windowHandle);
	UpdateWindow(windowHandle);

	return true;
}

// Global functions
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;
	switch (message)
	{
	case WM_INPUT:
		Engine::Input::HandleRawInput(lParam);
		break;
	case WM_MOUSEMOVE:
		Engine::Input::OnMouseMove(lParam);
		break;
	case WM_KEYDOWN:
		Engine::Input::OnKeyDown(wParam);
		break;
	case WM_KEYUP:
		Engine::Input::OnKeyUp(wParam);
		break;
	case WM_CHAR:
		break;
	case WM_LBUTTONDOWN:
		Engine::Input::OnKeyDown(VK_LBUTTON);
		break;
	case WM_LBUTTONUP:
		Engine::Input::OnKeyUp(VK_LBUTTON);
		break;
	case WM_RBUTTONDOWN:
		Engine::Input::OnKeyDown(VK_RBUTTON);
		break;
	case WM_RBUTTONUP:
		Engine::Input::OnKeyUp(VK_RBUTTON);
		break;
	case WM_MBUTTONDOWN:
		Engine::Input::OnKeyDown(VK_MBUTTON);
		break;
	case WM_MBUTTONUP:
		Engine::Input::OnKeyUp(VK_MBUTTON);
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(Engine::AppWindow::GetInstance(), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK HandleMessageRedirect(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		DestroyWindow(handle);
		return 0;
	}
	default:
	{
		return DefWindowProc(handle, msg, wparam, lparam);
	}
	}
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

HINSTANCE Engine::AppWindow::_instance;