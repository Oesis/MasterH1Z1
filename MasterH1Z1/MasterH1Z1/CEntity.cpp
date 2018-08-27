#include "stdafx.h"
#include "CEntity.h"

#define M_PI 3.14159265358979323846f

bool CEntity::IsDead()
{
	CHealthBase* healthBase = this->cHealthBase;
	if (!healthBase)
		return false;

	return this->cHealthBase->m_currentHealth <= 1;
}

bool CEntity::IsVehicule()
{
	return this->m_type == Types::ATV || this->m_type == Types::OffRoader ||
		this->m_type == Types::Pickup || this->m_type == Types::PoliceCar;
}

bool CEntity::IsPlayer()
{
	return this->m_type == Types::Player;
}

bool CEntity::IsLootItem()
{
	return this->m_type == Types::Ammo || this->m_type == Types::ClothesMedics ||
		this->m_type == Types::OtherGrenades || this->m_type == Types::StuntGrenade || 
		this->m_type == Types::Weapons;
}

int CEntity::GetHealth()
{
	return this->cHealthBase ? this->cHealthBase->m_currentHealth : 0;
}

Vector3 CEntity::GetHeadPositionFixed()
{
	Vector3 Empty = Vector3(0, 0, 0);
	auto actor = this->cActor;
	if (!actor) return Empty;

	auto start = actor->cStart;
	if (!start) return Empty;

	auto skeleton = start->cSkeleton;
	if (!skeleton) return Empty;

	auto bone = skeleton->cBone;
	if (!bone) return Empty;

	auto Head = bone->m_headBone;

	D3DXMATRIX RotateY;
	float Yaw = this->m_viewAngles.x;
	D3DXMatrixRotationY(&RotateY, (Yaw + 1.6f - M_PI / 2.f));
	D3DXVECTOR3 HeadFixed;
	D3DXVec3TransformCoord(&HeadFixed, &Head, &RotateY);

	return Vector3(HeadFixed.x, HeadFixed.y, HeadFixed.z);
}

Vector3 CEntity::GetBonePosition(Bone boneID, bool fixed)
{
	auto actor = this->cActor;
	if (!actor) return Vector3(0, 0, 0);

	auto start = actor->cStart;
	if (!start) return Vector3(0, 0, 0);

	auto skeleton = start->cSkeleton;
	if (!skeleton) return Vector3(0, 0, 0);

	auto bone = skeleton->cBone;
	if (!bone) return Vector3(0, 0, 0);

	Vector3 bonePosition = *reinterpret_cast<Vector3*>((DWORD64)bone + (DWORD64)(boneID * 12));

	if (fixed)
		GetBoneFixed(bonePosition);

	return bonePosition;
}

void CEntity::GetBoneFixed(Vector3& bonePosition)
{
	D3DXVECTOR3 dxBonePosition = D3DXVECTOR3(bonePosition.x, bonePosition.y, bonePosition.z);

	D3DXMATRIX RotateY;
	float Yaw = this->m_viewAngles.x;
	D3DXMatrixRotationY(&RotateY, (Yaw + 1.6f - M_PI / 2.f));
	D3DXVECTOR3 boneFixed;
	D3DXVec3TransformCoord(&boneFixed, &dxBonePosition, &RotateY);

	bonePosition = Vector3(boneFixed.x, boneFixed.y, boneFixed.z);
}
