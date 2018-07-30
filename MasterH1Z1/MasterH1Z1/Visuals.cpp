#include "Visuals.h"
#include "CGame.h"
#include "CGraphics.h"
#include "CEntity.h"

void Visuals::DrawLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float a = (color >> 24) & 0xff; //#AARRGGBB
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;

	window->DrawList->AddLine(from, to, ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), thickness);
}

void Visuals::DrawBox(const ImVec2& pos, const ImVec2& headPosition, uint32_t color)
{
	float height = headPosition.y - pos.y;
	float width = height * 0.35;

	//Draw box
	DrawLine(ImVec2(pos.x - width, pos.y), ImVec2(pos.x + width, pos.y), 0x00000000, 2.0f);
	DrawLine(ImVec2(pos.x - width, headPosition.y), ImVec2(pos.x - width, pos.y), 0x00000000, 2.0f);

	DrawLine(ImVec2(pos.x + width, headPosition.y), ImVec2(pos.x + width, pos.y), 0x00000000, 2.0f);
	DrawLine(ImVec2(pos.x - width, headPosition.y), ImVec2(pos.x + width, headPosition.y), 0x00000000, 2.0f);

	//Draw box
	DrawLine(ImVec2(pos.x - width, pos.y), ImVec2(pos.x + width, pos.y), color, 1.5f);
	DrawLine(ImVec2(pos.x - width, headPosition.y), ImVec2(pos.x - width, pos.y), color, 1.5f);

	DrawLine(ImVec2(pos.x + width, headPosition.y), ImVec2(pos.x + width, pos.y), color, 1.5f);
	DrawLine(ImVec2(pos.x - width, headPosition.y), ImVec2(pos.x + width, headPosition.y), color, 1.5f);
}

void Visuals::Run()
{
	for (auto entity : CGame::GetEntities())
	{
		if (entity->IsDead())
			continue;
		if (!entity->IsPlayer())
			continue;

		Vector3 entityPos = entity->m_position;

		Vector3 toHead, toFeet;
		bool canSeeHead = CGraphics::WorldToScreen(&toHead, entityPos + Vector3(0, PLAYER_HEIGHT, 0));
		bool canSeeFeet = CGraphics::WorldToScreen(&toFeet, entityPos);
		if (canSeeHead || canSeeFeet)
		{
			float height = toHead.y - toFeet.y;
			float width = height * 0.3f;
			DrawBox(ImVec2(toFeet.x, toFeet.y), ImVec2(toHead.x, toHead.y), 0xFFff8d3d);
		}
	}
}
