#include "stdafx.h"
#include "CGame.h"
#include "CEntity.h"

DWORD64 CGame::_cGamePointer = 0;
void CGame::CheckPointer()
{
	if (!_cGamePointer)
		_cGamePointer = *reinterpret_cast<DWORD64*>(oCGame);
}

int CGame::GetEntityCount()
{
	CheckPointer();
	return *reinterpret_cast<int*>(_cGamePointer + (uint)Offsets::CGame::EntityCount);
}

CEntity* CGame::GetFirstObject()
{
	CheckPointer();
	return *reinterpret_cast<CEntity**>(_cGamePointer + (uint)Offsets::CGame::FirstObject);
}

// Including localPlayer
std::vector<CEntity*> CGame::GetEntities()
{
	std::vector<CEntity*> allEntities;
	CEntity* firstObject = CGame::GetFirstObject();
	if (!firstObject)
		return allEntities;

	//allEntities.push_back(firstObject);
	for (CEntity* entity = firstObject->m_nextEntity; entity != nullptr; entity = entity->m_nextEntity)
	{
		allEntities.push_back(entity);
	}
	return allEntities;
}


