//#include "stdafx.h"
//#include "Overlay.h"
//#include <Windows.h>
//#include <d3dx9.h>
//#include <d3d9.h>
//#include <dwmapi.h>
//#include <TlHelp32.h>
//#include <string>
//#pragma comment(lib, "d3dx9.lib")
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "dwmapi.lib")
//
////
//int Width = 800;
//int Height = 600;
//HWND hWnd;
//MSG Message;
//HWND TargetWnd;
//HINSTANCE hInstance;
//RECT TargetRect;
//RECT CheckWnd;
//HINSTANCE  inj_hModule;
//const MARGINS Margin = { 0, 0, Width, Height };
//
//IDirect3D9Ex* dx_Object = NULL;
//IDirect3DDevice9Ex* dx_Device = NULL;
//D3DPRESENT_PARAMETERS dx_Param;
//ID3DXFont* dx_Font = 0;
//
//LRESULT CALLBACK Proc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
//{
//	switch (Message)
//	{
//	case WM_PAINT:
//		DwmExtendFrameIntoClientArea(hWnd, &Margin);
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		return 0;
//
//	default:
//		return DefWindowProc(hWnd, Message, wParam, lParam);
//	}
//
//	return 0;
//}
//BOOL RegisterDLLWindowClass(wchar_t szClassName[])
//{
//	WNDCLASSEX OverlayWnd;
//
//	OverlayWnd.cbClsExtra = 0;
//	OverlayWnd.cbSize = sizeof(WNDCLASSEX);
//	OverlayWnd.cbWndExtra = 0;
//	OverlayWnd.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
//	OverlayWnd.hCursor = LoadCursor(0, IDC_ARROW);
//	OverlayWnd.hIcon = LoadIcon(0, IDI_APPLICATION);
//	OverlayWnd.hIconSm = LoadIcon(0, IDI_APPLICATION);
//	OverlayWnd.hInstance = hInstance;
//	OverlayWnd.lpfnWndProc = Proc;
//	OverlayWnd.lpszClassName = "Bf4_Amazing_overlay";
//	OverlayWnd.lpszMenuName = "Bf4_Amazing_overlay";
//	OverlayWnd.style = CS_HREDRAW | CS_VREDRAW;
//	MSG messages;
//
//	if (!RegisterClassEx(&OverlayWnd))
//		return 0;
//}
//DWORD WINAPI ThreadProc(LPVOID lpParam)
//{
//
//	wchar_t *pString = reinterpret_cast<wchar_t *> (lpParam);
//	RegisterDLLWindowClass((wchar_t*)"InjectedDLLWindowClass");
//	TargetWnd = FindWindow("Window Injected Into ClassName", "Window Injected Into Caption");
//	hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_COMPOSITED | WS_EX_TRANSPARENT, "Bf4_Amazing_overlay", "Bf4_Amazing_overlay", WS_EX_TOPMOST | WS_POPUP, 100, 100, 1024, 786, NULL, NULL, NULL, inj_hModule);
//	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, ULW_COLORKEY);
//	SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
//	ShowWindow(hWnd, SW_SHOW);
//	DirectXxInit(hWnd);
//
//	//memory.init("bf4.exe");
//
//	for (;;)
//	{
//		if (PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&Message);
//			DispatchMessage(&Message);
//		}
//
//		TargetWnd = FindWindow(0, "Battlefield 4");
//		GetWindowRect(TargetWnd, &TargetRect);
//		MoveWindow(hWnd, TargetRect.left, TargetRect.top, TargetRect.right - TargetRect.left, TargetRect.bottom - TargetRect.top, true);
//
//		if (!TargetWnd)
//		{
//			exit(0);
//		}
//
//		Render();
//		Sleep(1);
//	}
//	return 0;
//
//}
//BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
//{
//	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
//		inj_hModule = hModule;
//		CreateThread(0, NULL, ThreadProc, (LPVOID)L"Window Title", NULL, NULL);
//	}
//	return TRUE;
//}
//
//
//int Render()
//{
//	dx_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
//	dx_Device->BeginScene();
//
//	if (TargetWnd == GetForegroundWindow())
//	{
//
//
//
//		DrawShadowText((char*)"Unknown Cheats DLL overlay by the famous Bostriche!", 30, 10, 128, 132, 200);
//
//
//	}
//	dx_Device->EndScene();
//	dx_Device->PresentEx(0, 0, 0, 0, 0);
//	return 0;
//}