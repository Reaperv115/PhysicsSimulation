#include "epch.h"
#include "Input.h"

void Engine::Input::Initialize(HWND hwnd, bool useRawInput /*= true*/)
{

    // store provided handle/flags in static members
    s_hwnd = hwnd;
    s_useRaw = useRawInput;

    // debug: report initialization
    char dbg[128];
    sprintf_s(dbg, "Input::Initialize hwnd=%p useRaw=%d\n", (void*)hwnd, (int)useRawInput);
    OutputDebugStringA(dbg);

    POINT p;
	if (GetCursorPos(&p))
	{
		ScreenToClient(hwnd, &p);
		s_mouseLastX = s_mouseX;
		s_mouseLastY = s_mouseY;
		s_mouseX = p.x;
		s_mouseY = p.y;
	}

    if (useRawInput && hwnd)
	{
		RAWINPUTDEVICE rid;
		rid.usUsagePage = 0x01; // Generic Desktop Controls
		rid.usUsage = 0x02;     // Mouse
		rid.dwFlags = RIDEV_INPUTSINK;
		rid.hwndTarget = hwnd;
        if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
        {
            char errbuf[128];
            sprintf_s(errbuf, "RegisterRawInputDevices failed: %lu\n", GetLastError());
            OutputDebugStringA(errbuf);
        }
	}
	else
		OutputDebugStringA("Raw input not enabled or hwnd is null.");

}

void Engine::Input::HandleRawInput(LPARAM lParam)
{
	if (!s_useRaw) return;

	UINT size = 0;
	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &size, sizeof(RAWINPUTDEVICE)) == (UINT)-1)
		return;
	if (size == 0) return;

	std::vector<uint8_t> buffer(size);
	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer.data(), &size, sizeof(RAWINPUTDEVICE)) != size)
		return;

	RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(buffer.data());
	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		s_mouseX += raw->data.mouse.lLastX;
		s_mouseY += raw->data.mouse.lLastY;

		POINT p;
		if (GetCursorPos(&p))
		{
			ScreenToClient(s_hwnd, &p);
			s_mouseX = p.x;
			s_mouseY = p.y;
		}
	}
}

void Engine::Input::OnMouseMove(LPARAM lparam)
{
	int x = GET_X_LPARAM(lparam);
	int y = GET_Y_LPARAM(lparam);

	//std::cout << "Mouse Move(" << x << ", " << y << ") " << std::endl;

	s_mouseDX += (x - s_mouseLastX);
	s_mouseDY += (y - s_mouseLastY);

	//std::cout << s_mouseDX << ", " << s_mouseDY << std::endl;

	s_mouseLastX = x;
	s_mouseLastY = y;
	s_mouseX = x;
	s_mouseY = y;
}

void Engine::Input::OnKeyDown(WPARAM vkey)
{
	if (vkey < 256) s_keys[static_cast<size_t>(vkey)] = 1;
}

void Engine::Input::OnKeyUp(WPARAM vkey)
{
	if (vkey < 256) s_keys[static_cast<size_t>(vkey)] = 0;
}

void Engine::Input::OnUpdate()
{
	s_prevKeys = s_keys;

	s_mouseDX = 0;
	s_mouseDY = 0;
}

bool Engine::Input::IsKeyDown(int vkey)
{
	if (vkey < 0 || vkey >= 256) return false;
	return s_keys[vkey] != 0;
}

bool Engine::Input::IsKeyPressed(int vkey)
{
	if (vkey < 0 || vkey >= 256) return false;
	return s_keys[vkey] != 0 && s_prevKeys[vkey] == 0;
}

bool Engine::Input::IsKeyReleased(int vkey)
{
	if (vkey < 0 || vkey >= 256) return false;
	return s_keys[vkey] == 0 && s_prevKeys[vkey] != 0;
}

bool Engine::Input::IsMouseButtonDown(int button)
{
	return IsKeyDown(button);
}

POINT Engine::Input::GetMousePosition()
{
	return POINT{ s_mouseX, s_mouseY };
}


POINT Engine::Input::GetMouseDelta()
{
	return POINT{ s_mouseDX, s_mouseDY };
}

int Engine::Input::GetMouseDeltaX()
{
	return s_mouseDX;
}

int Engine::Input::GetMouseDeltaY()
{
	return s_mouseDY;
}

