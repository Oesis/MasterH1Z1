#pragma once
#include <Windows.h>
#include <vector>

class CEntity;

class CGame
{
public:
	static int GetEntityCount();
	static CEntity* GetFirstObject();

	static std::vector<CEntity*> GetEntities();

private:
	static void CheckPointer();
	static DWORD64 _cGamePointer;
};
