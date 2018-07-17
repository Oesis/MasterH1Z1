#include "stdafx.h"
#include "Test.h"
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
	InitializeConsole();
	InitializeHotkeys();

	while (!GetAsyncKeyState(VK_END)) 
	{
		Sleep(100);

		if(GetAsyncKeyState(VK_F1))
			Test::Run();
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