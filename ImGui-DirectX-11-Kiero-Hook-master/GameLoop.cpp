#include "GameLoop.h"

void GameLoop()
{
	if (WorldActors.size() > 0)
	{
		float MaxDistance = FLT_MAX;

		for (int i = 0; i < WorldActors.size(); i++)
		{
			if (i >= WorldActors.size()) break;
			if (!WorldActors[i]) continue;


			SDK::AActor* actor = WorldActors[i];

			if (!actor->RootComponent) continue;
			if (actor->RootComponent->RelativeLocation.IsZero()) continue;

			SDK::FVector location = actor->RootComponent->RelativeLocation;

			auto LocalCharacter = reinterpret_cast<APlayerCharacter*>(MyController->Character);
			auto LocalPos = LocalCharacter->RootComponent->RelativeLocation;

			auto Distance = LocalPos.GetDistanceToInMeters(location);

			if (Distance > gl::World::MaxDistance) continue;

			SDK::FVector2D Pos{};

			SDK::FVector Center{};
			SDK::FVector Bounds{};

			if (MyController->ProjectWorldLocationToScreen(location, &Pos, false))
			{
				if (gl::World::BulletsImpacts)
				{
					if (actor->GetName().find("Impact") != std::string::npos)
					{
						ESP::DrawText2({ Pos.X, Pos.Y }, gl::esp_Colors::BulletsEffects, "Impact");
						continue;
					}
				}
				if (gl::World::Blood)
				{
					if (actor->GetName().find("Blood") != std::string::npos)
					{
						ESP::DrawText2({ Pos.X, Pos.Y }, gl::esp_Colors::Blood, "Blood");
						continue;
					}
				}
			}

			actor->GetActorBounds(true, &Center, &Bounds, false);

			if (MyController->ProjectWorldLocationToScreen(Center, &Pos, false))
			{

				if (gl::World::Doors)
				{
					if (actor->GetName().find("LinkProxy") != std::string::npos)
					{
						ESP::DrawText2({ Pos.X, Pos.Y }, gl::esp_Colors::Doors, "Door");
						ESP::Draw3DBox(Center, Bounds, MyController, gl::esp_Colors::Doors);
						continue;
					}
				}
				if (gl::World::BulletsFloor)
				{
					if (actor->GetName().find("Shell") != std::string::npos)
					{
						ESP::DrawText2({ Pos.X, Pos.Y }, gl::esp_Colors::BulletsFloor, "Shell");
						ESP::Draw3DBox(Center, Bounds, MyController, gl::esp_Colors::BulletsFloor);
						continue;
					}
				}
				if (gl::World::Evidence)
				{
					if (actor->GetName().find("Primary") != std::string::npos || actor->GetName().find("Secondary") != std::string::npos)
					{
						ESP::DrawText2({ Pos.X, Pos.Y }, gl::esp_Colors::Evidence, "Evidence");
						ESP::Draw3DBox(Center, Bounds, MyController, gl::esp_Colors::Evidence);
						continue;
					}
				}
				if (gl::World::Civilians)
				{
					if (actor->GetName().find("Civilian") != std::string::npos)
					{
						ESP::DrawText2({ Pos.X, Pos.Y }, gl::esp_Colors::Civilians, "Civilian");
						ESP::Draw3DBox(Center, Bounds, MyController, gl::esp_Colors::Civilians);

						FVector2D screen_middle = { 1920 / 2, 1080 / 2 };

						aimbot_distance = UKismetMathLibrary::Distance2D(Pos, screen_middle);

						if (aimbot_distance < MaxDistance && aimbot_distance <= gl::Aimbot::Fov)
						{
							MaxDistance = aimbot_distance;
							closestCivilianLocation = Center;
						}

						continue;
					}
				}
			}
		}
	}

	if (PlayerList.size() > 0)
	{
		float MaxDistance = FLT_MAX;
		bool IsActorVisibleAim = false;
		SDK::AActor* closest_actor{};
		SDK::FRotator closest_actor_rotation{};
		SDK::FVector closest_actor_head{};

		for (int i = 0; i < PlayerList.size(); i++)
		{
			bool Swat = false;

			if (i >= PlayerList.size()) break;
			if (!PlayerList[i]) continue;


			SDK::AActor* actor = PlayerList[i];

			if (!actor->RootComponent) continue;
			if (actor->RootComponent->RelativeLocation.IsZero()) continue;

			auto ActorState = actor->Instigator->PlayerState;

			if (!MyController->PlayerCameraManager) continue;

			auto CameraLocation = MyController->PlayerCameraManager->GetCameraLocation();
			auto CameraRotation = MyController->PlayerCameraManager->GetCameraRotation();

			auto LocalController = reinterpret_cast<ABP_BaseController_C*>(MyController);
			auto LocalCharacter = reinterpret_cast<APlayerCharacter*>(MyController->Character);

			auto CharacterMovement = LocalCharacter->CharacterMovement;

			//Exploits
			//------------------------------------------------------------------------------------------

			weapon = LocalCharacter->GetEquippedWeapon();

			if (!weapon) continue;

			auto CurrentItem = weapon->ItemType;
			bool IsWeapon = true;

			switch (CurrentItem)
			{
			case SDK::EItemType::IT_None:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_Rifles:
				break;
			case SDK::EItemType::IT_SubmachineGun:
				break;
			case SDK::EItemType::IT_LightMachineGun:
				break;
			case SDK::EItemType::IT_Shotgun:
				break;
			case SDK::EItemType::IT_Sniper:
				break;
			case SDK::EItemType::IT_PistolsLethal:
				break;
			case SDK::EItemType::IT_PistolsNonLethal:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_PrimaryNonLethal:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_Launcher:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_Melee:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_LessLethal:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_Headwear:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_BodyArmor:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_Grenade:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_GrenadeNonLethal:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_TacticalDevice:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_TacticalDeviceNonLethal:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_TacticalOne:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_TacticalTwo:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_TacticalThree:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_TacticalFour:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_TacticalFive:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_TacticalSix:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_TacticalSeven:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_TacticalEight:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_LongTactical:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_Skins:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_Loadouts:
				IsWeapon = false;
				break;
			case SDK::EItemType::IT_MAX:
				IsWeapon = false;
				break;
			default:
				break;
			}

			if (gl::Exploits::SuperSpeed)
			{
				CharacterMovement->MaxWalkSpeed = gl::Exploits::MaxSpeed;
			}
			if (gl::Exploits::FastFly)
			{
				CharacterMovement->MaxFlySpeed = gl::Exploits::MaxSpeed;
			}
			if (gl::Exploits::FastAcceleration)
			{
				CharacterMovement->MaxAcceleration = gl::Exploits::MaxSpeed;
			}
			if (gl::Exploits::GodMode)
			{
				LocalCharacter->CharacterHealth->bUnlimited = true;
			}
			if (gl::Exploits::SuperJump)
			{
				if (GetAsyncKeyState(VK_SPACE) & 1)
				{
					SDK::FVector Pos = LocalCharacter->RootComponent->RelativeLocation;
					Pos += SDK::FVector{ 0.f, 0.f, 250.f };

					LocalCharacter->TeleportPlayerToLocation(Pos);
				}
			}
			if (gl::Exploits::UnlimitedAmmo)
			{
				if (IsWeapon)
					weapon->bInfiniteAmmo = true;
			}
			if (gl::Exploits::NoRecoil)
			{
				if (IsWeapon)
				{
					weapon->ADSRecoilMultiplier = 0.f;
					weapon->FirstShotRecoil = 0.f;
					weapon->RecoilFireStrengthFirst = 0.f;
					weapon->RecoilFireADSModifier = 0.f;
				}
			}
			if (gl::Exploits::NoSpread)
			{
				if (IsWeapon)
				{
					weapon->ADSSpreadMultiplier = 0.f;
					weapon->FirstShotSpread = 0.f;
				}
			}
			if (gl::Exploits::IncreeseFireRate)
			{
				if (IsWeapon)
					weapon->FireRate = 0.01f;
			}
			if (gl::Exploits::InstaKill)
			{
				if (IsWeapon)
					weapon->Damage = 99999.f;
			}
			if (gl::Exploits::TpToCivilians)
			{
				if (!closestCivilianLocation.IsZero())
				{
					if (GetAsyncKeyState(VK_F1) & 1)
					{
						SDK::FVector NewPos{ closestCivilianLocation.X + 100.f, closestCivilianLocation.Y + 80.f, closestCivilianLocation.Z + 100.f };
						LocalCharacter->TeleportPlayerToLocation(NewPos);
					}
						
				}
			}

			//----------------------------------------------------------------------------------------------------

			auto LocalPos = LocalCharacter->RootComponent->RelativeLocation;

			SDK::AActor* MyActor{};

			if (ActorState == MyController->PlayerState)
			{
				MyActor = actor;
			}

			if (ActorState == MyController->PlayerState) continue;

			if (!actor) continue;
			if (!actor->Instigator) continue;
			if (!actor->Instigator->Controller) continue;
			if (!actor->Instigator->Controller->Character) continue;
			if (!actor->Instigator->Controller->Character->Mesh) continue;

			auto mesh = actor->Instigator->Controller->Character->Mesh;
			if (!mesh) continue;

			SDK::FVector location = actor->RootComponent->RelativeLocation;

			float ActorDistance = LocalPos.GetDistanceToInMeters(location);

			bool IsActorVisible = false;

			if (gl::ESP::VisCheck)
			{
				if (MyController->LineOfSightTo(actor, MyController->PlayerCameraManager->CameraCachePrivate.POV.Location, false))
				{
					IsActorVisible = true;
				}
			}

			SDK::FVector2D Bottom{};
			SDK::FVector2D Top{};
			SDK::FVector2D Middle{};

			SDK::FVector ActorCenter{};
			SDK::FVector ActorBoundsExtent{};

			actor->GetActorBounds(true, &ActorCenter, &ActorBoundsExtent, false);

			if (!MyController->ProjectWorldLocationToScreen(location, &Middle, false)) continue;

			SDK::FVector head_bone_pos = mesh->GetSocketLocation(StrToName("head"));
			SDK::FVector feet_bone_pos = mesh->GetSocketLocation(StrToName("ball_RI"));
			SDK::FVector torso_bone_pos = mesh->GetSocketLocation(StrToName("spine_2"));

			SDK::FVector feet_middle_pos = { location.X, location.Y, feet_bone_pos.Z };

			

			if (actor->GetName().find("Civilian") != std::string::npos)
				continue;

			if (!gl::Misc::TeamCheck)
			{
				if (actor->GetName().find("Swat") != std::string::npos)
					continue;
			}
			
			if (actor->GetName().find("Swat") != std::string::npos)
				Swat = true;

			if (MyController->ProjectWorldLocationToScreen(feet_middle_pos, &Bottom, false)
				&& MyController->ProjectWorldLocationToScreen(head_bone_pos, &Top, false))
			{
				const float h = std::abs(Top.Y - Bottom.Y);
				const float w = h * 0.2f;

				auto Character = reinterpret_cast<SDK::ASuspectCharacter*>(actor);
				auto health = Character->GetCurrentHealth();

				if (gl::ESP::ESP)
				{
					if (gl::ESP::ESP_Box)
					{
						if (!IsActorVisible)
						{
							if (!Swat)
								ESP::DrawBox(Vec2(Top.X - w, Top.Y), Vec2(Bottom.X + w, Bottom.Y), gl::esp_Colors::BoxColor, true);
							else
								ESP::DrawBox(Vec2(Top.X - w, Top.Y), Vec2(Bottom.X + w, Bottom.Y), Colors::Green, true);
						}
						else
						{
							if (!Swat)
								ESP::DrawBox(Vec2(Top.X - w, Top.Y), Vec2(Bottom.X + w, Bottom.Y), gl::esp_Colors::Visible, true);
							else
								ESP::DrawBox(Vec2(Top.X - w, Top.Y), Vec2(Bottom.X + w, Bottom.Y), Colors::Green, true);
						}
							
					}
					if (gl::ESP::ESP_3DBox)
					{
						if (!IsActorVisible)
						{
							if (!Swat)
								ESP::Draw3DBox(ActorCenter, ActorBoundsExtent, MyController, gl::esp_Colors::BoxColor);
							else
								ESP::Draw3DBox(ActorCenter, ActorBoundsExtent, MyController, Colors::Green);
						}
						else
						{
							if (!Swat)
								ESP::Draw3DBox(ActorCenter, ActorBoundsExtent, MyController, gl::esp_Colors::Visible);
							else
								ESP::Draw3DBox(ActorCenter, ActorBoundsExtent, MyController, Colors::Green);
						}

					}
					if (gl::ESP::ESP_CorneredBox)
					{
						if (!IsActorVisible)
						{
							if (!Swat)
							{
								ESP::DrawCorneredBox(Vec2(Top.X + 1, Top.Y + 1), Vec2(Bottom.X - 1, Bottom.Y - 1), w, h, Colors::Black);
								ESP::DrawCorneredBox(Vec2(Top.X - 1, Top.Y - 1), Vec2(Bottom.X + 1, Bottom.Y + 1), w, h, Colors::Black);
								ESP::DrawCorneredBox(Vec2(Top.X, Top.Y), Vec2(Bottom.X, Bottom.Y), w, h, gl::esp_Colors::BoxColor);
							}
							else
							{
								ESP::DrawCorneredBox(Vec2(Top.X + 1, Top.Y + 1), Vec2(Bottom.X - 1, Bottom.Y - 1), w, h, Colors::Black);
								ESP::DrawCorneredBox(Vec2(Top.X - 1, Top.Y - 1), Vec2(Bottom.X + 1, Bottom.Y + 1), w, h, Colors::Black);
								ESP::DrawCorneredBox(Vec2(Top.X, Top.Y), Vec2(Bottom.X, Bottom.Y), w, h, Colors::Green);
							}
						}
						else
						{
							if (!Swat)
							{
								ESP::DrawCorneredBox(Vec2(Top.X + 1, Top.Y + 1), Vec2(Bottom.X - 1, Bottom.Y - 1), w, h, Colors::Black);
								ESP::DrawCorneredBox(Vec2(Top.X - 1, Top.Y - 1), Vec2(Bottom.X  + 1, Bottom.Y + 1), w, h, Colors::Black);
								ESP::DrawCorneredBox(Vec2(Top.X, Top.Y), Vec2(Bottom.X, Bottom.Y), w, h, gl::esp_Colors::Visible);
							}
							else
							{
								ESP::DrawCorneredBox(Vec2(Top.X + 1, Top.Y + 1), Vec2(Bottom.X - 1, Bottom.Y - 1), w, h, Colors::Black);
								ESP::DrawCorneredBox(Vec2(Top.X - 1, Top.Y - 1), Vec2(Bottom.X + 1, Bottom.Y + 1), w, h, Colors::Black);
								ESP::DrawCorneredBox(Vec2(Top.X , Top.Y), Vec2(Bottom.X , Bottom.Y), w, h, Colors::Green);
							}
						}
					}
					if (gl::ESP::ESP_Snaplines)
					{
						if (!IsActorVisible)
						{
							if (!Swat)
								ESP::DrawLine(Vec2(1920 / 2, 0), Vec2(Top.X, Top.Y), gl::esp_Colors::SnaplineColor);
							else
								ESP::DrawLine(Vec2(1920 / 2, 0), Vec2(Top.X, Top.Y), Colors::Green);
						}
						else
						{
							if (!Swat)
								ESP::DrawLine(Vec2(1920 / 2, 0), Vec2(Top.X, Top.Y), gl::esp_Colors::Visible);
							else
								ESP::DrawLine(Vec2(1920 / 2, 0), Vec2(Top.X, Top.Y), Colors::Green);
						}
							
					}
					if (gl::ESP::ESP_Names)
					{
						ESP::DrawText2(Vec2(Top.X - w, Top.Y - 15), Colors::White, actor->GetName().c_str());
					}
					if (gl::ESP::HealthBar)
					{
						ESP::DrawBoxFilled(Vec2(Top.X - w - 6, Top.Y - 1), Vec2(Top.X - w - 3, Bottom.Y + 1), Colors::Black);
						ESP::DrawBoxFilled(Vec2(Top.X - w - 5, Bottom.Y - (h * (health * 0.01) / 3.5f)), Vec2(Top.X - w - 4, Bottom.Y), Colors::Green);
					}
					if (gl::ESP::ESP_Skeleton)
					{
						if (!IsActorVisible)
						{
							if (!Swat)
								DrawBones(mesh, MyController, gl::esp_Colors::SkeletonColor);
							else
								DrawBones(mesh, MyController, Colors::Green);
						}
						else
							if (!Swat)
								DrawBones(mesh, MyController, gl::esp_Colors::Visible);
							else
								DrawBones(mesh, MyController, Colors::Green);
					}
				}
				if (gl::Aimbot::Aimbot)
				{
					if (gl::Aimbot::ShowFov)
					{
						ESP::DrawCircle(Vec2(1920 / 2, 1080 / 2), gl::Aimbot::Fov, gl::esp_Colors::FovColor, 80);
					}

					if (gl::Aimbot::VisCheck)
					{
						if (MyController->LineOfSightTo(actor, MyController->PlayerCameraManager->CameraCachePrivate.POV.Location, false))
						{
							IsActorVisibleAim = true;
						}
						else
							IsActorVisibleAim = false;
					}

					auto rot = UKismetMathLibrary::FindLookAtRotation(CameraLocation, head_bone_pos);

					FVector2D screen_middle = { 1920 / 2, 1080 / 2 };

					aimbot_distance = UKismetMathLibrary::Distance2D(Top, screen_middle);

					if (aimbot_distance < MaxDistance && aimbot_distance <= gl::Aimbot::Fov)
					{
						MaxDistance = aimbot_distance;
						closest_actor = actor;
						closest_actor_rotation = rot;
						closest_actor_head = head_bone_pos;
					}
				}
			}
		}
		if (closest_actor && gl::Aimbot::Aimbot && GetAsyncKeyState(VK_XBUTTON2))
		{
			if (gl::Aimbot::VisCheck)
			{
				if (IsActorVisibleAim)
					MyController->SetControlRotation(closest_actor_rotation);
			}
			else
				MyController->SetControlRotation(closest_actor_rotation);
		}
		if (gl::Aimbot::MagicBullet && closest_actor && GetAsyncKeyState(VK_LBUTTON) & 1)
		{
			const FRotator BulletRotation = { 1.f, 1.f, 1.f };

			weapon->OnFire(BulletRotation, closest_actor_head);
		}
		if (gl::Exploits::TpToEnemies && closest_actor && GetAsyncKeyState(VK_F2) & 1)
		{
			auto LocalCharacter = reinterpret_cast<APlayerCharacter*>(MyController->Character);
			auto EnemiePos = closest_actor->RootComponent->RelativeLocation;

			SDK::FVector NewPos{ EnemiePos.X + 100.f, EnemiePos.Y + 80.f, EnemiePos.Z + 100.f };
			LocalCharacter->TeleportPlayerToLocation(NewPos);
		}
	}
}