#include "stdafx.h"
#include "CGraphics.h"

DWORD64 CGraphics::_cGraphicsPointer = 0;
void CGraphics::CheckPointer()
{
	if (!_cGraphicsPointer)
		_cGraphicsPointer = *reinterpret_cast<DWORD64*>(oCGraphics);
}

D3DXMATRIX CGraphics::GetGameMatrix()
{
	CheckPointer();
	CCamera* cCamera = *reinterpret_cast<CCamera**>(_cGraphicsPointer + (uint)Offsets::CGraphics::CCamera);
	if (!cCamera || !cCamera->cCameraMatrix)
		return D3DXMATRIX();

	D3DXMATRIX gameMatrix;
	D3DXMATRIX viewMatrix = cCamera->cCameraMatrix->m_viewMatrix;
	gameMatrix.m[0][0] = viewMatrix.m[0][0];
	gameMatrix.m[0][1] = viewMatrix.m[1][0];
	gameMatrix.m[0][2] = viewMatrix.m[2][0];
	gameMatrix.m[0][3] = viewMatrix.m[3][0];

	gameMatrix.m[1][0] = -viewMatrix.m[0][1];
	gameMatrix.m[1][1] = -viewMatrix.m[1][1];
	gameMatrix.m[1][2] = -viewMatrix.m[2][1];
	gameMatrix.m[1][3] = -viewMatrix.m[3][1];

	gameMatrix.m[2][0] = viewMatrix.m[0][2];
	gameMatrix.m[2][1] = viewMatrix.m[1][2];
	gameMatrix.m[2][2] = viewMatrix.m[2][2];
	gameMatrix.m[2][3] = viewMatrix.m[3][2];

	gameMatrix.m[3][0] = viewMatrix.m[0][3];
	gameMatrix.m[3][1] = viewMatrix.m[1][3];
	gameMatrix.m[3][2] = viewMatrix.m[2][3];
	gameMatrix.m[3][3] = viewMatrix.m[3][3];
	return gameMatrix;
}

D3DXMATRIX CGraphics::GetCameraMatrix()
{
	CheckPointer();
	CCamera* cCamera = *reinterpret_cast<CCamera**>(_cGraphicsPointer + (uint)Offsets::CGraphics::CCamera);
	if (!cCamera || !cCamera->cCameraMatrix)
		return D3DXMATRIX();
	return cCamera->cCameraMatrix->m_viewMatrix;
}

bool CGraphics::WorldToScreen(Vector3 * ScreenPos, Vector3 WorldPosition)
{
	D3DXMATRIX gameMatrix = GetGameMatrix();
	float w = 0.0f;

	ScreenPos->x = gameMatrix.m[0][0] * WorldPosition.x + gameMatrix.m[0][1] * WorldPosition.y + gameMatrix.m[0][2] * WorldPosition.z + gameMatrix.m[0][3];
	ScreenPos->y = gameMatrix.m[1][0] * WorldPosition.x + gameMatrix.m[1][1] * WorldPosition.y + gameMatrix.m[1][2] * WorldPosition.z + gameMatrix.m[1][3];
	w = (float)(gameMatrix.m[3][0] * WorldPosition.x + gameMatrix.m[3][1] * WorldPosition.y + gameMatrix.m[3][2] * WorldPosition.z + gameMatrix.m[3][3]);

	if (w < 0.01f)
		return false;

	float invw = 1.0f / w;
	ScreenPos->x *= invw;
	ScreenPos->y *= invw;

	float x = SCREEN_WIDTH / 2;
	float y = SCREEN_HEIGHT / 2;

	x += 0.5f * (float)ScreenPos->x * SCREEN_WIDTH + 0.5f;
	y -= 0.5f * (float)ScreenPos->y * SCREEN_HEIGHT + 0.5f;

	ScreenPos->x = x;
	ScreenPos->y = y;
	ScreenPos->z = 0;
	return true;
}
