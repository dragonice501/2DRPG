#pragma once

#include "../ECS/ECS.h"
#include "../ECS/Components.h"
#include "../EventBus/EventBus.h"
#include "../EventBus/Event.h"
#include "../Utils/Utils.h"
#include "../Utils/Vec2.h"
#include "../Utils/Constants.h"
#include "../Managers/SceneManager.h"

class WorldEncounterSystem : public System
{
public:
	size_t mEncounterStepsSize = 15;
	size_t mEncounterStepRemaining = mEncounterStepsSize;

public:
	WorldEncounterSystem()
	{

	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
	{
		eventBus->SubscribeToEvent<CharacterMovementEvent>(this, &WorldEncounterSystem::DetectMovement);
	}

	void DetectMovement(CharacterMovementEvent& event)
	{
		if (SceneManager::Instance().GetIsOverworld())
		{
			mEncounterStepRemaining--;

			if (mEncounterStepRemaining <= 0)
			{
				std::cout << "encounter" << std::endl;
				mEncounterStepRemaining = mEncounterStepsSize;
			}
		}
	}
};