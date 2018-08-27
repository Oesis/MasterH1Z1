#pragma once
#include "ImGui\imgui.h"
#include "ImGui\imgui_internal.h"
#include "ImGui\imgui_impl_dx11.h"
#include "Vector3.h"
#include "CSkeleton.h"
#include <vector>

class CEntity;

class Visuals
{

public:
	static void Initialize();
	static void Run();

	static void DrawLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness);
	static void DrawBox(const ImVec2& pos, const ImVec2& headPosition, uint32_t color);
	static void DrawCircle(const ImVec2& position, float radius, uint32_t color, float thickness = 1.0f);
	static float DrawMessage(ImFont* pFont, const std::string& text, const ImVec2& position, float size, uint32_t color, bool center);

	static void DrawHealthBar(CEntity* entity, Vector3 feet, Vector3 head);
	static void DrawSkeleton(CEntity*);

	static ImFont* m_defaultFont;
};
