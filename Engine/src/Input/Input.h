#pragma once
#include <windows.h>
#include <windowsx.h>
#include <array>
#include <vector>

namespace Engine
{
	class Input
	{
	public:
		static void Initialize(HWND hwnd, bool useRawInput = true);
		static void HandleRawInput(LPARAM lParam);
		static void OnMouseMove(LPARAM lparam);
		static void OnKeyDown(WPARAM vkey);
		static void OnKeyUp(WPARAM vkey);


		static void OnUpdate();

		static bool IsKeyDown(int vkey);
		static bool IsKeyPressed(int vkey);
		static bool IsKeyReleased(int vkey);

		static bool IsMouseButtonDown(int button);

		static POINT GetMousePosition();
		static POINT GetMouseDelta();
		static int GetMouseDeltaX();
		static int GetMouseDeltaY();

	private:
		static inline HWND s_hwnd = nullptr;
		static inline bool s_useRaw = false;

		static inline std::array<uint8_t, 256> s_keys = {};
		static inline std::array<uint8_t, 256> s_prevKeys = {};

		static inline LONG s_mouseX = 0, s_mouseY = 0;
		static inline LONG s_mouseDX = 0, s_mouseDY = 0;
		static inline LONG s_mouseLastX = 0, s_mouseLastY = 0;

	};
}