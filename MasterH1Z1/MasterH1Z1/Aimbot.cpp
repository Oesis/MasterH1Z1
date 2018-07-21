#include "Aimbot.h"
#include "CGame.h"
#include "CEntity.h"
#include "CGraphics.h"
#include "Inputs.h"

static float GetHeightFactor(CEntity* entity)
{
	float heightFactor = 1.0f;
	switch (entity->m_stance)
	{
	case Stances::Crouch: heightFactor = 0.56f; break;
	case Stances::CrouchWalk: heightFactor = 0.56f; break;
	case Stances::Prone: heightFactor = 0; break;
	case Stances::ProneMove: heightFactor = 0; break;
	}
	return heightFactor;
}

BestTarget Aimbot::GetBestTarget()
{
	BestTarget bestTarget = BestTarget(nullptr, Vector3());

	float bestAngleLenght = FLT_MAX;
	CEntity* localPlayer = CGame::GetFirstObject();

	auto entities = CGame::GetEntities();
	for (auto entity : entities)
	{
		if (entity->IsDead())
			continue;
		if (!entity->IsPlayer())
			continue;

		Vector3 toHead = Vector3();
		float velocityFactor = 0.08f;
		float heightFactor = GetHeightFactor(entity);
		Vector3 entityPos = entity->m_position;

		if (entityPos.DistToSqr(localPlayer->m_position) < 10 * 10)
			velocityFactor = 0.04f;
		Vector3 entityAimPosition = entityPos + Vector3(0, (PLAYER_HEIGHT + 0.05f) * heightFactor, 0) + entity->m_velocity * velocityFactor;
		if (CGraphics::WorldToScreen(&toHead, entityAimPosition))
		{
			float distTemp = toHead.DistTo(Vector3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
			if (/*distTemp < 300 && */distTemp < bestAngleLenght)
			{
				bestAngleLenght = distTemp;
				bestTarget.entity = entity;
				bestTarget.screenPosition = toHead;
			}
		}
	}

	return bestTarget;
}

void Aimbot::Run()
{
	CEntity* localPlayer = CGame::GetFirstObject();
	if (!localPlayer)
		return;

	BestTarget bestTarget = GetBestTarget();
	if (!bestTarget.entity) {
		std::cout << "[BestTarget] NULL" << std::endl;

		return;
	}

	Inputs::MoveMouse((int)bestTarget.screenPosition.x, (int)bestTarget.screenPosition.y);

	std::cout << "[BestTarget]" << bestTarget.entity->m_name << std::endl;
	std::cout << "Moving mouse to :" << bestTarget.screenPosition.x << ", " << bestTarget.screenPosition.y << std::endl;
}

