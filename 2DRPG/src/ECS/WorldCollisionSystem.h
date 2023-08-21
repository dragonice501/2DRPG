#pragma once

#include "../ECS/ECS.h"
#include "../Managers/SceneManager.h"

class WorldCollisionSystem : public System
{
public:
	WorldCollisionSystem()
	{
		RequireComponent<SceneEntranceComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
	{
		eventBus->SubscribeToEvent<CharacterMovementEvent>(this, &WorldCollisionSystem::CheckCharacterOnEntrance);
	}

	void CheckCharacterOnEntrance(CharacterMovementEvent& event)
	{
		std::vector<Entity>& entities = GetSystemEntities();

		for (auto i = entities.begin(); i != entities.end(); i++)
		{
			const SceneEntranceComponent& entrance = i->GetComponent<SceneEntranceComponent>();

			if (entrance.position * TILE_SIZE == event.position)
			{
				SceneManager::Instance().SetSceneToLoad(static_cast<SceneNames>(entrance.sceneName), entrance.sceneEntranceIndex);
			}
		}
	}
};