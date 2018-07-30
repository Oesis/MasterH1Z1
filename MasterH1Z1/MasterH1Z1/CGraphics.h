#pragma once
#include <Windows.h>
#include "stdafx.h"

#define SCREEN_WIDTH	1920
#define SCREEN_HEIGHT	1080

class CCameraMatrix
{
public:
	char pad_0000[432]; //0x0000
	D3DXMATRIX m_viewMatrix; //0x01B0
}; //Size: 0x01F0

class CCamera
{
public:
	char pad_0000[48]; //0x0000
	class CCameraMatrix* cCameraMatrix; //0x0030
}; //Size: 0x0038

class CGraphics
{
public:
	static D3DXMATRIX GetGameMatrix();
	static D3DXMATRIX GetCameraMatrix();
	static bool WorldToScreen(Vector3* ScreenPos, Vector3 WorldPosition);
private:
	static void CheckPointer();
	static DWORD64 _cGraphicsPointer;
};

