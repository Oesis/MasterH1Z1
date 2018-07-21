#pragma once
#include "Macros.h"
#include "Patchable.h"
#include "StaticEnums.h"
#include "Vector3.h"

#define PLAYER_HEIGHT 1.6f

#pragma region STRUCTS
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
}; //Size: 0x0020

class CHealthBase
{
public:
	char pad_0000[176]; //0x0000
	uint32_t m_currentHealth; //0x00B0
}; //Size: 0x00C4
#pragma endregion

class CEntity
{
public:
	char pad_0000[768]; //0x0000
	class CPlayerBase* cPlayerBase; //0x0300
	char pad_0308[240]; //0x0308
	Types m_type; //0x03F8
	char pad_03FC[36]; //0x03FC
	Vector3 m_position; //0x0420
	char pad_042C[4]; //0x042C
	Vector3 m_velocity; //0x0430
	char pad_043C[244]; //0x043C
	Vector3 m_viewAngles; //0x0530
	char pad_053C[132]; //0x053C
	class CActor* cActor; //0x05C0
	char pad_05C8[384]; //0x05C8
	class CEntity* m_nextEntity; //0x0748
	char pad_0750[112]; //0x0750
	char* m_name; //0x07C0
	char pad_07C8[396]; //0x07C8
	Stances m_stance; //0x0954
	char pad_0958[13424]; //0x0958
	class CHealthBase* cHealthBase; //0x3DC8

	// Custom Functions
	bool IsDead();

	bool IsVehicule();
	bool IsPlayer();
	bool IsLootItem();

	int GetHealth();

}; //Size: 0x4054





   //class CEntity
   //{
   //public:
   //	MAKE_GET(CPlayerBase*, cPlayerBase, Offsets::CEntity::CPlayerBase);
   //	MAKE_GET(Types, m_type, Offsets::CEntity::Type);
   //	MAKE_GET(Vector3, m_position, Offsets::CEntity::Position);
   //	MAKE_GET(Vector3, m_velocity, Offsets::CEntity::Velocity);
   //	MAKE_GET(Vector3, m_viewAngles, Offsets::CEntity::ViewAngles);
   //	MAKE_GET(CActor*, cActor, Offsets::CEntity::CActor);
   //	MAKE_GET(CEntity*, nextEntity, Offsets::CEntity::NextEntity);
   //	MAKE_GET(char*, m_name, Offsets::CEntity::Name);
   //	MAKE_GET(EntityStance, m_stance, Offsets::CEntity::Stance);
   //	MAKE_GET(CHealthBase*, cHealthBase, Offsets::CEntity::CHealthBase);
   //};