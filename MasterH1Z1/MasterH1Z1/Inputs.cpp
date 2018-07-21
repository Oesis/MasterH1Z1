#include "Inputs.h"

LONG_PTR Inputs::oriWndProc = NULL; //instantiate
bool Inputs::KeyListener[256] = {};

void Inputs::Initialize()
{
	//Inputs::oriWndProc = SetWindowLongPtr(FindWindow(NULL, "H1Z1 v1.0.261.361112 id=ec4f51f7"), GWLP_WNDPROC, (LONG_PTR)Inputs::WndProc);
	Inputs::oriWndProc = SetWindowLongPtr(GetForegroundWindow(), GWLP_WNDPROC, (LONG_PTR)Inputs::WndProc);
}

LRESULT __stdcall Inputs::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) // WndProc wrapper
{ // this will be called each time WndProc is called.
	switch (uMsg) // Each keystroke will PostMessage with uMsg down and wParam the key.
	{
	case WM_LBUTTONDOWN:
		Inputs::KeyListener[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		Inputs::KeyListener[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		Inputs::KeyListener[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		Inputs::KeyListener[VK_RBUTTON] = false;
		break;
	case WM_MBUTTONDOWN:
		Inputs::KeyListener[VK_MBUTTON] = true;
		break;
	case WM_MBUTTONUP:
		Inputs::KeyListener[VK_MBUTTON] = false;
		break;
	case WM_XBUTTONDOWN:
	{
		if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
		{
			Inputs::KeyListener[VK_XBUTTON1] = true;
		}
		else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
		{
			Inputs::KeyListener[VK_XBUTTON2] = true;
		}
		break;
	}
	case WM_XBUTTONUP:
	{
		if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
		{
			Inputs::KeyListener[VK_XBUTTON1] = false;
		}
		else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
		{
			Inputs::KeyListener[VK_XBUTTON2] = false;
		}
		break;
	}
	case WM_KEYDOWN:
		Inputs::KeyListener[wParam] = true;
		break;
	case WM_KEYUP:
		Inputs::KeyListener[wParam] = false;
		break;
	default:
		break;
	}

	return CallWindowProcW((WNDPROC)Inputs::oriWndProc, hWnd, uMsg, wParam, lParam); // Call the original Function
}

//void Inputs::MoveMouse(int x, int y)
//{
//	mouse_event(0x0001, x, y, 0, 0);
//	Sleep(5);
//}

void Inputs::MoveMouse(int x, int y)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dx = (LONG)x;
	Input.mi.dy = (LONG)y;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &Input, sizeof(INPUT));
}
