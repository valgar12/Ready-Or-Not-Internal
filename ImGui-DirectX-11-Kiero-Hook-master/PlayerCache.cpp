#include "PlayerCache.h"
#include "SDK.hpp"

void PlayerCache::PlayerCache()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	World = SDK::UWorld::GetWorld();
	Engine = SDK::UEngine::GetEngine();

	actors = World->PersistentLevel->Actors;
	MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;

	while (alive)
	{
		PlayerList.clear();

		actors = World->PersistentLevel->Actors;

		for (int i = 0; i < actors.Num(); i++)
		{
			if (i >= actors.Num()) break;

			actor_list = actors[i];

			if (!actor_list || actor_list == nullptr) continue;
			if (!actor_list->RootComponent) continue;
			if (actor_list->RootComponent->RelativeLocation.IsZero()) continue;

			MyController = World->OwningGameInstance->LocalPlayers[0]->PlayerController;

			if (!actor_list->RootComponent) continue;
			if (!actor_list->HasTypeFlag(SDK::EClassCastFlags::Pawn)) continue;
			if (!actor_list->Instigator) continue;
			if (!actor_list->Instigator->Controller) continue;
			if (!actor_list->Instigator->Controller->Character) continue;
			if (!actor_list->Instigator->Controller->Character->Mesh) continue;

			PlayerList.push_back(actor_list);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}