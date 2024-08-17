#include "ActorCache.h"
#include "SDK.hpp"

void ActorsCache::ActorsCache()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));

	while (alive)
	{
		WorldActors.clear();

		actors = World->PersistentLevel->Actors;

		for (int i = 0; i < actors.Num(); i++)
		{
			if (i >= actors.Num()) break;

			if (!actors[i]) continue;

			SDK::AActor* actor = actors[i];

			if (!actor || actor == nullptr) continue;
			if (!actor->RootComponent) continue;
			if (actor->RootComponent->RelativeLocation.IsZero()) continue;

			WorldActors.push_back(actor);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}