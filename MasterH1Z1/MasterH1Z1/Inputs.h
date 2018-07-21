#pragma once
#include <iostream>
#include <Windows.h>

// using Inputs::KeyListener[VKkey] to get the corresponding keypress
namespace Inputs
{
	void Initialize();

	extern LONG_PTR oriWndProc;

	extern bool KeyListener[256]; // corresponding indeces will be set true when message is posted to WndProc

	LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void MoveMouse(int x, int y);
}
