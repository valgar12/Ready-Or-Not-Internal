#pragma once
#include "includes.h"
#include "SDK.hpp"

using namespace SDK;

inline SDK::FName StrToName(std::string str)
{
    std::wstring wstr(str.begin(), str.end());
    const wchar_t* wstr_cstr = wstr.c_str();

    return SDK::UKismetStringLibrary::Conv_StringToName(SDK::FString(TEXT(wstr_cstr)));
}
inline SDK::FName StrCToName(const wchar_t* str)
{
    return SDK::UKismetStringLibrary::Conv_StringToName(SDK::FString(TEXT(str)));
}


struct Bone {
    std::string start;
    std::string end;
};

inline Bone makeBone(std::string start, std::string end) {
    return { start, end };
}


inline std::array<Bone, 21> bones_map{
    makeBone("head","Neck_1"),
    makeBone("Neck_1","spine_2"),
    makeBone("spine_2","spine_1"),
    makeBone("spine_1","thigh_twist_2_RI"),
    makeBone("thigh_twist_2_RI","calf_hlp_back_RI"),
    makeBone("calf_hlp_back_RI","calf_twist_2_RI"),
    makeBone("calf_twist_2_RI","heel_RI"),
    makeBone("heel_RI","ball_RI"),
    makeBone("spine_1","thigh_twist_2_LE"),
    makeBone("thigh_twist_2_LE","calf_hlp_back_LE"),
    makeBone("calf_hlp_back_LE","calf_twist_2_LE"),
    makeBone("calf_twist_2_LE","heel_LE"),
    makeBone("heel_LE","ball_LE"),
    makeBone("Neck_1","upperarm_RI"),
    makeBone("upperarm_RI","lowerarm_RI"),
    makeBone("lowerarm_RI","lowerarm_twist_1_RI"),
    makeBone("lowerarm_twist_1_RI","pinky_1_RI"),
    makeBone("Neck_1","upperarm_LE"),
    makeBone("upperarm_LE","lowerarm_LE"),
    makeBone("lowerarm_LE","lowerarm_twist_1_LE"),
    makeBone("lowerarm_twist_1_LE","pinky_1_LE")
};

inline void DrawBones(SDK::USkeletalMeshComponent* mesh, SDK::APlayerController* controller, ImColor color)
{

    for (int i = 0; i < bones_map.size(); i++)
    {
        /*if (!mesh) continue;*/

        SDK::FVector bone_location1 = mesh->GetSocketLocation(StrToName(bones_map[i].start));
        SDK::FVector bone_location2 = mesh->GetSocketLocation(StrToName(bones_map[i].end));

        SDK::FVector2D bone1_w2s_2D{};
        SDK::FVector2D bone2_w2s_2D{};

        if (controller->ProjectWorldLocationToScreen(bone_location1, &bone1_w2s_2D, false) &&
            controller->ProjectWorldLocationToScreen(bone_location2, &bone2_w2s_2D, false))
        {
            Vec2 bone1_w2s = { bone1_w2s_2D.X, bone1_w2s_2D.Y };
            Vec2 bone2_w2s = { bone2_w2s_2D.X, bone2_w2s_2D.Y };

            ESP::DrawLine(bone1_w2s, bone2_w2s, color);
        }
    }
}

inline void mousemove(float tarx, float tary, int smooth)
{
	float ScreenCenterX = (1920 / 2);
	float ScreenCenterY = (1080 / 2);
	float TargetX = 0;
	float TargetY = 0;

	smooth = smooth + 3;

	if (tarx != 0)
	{
		if (tarx > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - tarx);
			TargetX /= smooth;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (tarx < ScreenCenterX)
		{
			TargetX = tarx - ScreenCenterX;
			TargetX /= smooth;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (tary != 0)
	{
		if (tary > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - tary);
			TargetY /= smooth;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (tary < ScreenCenterY)
		{
			TargetY = tary - ScreenCenterY;
			TargetY /= smooth;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}
	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
}
