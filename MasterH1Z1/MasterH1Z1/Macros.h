#pragma once

#define MAKE_GET(TYPE, NAME, OFFSET) \
auto NAME##() { \
	return *reinterpret_cast<TYPE*>((DWORD64) this + static_cast<__int32>(OFFSET)); \
}

//#define as_integrer(ENUM_DECL, ENUM_TYPE) \
//auto as_integrer() { \
//	return static_cast<std::underlying_type<ENUM>::type>(ENUM_TYPE); \
//}

namespace ENUM_MACRO
{
	template <typename Enumeration>
	auto as_integer(Enumeration const value)
		-> typename std::underlying_type<Enumeration>::type
	{
		return static_cast<typename std::underlying_type<Enumeration>::type>(value);
	}
}
