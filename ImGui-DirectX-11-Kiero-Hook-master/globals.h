#pragma once
#include "includes.h"
#include "SDK.hpp"

inline bool showmenu = true;
inline bool alive = true;
inline ImDrawList* draw_list{};
inline std::vector<SDK::AActor*> PlayerList{};
inline std::vector<SDK::AActor*> ActorList{};
inline SDK::UEngine* Engine{};
inline SDK::UWorld* World{};
inline SDK::TArray<SDK::AActor*> actors{};
inline SDK::AActor* actor_list{};
inline SDK::APlayerController* MyController{};
inline float aimbot_distance{};
inline SDK::ABaseMagazineWeapon* weapon{};
inline std::vector<SDK::AActor*> WorldActors{};
inline SDK::FVector closestCivilianLocation{};


enum BoxTypes
{
	Nornmal = 0,
	Cornered = 1,
	Box_3D = 2
};

namespace Colors
{
	inline ImColor White(255.f, 255.f, 255.f);
	inline ImColor Black(0.f, 0.f, 0.f);
	inline ImColor Red(255.f, 0.f, 0.f);
	inline ImColor DarkRed(0.700f, 0.f, 0.f);
	inline ImColor Green(0.f, 255.f, 0.f);
	inline ImColor DarkGreen(0.f, 0.600f, 0.f);
	inline ImColor Blue(0.f, 0.f, 255.f);
	inline ImColor DarkBlue(0.f, 0.f, 0.700f);
	inline ImColor Pink(255.f, 0.f, 255.f);
	inline ImColor Cian(0.f, 255.f, 255.f);
	inline ImColor Yellow(255.f, 255.f, 0.f);
	inline ImColor Grey(0.600f, 0.600f, 0.600f);
	inline ImColor Purple(0.200f, 0.f, 0.600f);
}

namespace gl
{
	namespace ESP
	{
		inline bool ESP = true;
		inline bool ESP_Box = false;
		inline bool ESP_CorneredBox = false;
		inline bool ESP_3DBox = true;
		inline bool ESP_Snaplines = false;
		inline bool ESP_Skeleton = true;
		inline bool ESP_Names = false;
		inline bool HealthBar = true;

		inline bool VisCheck = true;

		inline int BoxTypeID = 0;
		inline BoxTypes BoxType = BoxTypes::Nornmal;
		inline const char* BoxTypeArray[3]{ "Normal", "Cornered", "3D Box" };
	}

	namespace Aimbot
	{
		inline bool Aimbot = true;
		inline bool MagicBullet = false;
		inline bool ShowFov = true;
		inline float Fov = 500.f;
		inline bool VisCheck = false;
		inline float Smooth = 1.f;
	}

	namespace Exploits
	{
		inline int MaxSpeed = 3000.f;

		inline bool SuperSpeed = true;
		inline bool FastFly = true;
		inline bool GodMode = true;
		inline bool SuperJump = true;
		inline bool FastAcceleration = true;
		inline bool UnlimitedAmmo = true;
		inline bool NoRecoil = true;
		inline bool NoSpread = true;
		inline bool InstaKill = true;
		inline bool Noclip = false;
		inline bool IncreeseFireRate = true;
		inline bool TpToCivilians = true;
		inline bool TpToEnemies = true;
	}

	namespace Misc
	{
		inline bool TeamCheck = false;
		inline bool ShowMouse = true;
		inline bool ShowFPS = true;
		inline bool DrawCrosshair = false;
		inline float CrosshairSize = 5.f;
		inline float CrosshairThickness = 1.f;
	}
	namespace World
	{
		inline float MaxDistance = 100.f;

		inline bool World = true;
		inline bool Civilians = true;
		inline bool BulletsImpacts = false;
		inline bool Doors = true;
		inline bool Evidence = true;
		inline bool Blood = false;
		inline bool BulletsFloor = false;
	}

	namespace esp_Colors
	{
		inline ImColor BoxColor = Colors::Purple;
		inline ImColor Box3DColor{ 255.f, 0.f , 0.f };
		inline ImColor SnaplineColor{ 255.f, 255.f , 255.f };
		inline ImColor SkeletonColor{ 255.f, 0.f, 0.f };
		inline ImColor FovColor{ 255.f, 255.f, 255.f };
		inline ImColor CrosshairColor{ 255.f, 0.f, 0.f };
		inline ImColor Visible{ 0.f, 0.f, 255.f };
		inline ImColor NotVisible{ 255.f, 0.f, 0.f };

		inline ImColor Civilians = Colors::Green;
		inline ImColor BulletsFloor = Colors::Yellow;
		inline ImColor BulletsEffects = Colors::Grey;
		inline ImColor Evidence = Colors::Pink;
		inline ImColor Blood = Colors::DarkRed;
		inline ImColor Doors = Colors::Cian;
	}
}



