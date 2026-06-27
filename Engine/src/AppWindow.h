#pragma once
#include <windows.h>
#include "Resource.h"
#include "Input/Input.h"
#include "vendor/imgui/imgui_impl_win32.h"


namespace Engine
{

	struct WindowProperties
	{
		std::wstring windowName = L"Engine";
		std::wstring className = L"Engine Class";
		double width  = 1920, height = 1080;
	}; 

	class AppWindow
	{
	public:
		AppWindow(HINSTANCE inst, const WindowProperties& windowprops = WindowProperties());
		~AppWindow();

		static inline HINSTANCE GetInstance() { return _instance; }

		void Create();
		void Update();

		inline bool IsRunning() const { return isRunning; }
		inline HWND GetWindowHandle() { return windowHandle; }

	private:
		bool RegisterWindowClass(const std::wstring& classname, HINSTANCE inst);
		bool InitInstance(HINSTANCE hInst);
	private:
		static HINSTANCE _instance;
		HWND windowHandle;
		std::wstring appName;
		std::wstring className;
	private:
		WindowProperties windowProperties;
		bool isRunning = true;
		bool firstmouse = true;

		friend class Application;
	};

}


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	HandleMessageRedirect(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

