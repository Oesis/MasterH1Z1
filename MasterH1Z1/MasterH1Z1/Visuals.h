#pragma once
#include "ImGui\imgui.h"
#include "ImGui\imgui_internal.h"
#include "ImGui\imgui_impl_dx11.h"

class Visuals
{

public:
	static void Run();

	static void DrawLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness);
	static void DrawBox(const ImVec2& pos, const ImVec2& headPosition, uint32_t color);
};
