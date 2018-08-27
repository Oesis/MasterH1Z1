#include "Visuals.h"
#include "CGame.h"
#include "CGraphics.h"
#include "CEntity.h"
#include "Imgui/Rubik.h"
#include "Aimbot.h"

ImFont* Visuals::m_defaultFont = nullptr;

void Visuals::DrawLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float a = (color >> 24) & 0xff; //#AARRGGBB
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;

	window->DrawList->AddLine(from, to, ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), thickness);
}

void Visuals::DrawBox(const ImVec2& feet, const ImVec2& headPosition, uint32_t color)
{
	float height = headPosition.y - feet.y;
	float width = height * 0.35;

	//Draw box
	DrawLine(ImVec2(feet.x - width, feet.y), ImVec2(feet.x + width, feet.y), 0x00000000, 2.0f);
	DrawLine(ImVec2(feet.x - width, headPosition.y), ImVec2(feet.x - width, feet.y), 0x00000000, 2.0f);

	DrawLine(ImVec2(feet.x + width, headPosition.y), ImVec2(feet.x + width, feet.y), 0x00000000, 2.0f);
	DrawLine(ImVec2(feet.x - width, headPosition.y), ImVec2(feet.x + width, headPosition.y), 0x00000000, 2.0f);

	//Draw box
	DrawLine(ImVec2(feet.x - width, feet.y), ImVec2(feet.x + width, feet.y), color, 1.5f);
	DrawLine(ImVec2(feet.x - width, headPosition.y), ImVec2(feet.x - width, feet.y), color, 1.5f);

	DrawLine(ImVec2(feet.x + width, headPosition.y), ImVec2(feet.x + width, feet.y), color, 1.5f);
	DrawLine(ImVec2(feet.x - width, headPosition.y), ImVec2(feet.x + width, headPosition.y), color, 1.5f);
}

void Visuals::DrawCircle(const ImVec2 & position, float radius, uint32_t color, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float a = (color >> 24) & 0xff; //#AARRGGBB
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;

	window->DrawList->AddCircle(position, radius, ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), 24, thickness);
}

float Visuals::DrawMessage(ImFont * pFont, const std::string & text, const ImVec2 & position, float size, uint32_t color, bool center)
{
	if (!pFont)
		return 0;

	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float a = (color >> 24) & 0xff; //#AARRGGBB
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;

	std::stringstream steam(text);
	std::string line;
	float y = 0.0f;
	int i = 0;

	while (std::getline(steam, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());
		if (center)
		{
			window->DrawList->AddText(ImGui::GetWindowFont(), ImGui::GetWindowFontSize(), ImVec2(position.x - textSize.x / 2.0f, position.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), line.c_str());
		}
		else
		{
			window->DrawList->AddText(ImGui::GetWindowFont(), ImGui::GetWindowFontSize(), ImVec2(position.x, position.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), line.c_str());
		}

		y = position.y + textSize.y * (i + 1);
		i++;
	}

	return y;
}

void Visuals::DrawHealthBar(CEntity * entity, Vector3 feet, Vector3 head)
{
	float height = feet.y - head.y;
	float width = height * 0.3f;
	DrawLine(ImVec2(feet.x - width / 2 - 8, feet.y), ImVec2(head.x - width / 2 - 8, head.y), 0x64000000, 4);
	DrawLine(ImVec2(feet.x - width / 2 - 8, feet.y), ImVec2(head.x - width / 2 - 8, feet.y - (height * entity->GetHealth() / 10000.f)), 0xFF00ff00, 4);
}

Bone arrSkeletonEnds[] = { Bone::L_wrist, Bone::R_wrist, Bone::L_ankle, Bone::R_ankle };
Bone arrSkeletonUpper[] = { Bone::hat, Bone::head, Bone::neck };
Bone arrSkeletonRightArm[] = { Bone::neck, Bone::R_shoulder, Bone::R_elbow, Bone::R_wrist };
Bone arrSkeletonLeftArm[] = { Bone::neck, Bone::L_shoulder, Bone::L_elbow, Bone::L_wrist };
Bone arrSkeletonSpine[] = { Bone::neck, Bone::spineUpper, Bone::spineMiddle, Bone::spineLower };
Bone arrSkeletonLowerRight[] = { Bone::spineLower, Bone::R_hip, Bone::R_knee, Bone::R_ankle, Bone::R_toe };
Bone arrSkeletonLowerLeft[] = { Bone::spineLower, Bone::L_hip, Bone::L_knee, Bone::L_ankle, Bone::L_toe };

std::vector<Bone> skeletonEnds(arrSkeletonEnds, arrSkeletonEnds + sizeof(arrSkeletonEnds) / sizeof(Bone));
std::vector<Bone> skeletonUpper(arrSkeletonUpper, arrSkeletonUpper + sizeof(arrSkeletonUpper) / sizeof(Bone));
std::vector<Bone> skeletonRightArm(arrSkeletonRightArm, arrSkeletonRightArm + sizeof(arrSkeletonRightArm) / sizeof(Bone));
std::vector<Bone> skeletonLeftArm(arrSkeletonLeftArm, arrSkeletonLeftArm + sizeof(arrSkeletonLeftArm) / sizeof(Bone));
std::vector<Bone> skeletonSpine(arrSkeletonSpine, arrSkeletonSpine + sizeof(arrSkeletonSpine) / sizeof(Bone));
std::vector<Bone> skeletonLowerRight(arrSkeletonLowerRight, arrSkeletonLowerRight + sizeof(arrSkeletonLowerRight) / sizeof(Bone));
std::vector<Bone> skeletonLowerLeft(arrSkeletonLowerLeft, arrSkeletonLowerLeft + sizeof(arrSkeletonLowerLeft) / sizeof(Bone));

std::vector<std::vector<Bone>> skeleton;

void Visuals::DrawSkeleton(CEntity * entity)
{
	Vector3 screen1;
	Vector3 screen2;
	if (!entity->cPlayerBase)
		return;
	Vector3 basePosition = entity->cPlayerBase->m_position;

	Vector3 head = entity->GetHeadPositionFixed() + basePosition;
	Vector3 neck = entity->GetBonePosition(Bone::neck) + basePosition;
	if (!CGraphics::WorldToScreen(&screen1, head)/* || CGraphics::WorldToScreen(&screen2, neck)*/)
		return;

	// Draw Head
	//DrawCircle(ImVec2(screen1.x, screen1.y), (screen2.y - screen1.y) * 1.5f, 0xFFFFE200, 1);
	DrawCircle(ImVec2(screen1.x, screen1.y), 5, 0xFFFFE200, 1);

	//for (auto part : skeleton)
	//{
	//	bool isFirst = true;
	//	Vector3 currentPoint = Vector3(0, 0, 0);

	//	for (auto bone : part)
	//	{
	//		Vector3 h;
	//		CGraphics::WorldToScreen(&h, entity->GetBonePosition(bone) + basePosition);
	//		if (isFirst)
	//		{
	//			isFirst = false;
	//			currentPoint = h;
	//			continue;
	//		}
	//		else
	//		{
	//			DrawLine(ImVec2(currentPoint.x, currentPoint.y), ImVec2(h.x, h.y), 0xFFFFE200, 1);
	//			currentPoint = h;
	//		}
	//	}
	//}

	//for (auto bone : skeletonEnds)
	//{
	//	Vector3 p;
	//	if (CGraphics::WorldToScreen(&p, entity->GetBonePosition(bone) + basePosition))
	//		DrawCircle(ImVec2(p.x, p.y), 3, 0xFFBD00FF, 1);
	//}
}

void Visuals::Initialize()
{
	ImGuiIO& io = ImGui::GetIO();
	/*io.Fonts->AddFontFromMemoryTTF(g_fRubik, sizeof(g_fRubik), 16.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	m_defaultFont = io.Fonts->AddFontFromMemoryTTF(g_fRubik, sizeof(g_fRubik), 16.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());*/
	//io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\STENCIL.TTF", 16.0f);
	m_defaultFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\STENCIL.TTF", 16.0f);

	// For Skeleton parts
	skeleton.push_back(skeletonUpper);
	skeleton.push_back(skeletonRightArm);
	skeleton.push_back(skeletonLeftArm);
	skeleton.push_back(skeletonSpine);
	skeleton.push_back(skeletonLowerRight);
	skeleton.push_back(skeletonLowerLeft);
}

void Visuals::Run()
{
	DrawCircle(ImVec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 100, Aimbot::isLock ? 0xFF00ff00 : 0xFFffffff);

	CEntity* localPlayer = CGame::GetFirstObject();

	for (auto entity : CGame::GetEntities())
	{
		if (entity->IsDead())
			continue;
		if (!(entity->IsPlayer() || entity->IsVehicule()))
			continue;

		Vector3 entityPos = entity->m_position;
		if (entity->IsPlayer()) 
		{
			if (!entity->cPlayerBase)
				continue;
			entityPos = entity->cPlayerBase->m_position;
		}

		Vector3 toHead, toFeet;
		bool canSeeHead = CGraphics::WorldToScreen(&toHead, entityPos + Vector3(0, PLAYER_HEIGHT, 0));
		bool canSeeFeet = CGraphics::WorldToScreen(&toFeet, entityPos);
		if (canSeeHead || canSeeFeet)
		{
			float height = toHead.y - toFeet.y;
			float width = height * 0.3f;
			int distance = entityPos.DistTo(localPlayer->cPlayerBase->m_position);

			if (entity->IsPlayer()) 
			{
				char distanceBuffer[512];
				sprintf_s(distanceBuffer, "[%i]", distance);

				DrawBox(ImVec2(toFeet.x, toFeet.y), ImVec2(toHead.x, toHead.y), entity->cActor->m_isInCar ? 0xFF007C6D : 0xFFff8d3d);
				DrawHealthBar(entity, toFeet, toHead);
				DrawMessage(m_defaultFont, distanceBuffer, ImVec2(toFeet.x, toFeet.y), 12.f, 0xFF7CC576, true);
				DrawLine(ImVec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT), ImVec2(toFeet.x, toFeet.y), 0x64ffffff, 1);
				if (distance < 200)
					DrawSkeleton(entity);
			}
			else if(entity->IsVehicule())
			{
				char nameBuffer[512];
				sprintf_s(nameBuffer, "%s [%i]", entity->m_name, distance);
				DrawMessage(m_defaultFont, nameBuffer, ImVec2(toFeet.x, toFeet.y), 12.f, 0xFFffffff, true);
			}

			else if (entity->m_type == Types::Loot)
			{
				char nameBuffer[512];
				sprintf_s(nameBuffer, "Loot [%i]", distance);
				DrawMessage(m_defaultFont, nameBuffer, ImVec2(toFeet.x, toFeet.y), 12.f, 0xFFE7D8DF, true);
			}
		}
	}
}
