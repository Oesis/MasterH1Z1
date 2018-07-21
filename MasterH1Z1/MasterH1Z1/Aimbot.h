#pragma once
#include "Vector3.h"

class CEntity;

struct BestTarget
{
	BestTarget(CEntity* entity, Vector3 screenPosition)
	{
		this->entity = entity;
		this->screenPosition = screenPosition;
	}

	Vector3 screenPosition;
	CEntity* entity;
};

class Aimbot
{
public:
	static void Run();

private:
	static BestTarget GetBestTarget();
};