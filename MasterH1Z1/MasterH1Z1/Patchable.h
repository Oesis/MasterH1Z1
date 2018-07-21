#pragma once

#ifndef oCGame
#define oCGame		0x1446E11A0
#endif

#ifndef oCGraphics
#define oCGraphics	0x1446E2668
#endif

namespace Offsets
{
	enum class CGame
	{
		EntityCount = 0x50,
		FirstObject = 0x780
	};

	enum class CGraphics
	{
		CCamera = 0x48
	};

	////------- .:: CEntity ::. -------

	//enum class CEntity
	//{
	//	CPlayerBase = 0x300,
	//	Type = 0x3F8,
	//	Position = 0x420,
	//	Velocity = 0x430,
	//	ViewAngles = 0x530,
	//	CActor = 0x5C0,
	//	NextEntity = 0x748,
	//	Name = 0x7C0,
	//	Stance = 0x954,
	//	CHealthBase = 0x3DC8
	//};

	//enum class CHealthBase
	//{
	//	HealthValue = 0xB0
	//};

	//enum class CActor
	//{
	//	IsInCar = 0x0018
	//};

	//enum class CPlayerBase
	//{
	//	Position = 0x03F0
	//};
}