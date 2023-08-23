#pragma once

#include "../Logger/Logger.h"

#include "../Engine/Engine.h"

#include "../ECS/Components.h"
#include "../ECS/ECS.h"

#include "../EventBus/EventBus.h"
#include "../EventBus/Events.h"

#include "../Utils/Constants.h"
#include "../Utils/Utils.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>

#include <iostream>
#include <algorithm>
#include <math.h>

class AnimationSystem : public System
{
public:
	AnimationSystem()
	{
		RequireComponent<SpriteComponent>();
		RequireComponent<AnimationComponent>();
	}

	void Update(float deltaTime)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& animation = entity.GetComponent<AnimationComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();

			animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameRateSpeed / 1000) % animation.numFrames;
			sprite.srcRect.x = animation.currentFrame * sprite.width;
		}
	}
};

class CameraMovementSystem : public System
{
public:
	CameraMovementSystem()
	{
		RequireComponent<CameraFollowComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(SDL_Rect& camera, const int mapWidth, const int mapHeight)
	{
		for (auto& entity : GetSystemEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& cameraFollow = entity.GetComponent<CameraFollowComponent>();

			camera.x = transform.position.x * TILE_SPRITE_SCALE - (Engine::mWindowWidth / 2);
			camera.y = transform.position.y * TILE_SPRITE_SCALE - (Engine::mWindowHeight / 2);

			camera.x = Clampf(camera.x, 0, mapWidth * TILE_SIZE * TILE_SPRITE_SCALE - camera.w);
			camera.y = Clampf(camera.y, 0, mapHeight * TILE_SIZE * TILE_SPRITE_SCALE - camera.h);
		}
	}
};

class CharacterAnimationSystem : public System
{
public:
	CharacterAnimationSystem()
	{
		RequireComponent<SpriteComponent>();
		RequireComponent<AnimationSystemComponent>();
		RequireComponent<AnimationStateComponent>();
		RequireComponent<RigidbodyComponent>();
	}

	void Update(float deltaTime)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& animationState = entity.GetComponent<AnimationStateComponent>();
			auto& animationSystem = entity.GetComponent<AnimationSystemComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();

			if (rigidbody.velocity != Vec2(0.0f))
			{
				animationState.animationState = AnimationStateComponent::MOVING;
				animationSystem.SetCurrentAnimation("Moving");
				sprite.assetId = animationSystem.GetCurrentAnimation().assetId;
			}
			else
			{
				animationState.animationState = AnimationStateComponent::IDLE;
				animationSystem.SetCurrentAnimation("Idle");
				sprite.assetId = animationSystem.GetCurrentAnimation().assetId;
			}

			if (animationState.animationState == AnimationStateComponent::IDLE)
			{
				if (rigidbody.lastVelocity.y < 0)
				{
					sprite.srcRect.y = sprite.height * 0;
				}
				else if (rigidbody.lastVelocity.y > 0)
				{
					sprite.srcRect.y = sprite.height * 1;
				}
				else if (rigidbody.lastVelocity.x < 0)
				{
					sprite.srcRect.y = sprite.height * 2;
				}
				else if (rigidbody.lastVelocity.x > 0)
				{
					sprite.srcRect.y = sprite.height * 3;
				}
			}
			else if (animationState.animationState == AnimationStateComponent::MOVING)
			{
				if (rigidbody.velocity.y < 0)
				{
					sprite.srcRect.y = sprite.height * 0;
				}
				else if (rigidbody.velocity.y > 0)
				{
					sprite.srcRect.y = sprite.height * 1;
				}
				else if (rigidbody.velocity.x < 0)
				{
					sprite.srcRect.y = sprite.height * 2;
				}
				else if (rigidbody.velocity.x > 0)
				{
					sprite.srcRect.y = sprite.height * 3;
				}
			}

			AnimationSystemComponent::Animation& anim = animationSystem.GetCurrentAnimation();

			anim.currentFrame = ((SDL_GetTicks() - anim.startTime) * anim.frameRateSpeed / 1000) % anim.numFrames;
			sprite.srcRect.x = anim.currentFrame * sprite.width;
		}
	}
};

class CharacterInputSystem : public System
{
public:
	CharacterInputSystem()
	{
		RequireComponent<CharacterInputComponent>();
	}

	void Update(float dt)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& characterInput = entity.GetComponent<CharacterInputComponent>();

			if (characterInput.interactButtonPressed || characterInput.interactButtonHeld)
			{
				characterInput.interactButtonPressed = false;
				characterInput.interactButtonHeld = true;
			}
		}
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
	{
		eventBus->SubscribeToEvent<KeyPressedEvent>(this, &CharacterInputSystem::OnKeyPressed);
		eventBus->SubscribeToEvent<KeyReleasedEvent>(this, &CharacterInputSystem::OnKeyReleased);
	}

	void OnKeyPressed(KeyPressedEvent& event)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& characterInput = entity.GetComponent<CharacterInputComponent>();

			switch (event.symbol)
			{
				case SDLK_w:
				{
					characterInput.upButtonPresed = true;
					break;
				}
				case SDLK_s:
				{
					characterInput.downButtonPresed = true;
					break;
				}
				case SDLK_a:
				{
					characterInput.leftButtonPresed = true;
					break;
				}
				case SDLK_d:
				{
					characterInput.rightButtonPresed = true;
					break;
				}
				case SDLK_e:
				{
					if (!characterInput.interactButtonHeld)
					{
						characterInput.interactButtonPressed = true;
					}
					else
					{
						characterInput.interactButtonHeld = true;
						characterInput.interactButtonPressed = false;
					}
					break;
				}
			}
		}
	}

	void OnKeyReleased(KeyReleasedEvent& event)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& characterInput = entity.GetComponent<CharacterInputComponent>();

			switch (event.symbol)
			{
				case SDLK_w:
				{
					characterInput.upButtonPresed = false;
					break;
				}
				case SDLK_s:
				{
					characterInput.downButtonPresed = false;
					break;
				}
				case SDLK_a:
				{
					characterInput.leftButtonPresed = false;
					break;
				}
				case SDLK_d:
				{
					characterInput.rightButtonPresed = false;
					break;
				}
				case SDLK_e:
				{
					characterInput.interactButtonHeld = false;
					characterInput.interactButtonPressed = false;
					break;
				}
			}
		}
	}
};

class CharacterInteractSystem: public System
{
public:
	CharacterInteractSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<RigidbodyComponent>();
		RequireComponent<CharacterInputComponent>();
	}

	void Update(std::unique_ptr<EventBus>& eventbus)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& input = entity.GetComponent<CharacterInputComponent>();
			const auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
			const auto& transform = entity.GetComponent<TransformComponent>();

			if (input.interactButtonPressed)
			{	
				Vec2 interactionPosition =
				{
					transform.position.x + rigidbody.lastVelocity.x * TILE_SIZE,
					transform.position.y + rigidbody.lastVelocity.y * TILE_SIZE
				};

				eventbus->EmitEvent<CharacterInteractEvent>(interactionPosition);

				input.interactButtonHeld = true;
			}
		}
	}
};

class InteractSystem : public System
{
public:
	InteractSystem()
	{
		RequireComponent<InteractableComponent>();
		RequireComponent<TransformComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
	{
		eventBus->SubscribeToEvent<CharacterInteractEvent>(this, &InteractSystem::CheckInteractables);
	}

	void CheckInteractables(CharacterInteractEvent& event)
	{
		for (auto& entity : GetSystemEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();

			if (transform.position == event.interactPosition)
			{
				std::cout << "interaction made at: " << transform.position.x << ',' << transform.position.y << std::endl;
			}
		}
	}
};

class RenderCharacterSystem : public System
{
public:
	RenderCharacterSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<AnimationSystemComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, const SDL_Rect& camera)
	{
		for (const auto& entity : GetSystemEntities())
		{
			const auto& transform = entity.GetComponent<TransformComponent>();
			const auto& sprite = entity.GetComponent<SpriteComponent>();

			SDL_Rect srcRect = sprite.srcRect;
			SDL_Rect destRect =
			{
				transform.position.x * TILE_SPRITE_SCALE + sprite.xOffset * TILE_SPRITE_SCALE - (sprite.isFixed ? 0 : camera.x),
				transform.position.y * TILE_SPRITE_SCALE + sprite.yOffset * TILE_SPRITE_SCALE - (sprite.isFixed ? 0 : camera.y),
				sprite.width * transform.scale.x * TILE_SPRITE_SCALE,
				sprite.height * transform.scale.y * TILE_SPRITE_SCALE
			};

			SDL_RenderCopyEx(renderer, assetStore->GetTexture(sprite.assetId), &srcRect, &destRect, transform.rotation, nullptr, sprite.flip);
		}
	}
};

class RenderTextSystem : public System {
public:
	RenderTextSystem()
	{
		RequireComponent<TextLabelComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, const SDL_Rect& camera)
	{
		for (auto entity : GetSystemEntities())
		{
			const auto textlabel = entity.GetComponent<TextLabelComponent>();

			SDL_Surface* surface = TTF_RenderText_Blended(assetStore->GetFont(textlabel.assetId), textlabel.text.c_str(), textlabel.color);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			int labelWidth = 0;
			int labelHeight = 0;
			SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);
			SDL_Rect healthBarTextRectangle =
			{
				textlabel.position.x - (textlabel.isFixed ? 0 : camera.x),
				textlabel.position.y - (textlabel.isFixed ? 0 : camera.y),
				labelWidth,
				labelHeight
			};

			SDL_RenderCopy(renderer, texture, NULL, &healthBarTextRectangle);
			SDL_DestroyTexture(texture);
		}
	}
};

class RenderTileSystem : public System
{
public:
	RenderTileSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<TileComponent>();
	}

	~RenderTileSystem()
	{
		
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, const SDL_Rect& camera)
	{
		int x = camera.x - (camera.x % TILE_SIZE);
		int y = camera.y - (camera.y % TILE_SIZE);

		for (const auto& entity : GetSystemEntities())
		{
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			SDL_Rect srcRect = sprite.srcRect;
			SDL_Rect destRect =
			{
				transform.position.x * TILE_SPRITE_SCALE - (sprite.isFixed ? 0 : camera.x),
				transform.position.y * TILE_SPRITE_SCALE - (sprite.isFixed ? 0 : camera.y),
				sprite.width * transform.scale.x * TILE_SPRITE_SCALE,
				sprite.height * transform.scale.y * TILE_SPRITE_SCALE
			};

			SDL_RenderCopyEx(renderer, assetStore->GetTexture(sprite.assetId), &srcRect, &destRect, transform.rotation, nullptr, sprite.flip);
		}
	}
};

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
		//PrintTerrainType(event.terrainType);
		mEncounterStepRemaining--;

		if (mEncounterStepRemaining <= 0)
		{
			std::cout << "encounter" << std::endl;
			mEncounterStepRemaining = mEncounterStepsSize;
		}
	}
};