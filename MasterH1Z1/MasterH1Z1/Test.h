#pragma once
#include "stdafx.h"
#include "CGame.h"
#include "CEntity.h"
#include "CGraphics.h"

#ifndef oCGame
#define oCGame		0x1446E11A0
#endif

#ifndef oCGraphics
#define oCGraphics	0x1446E2668
#endif

static std::vector<CEntity*> GetEntities()
{
	std::vector<CEntity*> allEntities;
	CEntity* pLocalPlayer = CGame::GetFirstObject();
	if (!pLocalPlayer)
		return allEntities;

	for (CEntity* entity = pLocalPlayer->m_nextEntity; entity != nullptr; entity = entity->m_nextEntity)
	{
		allEntities.push_back(entity);
	}
	return allEntities;
}

namespace Test
{

	static void RunViewMatrix()
	{
		std::cout << "\n-----------------" << std::endl;
		D3DXMATRIX viewMatrix = CGraphics::GetCameraMatrix();

		std::cout << "[ViewMatrix] : " << std::endl;
		std::cout << std::fixed << std::setprecision(3);
		for (uint i = 0; i < 4; ++i)
		{
			std::cout << viewMatrix.m[i][0] << ", " <<
				viewMatrix.m[i][1] << ", " <<
				viewMatrix.m[i][2] << ", " <<
				viewMatrix.m[i][3] << std::endl;
		}
	}
	static void Run()
	{
		printf("h1z1.exe base address : %10X \n", GetModuleHandle(NULL));

		DWORD64 pCGame = *(DWORD64*)oCGame;
		printf("CGame pointer : %10X \n", pCGame);

		CEntity* pLocalPlayer = CGame::GetFirstObject();
		printf("Entity Count : %i \n", CGame::GetEntityCount());

		printf("LocalPlayer pointer : %10X \n", pLocalPlayer);
		if (!pLocalPlayer)
			return;
		printf("CPlayerBase pointer : %10X \n", pLocalPlayer->cPlayerBase);

		// Printing LocalPlayer
		std::cout << "Name : " << pLocalPlayer->m_name << std::endl;
		std::cout << "Stance : " << ENUM_MACRO::as_integer(pLocalPlayer->m_stance) << std::endl;

		std::cout << "Position : ";
		std::cout << pLocalPlayer->cPlayerBase->m_pelvisPosition.x;
		std::cout << ", " << pLocalPlayer->cPlayerBase->m_pelvisPosition.y;
		std::cout << ", " << pLocalPlayer->cPlayerBase->m_pelvisPosition.z << std::endl;

		std::vector<CEntity*> allEntities = CGame::GetEntities();
		std::cout << "Found " << allEntities.size() << " valid entities " << std::endl;
		for (auto entity : allEntities)
		{
			if (entity->m_type != Types::Player)
				continue;
			std::cout << "[NextObject] = " << entity << std::endl;
			std::cout << "[NextObject] " << entity->m_name << std::endl;
			std::cout << "[NextObject] (type) = " << ENUM_MACRO::as_integer(entity->m_type) << std::endl;
			std::cout << "[NextObject] (Current Health) = " << entity->GetHealth() << std::endl;
			std::cout << "[NextObject] : " <<
				entity->m_position.x << ", " <<
				entity->m_position.y << ", " <<
				entity->m_position.z << ", " <<
				std::endl;
			Vector3 toScreen;
			if(CGraphics::WorldToScreen(&toScreen, entity->m_position))
				std::cout << "[NextObject] (In Screen Position) : " <<
				toScreen.x << ", " <<
				toScreen.y << std::endl;

			std::cout << "-----------------" << std::endl;
		}


		std::cout << "\n-----------------" << std::endl;
		D3DXMATRIX viewMatrix = CGraphics::GetCameraMatrix();
		printf("CGraphics pointer : %10X \n", pCGame);

		std::cout << "[ViewMatrix] : " << std::endl;
		std::cout << std::fixed << std::setprecision(3);
		for (uint i = 0; i < 4; ++i)
		{
			std::cout << viewMatrix.m[i][0] << ", " <<
				viewMatrix.m[i][1] << ", " <<
				viewMatrix.m[i][2] << ", " <<
				viewMatrix.m[i][3] << std::endl;
		}

		Vector3 playerScreen;
		if (CGraphics::WorldToScreen(&playerScreen, pLocalPlayer->m_position + Vector3(0, 1.6f, 0)))
			std::cout << "Player W2S : " << playerScreen.x << ", " << playerScreen.y << std::endl;



	}
}
