#pragma once
#include "stdafx.h"

class CPlayerBase
{
public:
	char pad_0000[1008]; //0x0000
	Vector3 m_position; //0x03F0
	char pad_03FC[80]; //0x03FC
}; //Size: 0x044C

class CActor
{
public:
	char pad_0000[24]; //0x0000
	uint32_t m_isInCar; //0x0018
	char pad_001C[4]; //0x001C
}; //Size: 0x0020

class CEntity
{
public:
	char pad_0000[768]; //0x0000
	class CPlayerBase* pCPlayerBase; //0x0300
	char pad_0308[240]; //0x0308
	uint32_t m_type; //0x03F8
	char pad_03FC[36]; //0x03FC
	Vector3 m_position; //0x0420
	char pad_042C[4]; //0x042C
	Vector3 m_velocity; //0x0430
	char pad_043C[388]; //0x043C
	class CActor* pCActor; //0x05C0
	char pad_05C8[524]; //0x05C8
	char m_name[20]; //0x07D4
	char pad_07E8[380]; //0x07E8
	uint32_t m_stance; //0x0964
	char pad_0968[756]; //0x0968
}; //Size: 0x0C5C

class CGame
{
public:
	char pad_0000[1920]; //0x0000
	class CEntity* FirstObject; //0x0780
}; //Size: 0x0788

namespace Test
{
	static void Run()
	{
		printf("h1z1.exe base address : %10X \n", GetModuleHandle(NULL));

		DWORD64 pCGame = *(DWORD64*)0x1446E1380;
		printf("CGame pointer : %10X \n", pCGame);

		CGame* cgame = (CGame*)0x1446E1380;
		CEntity* pLocalPlayer = cgame->FirstObject;
		printf("LocalPlayer pointer : %10X \n", pLocalPlayer);

		// Printing LocalPlayer
		//std::cout << "Name : " << pLocalPlayer->m_name << std::endl;

		std::cout << "Position : ";
		std::cout << pLocalPlayer->pCPlayerBase->m_position.x;
		std::cout << ", " << pLocalPlayer->pCPlayerBase->m_position.y;
		std::cout << ", " << pLocalPlayer->pCPlayerBase->m_position.z << std::endl;
	}
}
