#pragma once
#include "includes.h"

inline void DrawMenu()
{
	ImGui::Begin("Valgar1 Base");

	if (ImGui::BeginTabBar("tabs"))
	{
		if (ImGui::BeginTabItem("Visuals"))
		{
			ImGui::Checkbox("ESP", &gl::ESP::ESP);
			if (gl::ESP::ESP)
			{
				ImGui::Separator();
				ImGui::Checkbox("Vischeck", &gl::ESP::VisCheck);
				ImGui::Separator();
				ImGui::Checkbox("Box", &gl::ESP::ESP_Box);
				ImGui::SameLine();
				ImGui::ColorEdit3("##Box color", (float*)&gl::esp_Colors::BoxColor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Cornered Box", &gl::ESP::ESP_CorneredBox);
				ImGui::Checkbox("3D Box", &gl::ESP::ESP_3DBox);
				ImGui::Checkbox("Snaplines", &gl::ESP::ESP_Snaplines);
				ImGui::SameLine();
				ImGui::ColorEdit3("##Snaplines color", (float*)&gl::esp_Colors::SnaplineColor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Skeleton", &gl::ESP::ESP_Skeleton);
				ImGui::SameLine();
				ImGui::ColorEdit3("##Skeleton color", (float*)&gl::esp_Colors::SkeletonColor, ImGuiColorEditFlags_NoInputs);
				ImGui::Checkbox("Health Bar", &gl::ESP::HealthBar);
				ImGui::Checkbox("Names", &gl::ESP::ESP_Names);
				
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("World"))
		{
			ImGui::Checkbox("World ESP", &gl::World::World);

			ImGui::SliderFloat("Max Distance", &gl::World::MaxDistance, 20.f, 1000.f);

			ImGui::Checkbox("Civilians", &gl::World::Civilians);
			ImGui::SameLine();
			ImGui::ColorEdit3("##Civilians color", (float*)&gl::esp_Colors::Civilians, ImGuiColorEditFlags_NoInputs);
			ImGui::Checkbox("Bullets impacts", &gl::World::BulletsImpacts);
			ImGui::SameLine();
			ImGui::ColorEdit3("##BulletsImpact color", (float*)&gl::esp_Colors::BulletsEffects, ImGuiColorEditFlags_NoInputs);
			ImGui::Checkbox("Bullets Floor", &gl::World::BulletsFloor);
			ImGui::SameLine();
			ImGui::ColorEdit3("##Bulletsfloor color", (float*)&gl::esp_Colors::BulletsFloor, ImGuiColorEditFlags_NoInputs);
			ImGui::Checkbox("Evidence", &gl::World::Evidence);
			ImGui::SameLine();
			ImGui::ColorEdit3("##evi color", (float*)&gl::esp_Colors::Evidence, ImGuiColorEditFlags_NoInputs);
			ImGui::Checkbox("Doors", &gl::World::Doors);
			ImGui::SameLine();
			ImGui::ColorEdit3("##doors color", (float*)&gl::esp_Colors::Doors, ImGuiColorEditFlags_NoInputs);
			ImGui::Checkbox("Blood", &gl::World::Blood);
			ImGui::SameLine();
			ImGui::ColorEdit3("##Blood color", (float*)&gl::esp_Colors::Blood, ImGuiColorEditFlags_NoInputs);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Aimbot"))
		{
			ImGui::Checkbox("Aimbot", &gl::Aimbot::Aimbot);
			if (gl::Aimbot::Aimbot)
			{
				ImGui::Separator();
				ImGui::Checkbox("Vis Check", &gl::Aimbot::VisCheck);
				ImGui::Checkbox("Magic Bullet", &gl::Aimbot::MagicBullet);
				ImGui::SliderFloat("FOV", &gl::Aimbot::Fov, 5.f, 3000.f);
				ImGui::Checkbox("Show FOV", &gl::Aimbot::ShowFov);
				ImGui::SameLine();
				ImGui::ColorEdit3("##FOV color", (float*)&gl::esp_Colors::FovColor, ImGuiColorEditFlags_NoInputs);
				ImGui::SliderFloat("Smooth", &gl::Aimbot::Smooth, 0.f, 10.f);
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Exploits"))
		{
			ImGui::SliderInt("Max Speed", &gl::Exploits::MaxSpeed, 100, 10000);
			ImGui::Separator();
			ImGui::Checkbox("Super Speed", &gl::Exploits::SuperSpeed);
			ImGui::Checkbox("Fast fly", &gl::Exploits::FastFly);
			ImGui::Checkbox("Fast Acceleration", &gl::Exploits::FastAcceleration);
			ImGui::Checkbox("Super Jump", &gl::Exploits::SuperJump);
			ImGui::Checkbox("God Mode", &gl::Exploits::GodMode);
			ImGui::Checkbox("Unlimited Ammo", &gl::Exploits::UnlimitedAmmo);
			ImGui::Checkbox("No Recoil", &gl::Exploits::NoRecoil);
			ImGui::Checkbox("No Spread", &gl::Exploits::NoSpread);
			ImGui::Checkbox("Rapid Fire", &gl::Exploits::IncreeseFireRate);
			ImGui::Checkbox("Insta kill", &gl::Exploits::InstaKill);
			ImGui::Checkbox("Tp To Civilians [F1]", &gl::Exploits::TpToCivilians);
			ImGui::Checkbox("Tp To Enemies [F2]", &gl::Exploits::TpToEnemies);

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Misc"))
		{
			ImGui::Checkbox("Team Check", &gl::Misc::TeamCheck);
			ImGui::Checkbox("Show mouse", &gl::Misc::ShowMouse);
			ImGui::Checkbox("Crosshair", &gl::Misc::DrawCrosshair);
			if (gl::Misc::DrawCrosshair)
			{
				ImGui::SameLine();
				ImGui::ColorEdit3("##Crosshair color", (float*)&gl::esp_Colors::CrosshairColor, ImGuiColorEditFlags_NoInputs);
				ImGui::SliderFloat("Crosshair Size", &gl::Misc::CrosshairSize, 1.f, 20.f);
				ImGui::SliderFloat("Crosshair Thickness", &gl::Misc::CrosshairThickness, 1.f, 5.f);
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Editor"))
		{
			ImGui::ShowStyleEditor();
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}

inline void SetColorsFlags()
{
	ImVec4* colors = ImGui::GetStyle().Colors;

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.88f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.14f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.35f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.88f, 0.88f, 0.90f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.53f, 0.53f, 0.53f, 0.69f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.23f, 0.23f, 0.23f, 0.83f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.65f, 0.65f, 0.65f, 0.87f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.47f, 0.47f, 0.47f, 0.20f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.43f, 0.43f, 0.43f, 0.80f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.71f, 0.71f, 0.71f, 0.30f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.40f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
	colors[ImGuiCol_Button] = ImVec4(1.00f, 1.00f, 1.00f, 0.57f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.79f);
	colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.40f, 0.40f, 0.40f, 0.45f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
	colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.70f, 0.70f, 0.90f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.16f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.78f, 0.82f, 1.00f, 0.60f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.82f, 1.00f, 0.90f);
	colors[ImGuiCol_Tab] = ImVec4(0.42f, 0.42f, 0.42f, 0.79f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.76f, 0.76f, 0.76f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.81f, 0.81f, 0.81f, 0.84f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.28f, 0.28f, 0.57f, 0.82f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.35f, 0.65f, 0.84f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);



	ImGuiStyle& style = ImGui::GetStyle();

	style.FrameBorderSize = 1.f;
	style.TabBorderSize = 1.f;
	style.WindowTitleAlign.x = 0.50f;
	style.WindowPadding = ImVec2(5, 5);
	style.WindowRounding = 12.0f;
	style.FramePadding = ImVec2(6, 6);
	style.FrameRounding = 2.0f;
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 20.0f;
	style.GrabRounding = 3.0f;
	style.TabRounding = 8.f;
}
