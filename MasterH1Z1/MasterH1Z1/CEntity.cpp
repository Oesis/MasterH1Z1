#include "stdafx.h"
#include "CEntity.h"

bool CEntity::IsDead()
{
	CHealthBase* healthBase = this->cHealthBase;
	if (!healthBase)
		return false;

	return !this->cHealthBase->m_currentHealth;
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
