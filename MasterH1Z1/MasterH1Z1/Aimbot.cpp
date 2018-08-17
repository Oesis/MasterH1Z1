#include "Aimbot.h"
#include "CGame.h"
#include "CEntity.h"
#include "CGraphics.h"
#include "Inputs.h"

TargetInfo Aimbot::CurrentTarget;
bool Aimbot::isLock = false;

static float GetHeightFactor(CEntity* entity)
{
	if (entity->cActor->m_isInCar)
		return 0.28f;
	switch (entity->m_stance)
	{
	case Stances::Crouch: return 0.56f; break;
	case Stances::CrouchWalk: return 0.56f; break;
	case Stances::Prone: return 0; break;
	case Stances::ProneMove: return 0; break;
	default: return 1;
	}
}


TargetInfo Aimbot::GetBestTarget()
{
	TargetInfo bestTarget;

	float bestAngleLenght = FLT_MAX;
	CEntity* localPlayer = CGame::GetFirstObject();

	auto entities = CGame::GetEntities();
	for (auto entity : entities)
	{
		TargetInfo aimbotTarget = GetTargetInfo(entity);

		if (!aimbotTarget.isInScreen || aimbotTarget.entity == nullptr)
			continue;

		float distTemp = aimbotTarget.screenPosition.DistTo(Vector3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
		if (distTemp < 100 && distTemp < bestAngleLenght)
		{
			bestAngleLenght = distTemp;
			bestTarget = aimbotTarget;
		}
	}

	return bestTarget;
}
//TargetInfo Aimbot::GetTargetInfo(CEntity* entity)
//{
//	if (!entity)
//		return TargetInfo();
//
//	if (entity->IsDead())
//		return TargetInfo();
//	if (!entity->IsPlayer())
//		return TargetInfo();
//	if (!entity->cPlayerBase)
//		return TargetInfo();
//
//	Vector3 entityVelocity = entity->m_velocity;
//	Vector3 aimPrediction = entity->m_position;
//	if (entity->cActor->m_isInCar)
//		aimPrediction = entity->cPlayerBase->m_position;
//
//	float distance = CGame::GetFirstObject()->m_position.DistTo(aimPrediction);
//	float timeToHit = distance / 500;
//
//	aimPrediction += entityVelocity * timeToHit;
//
//	//float velocityFactor = 0.095f;
//	//if (distance < 10)
//	//	velocityFactor = 0.04f;
//	//aimPrediction += entityVelocity * velocityFactor;
//
//
//	if (distance > 49)
//	{
//		float bulletDrop = (0.00365f * distance);
//		aimPrediction.y += bulletDrop;
//	}
//	if (!entity->cActor->m_isInCar)
//	{
//		if (isLock)
//			aimPrediction.y += entity->cPlayerBase->m_position.y - entity->m_position.y;
//		else
//			aimPrediction.y += PLAYER_HEIGHT * GetHeightFactor(entity);
//	}
//
//	Vector3 toHead;
//	TargetInfo targetInfo;
//	if (CGraphics::WorldToScreen(&toHead, aimPrediction))
//	{
//		targetInfo.screenPosition = toHead;
//		targetInfo.entity = entity;
//		targetInfo.isInScreen = true;
//	}
//	else
//	{
//		targetInfo.entity = nullptr;
//		targetInfo.screenPosition = Vector3(0,0,0);
//		targetInfo.isInScreen = false;
//	}
//	return targetInfo;
//}

TargetInfo Aimbot::GetTargetInfo(CEntity* entity)
{
	if (!entity)
		return TargetInfo();

	if (entity->IsDead())
		return TargetInfo();
	if (!entity->IsPlayer())
		return TargetInfo();
	if (!entity->cPlayerBase)
		return TargetInfo();

	Vector3 entityVelocity = entity->m_velocity;
	Vector3 aimPrediction = entity->cPlayerBase->m_position + entity->GetHeadPositionFixed();

	// Movement prediction
	float distance = CGame::GetFirstObject()->m_position.DistTo(aimPrediction);
	float timeToHit = distance / 550.f;
	if (distance < 20)
		aimPrediction += entityVelocity * 0.04f;
	else
		aimPrediction += entityVelocity * timeToHit;

	// Bullet drop
	if (distance > 49)
	{
		float bulletDrop = (0.00365f * distance);
		aimPrediction.y += bulletDrop;
	}

	Vector3 toHead;
	TargetInfo targetInfo;
	if (CGraphics::WorldToScreen(&toHead, aimPrediction))
	{
		targetInfo.screenPosition = toHead;
		targetInfo.entity = entity;
		targetInfo.isInScreen = true;
	}
	else
	{
		targetInfo.entity = nullptr;
		targetInfo.screenPosition = Vector3(0, 0, 0);
		targetInfo.isInScreen = false;
	}
	return targetInfo;
}
void Aimbot::Run()
{
	if (!isLock && !GetAsyncKeyState(VK_RBUTTON))
	{
		CurrentTarget = TargetInfo();
		return;
	}

	if (GetAsyncKeyState(VK_MBUTTON))
	{
		isLock = !isLock;
		Sleep(300);
	}

	CEntity* localPlayer = CGame::GetFirstObject();
	if (!localPlayer)
		return;

	if (!CurrentTarget.isInScreen)
	{
		CurrentTarget = GetBestTarget();
	}

	CurrentTarget = GetTargetInfo(CurrentTarget.entity);
	if (CurrentTarget.isInScreen)
	{
		Inputs::MoveMouse((int)CurrentTarget.screenPosition.x - SCREEN_WIDTH / 2, (int)CurrentTarget.screenPosition.y - SCREEN_HEIGHT / 2);
	}
}














//BestTarget Aimbot::GetBestTarget()
//{
//	BestTarget bestTarget = BestTarget(nullptr, Vector3());
//
//	float bestAngleLenght = FLT_MAX;
//	CEntity* localPlayer = CGame::GetFirstObject();
//
//	auto entities = CGame::GetEntities();
//	for (auto entity : entities)
//	{
//		if (entity->IsDead())
//			continue;
//		if (!entity->IsPlayer())
//			continue;
//		//if (entity->cActor->m_isInCar)
//		//	continue;
//		if (!entity->cPlayerBase)
//			continue;
//
//		Vector3 toHead = Vector3();
//		float velocityFactor = 0.08f;
//		float heightFactor = GetHeightFactor(entity);
//		Vector3 entityPos = entity->cPlayerBase->m_position;
//
//		if (entityPos.DistToSqr(localPlayer->cPlayerBase->m_position) < 10 * 10)
//			velocityFactor = 0.04f;
//		Vector3 entityAimPosition = entityPos + Vector3(0, PLAYER_HEIGHT * heightFactor, 0) + (entity->m_velocity * velocityFactor);
//		if (CGraphics::WorldToScreen(&toHead, entityAimPosition))
//		{
//			float distTemp = toHead.DistTo(Vector3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
//			if (distTemp < 80 && distTemp < bestAngleLenght)
//			{
//				//std::cout << "Aim to :" << toHead.x << ", " << toHead.y << std::endl;
//				bestAngleLenght = distTemp;
//				bestTarget.entity = entity;
//				bestTarget.screenPosition = toHead;
//			}
//		}
//	}
//
//	return bestTarget;
//}

