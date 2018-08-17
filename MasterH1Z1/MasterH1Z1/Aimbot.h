#pragma once
#include "Vector3.h"

class CEntity;

struct TargetInfo
{
	TargetInfo()
	{
		this->entity = nullptr;
		this->screenPosition = Vector3(0,0,0);
		this->isInScreen = false;
	}
	//TargetInfo(CEntity* entity, Vector3 screenPosition)
	//{
	//	this->entity = entity;
	//	this->screenPosition = screenPosition;
	//	this->isInScreen = false;
	//}

	Vector3 screenPosition;
	CEntity* entity;
	bool isInScreen;
};

class Aimbot
{
public:
	static void Run();

	static TargetInfo CurrentTarget;
	static bool isLock;

private:
	static TargetInfo GetBestTarget();
	static TargetInfo GetTargetInfo(CEntity* entity);
};