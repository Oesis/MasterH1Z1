#include "stdafx.h"
#include "Test.h"
#include "Inputs.h"
#include "Aimbot.h"
#include "D3D11Hooks.h"
#define _DEBUG

void InitializeHotkeys()
{
}

void InitializeConsole()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
}

DWORD WINAPI MainThread(LPVOID base)
{
	Inputs::Initialize();
	//InitializeConsole();
	InitializeHotkeys();

	//std::cout << "Wait to be in main menu to press a key" << std::endl;
	//system("pause");
	Sleep(10000);
	D3D11::Initialize();

	while (!GetAsyncKeyState(VK_END)) 
	{
		Sleep(1000 / 100);

		Aimbot::Run();

		if (GetAsyncKeyState(VK_F1))
		{
			__try{ Test::Run(); }
			__except (1) { std::cout << "[Error] in TEST" << std::endl; }
			Sleep(250);
		}

		if (GetAsyncKeyState(VK_F2))
		{
			__try { Test::RunViewMatrix(); }
			__except (1) { std::cout << "[Error] in TEST" << std::endl; }
			Sleep(250);
		}
	}

	Beep(523, 250);
	FreeConsole();
	Sleep(250);
	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
	return false;
}

BOOL WINAPI OnDllDetach()
{
	return TRUE;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
		return TRUE;
	case DLL_PROCESS_DETACH:
		if (lpReserved == nullptr)
			return OnDllDetach();
		return TRUE;
	default:
		return TRUE;
	}
	return TRUE;
}