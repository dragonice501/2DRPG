#pragma once

#include "../Logger/Logger.h"

#include "../Engine/Engine.h"

#include "../ECS/Components.h"
#include "../ECS/ECS.h"

#include "../EventBus/EventBus.h"
#include "../EventBus/Events.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>

#include <iostream>
#include <algorithm>

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

	void Update(SDL_Rect& camera)
	{
		for (auto entity : GetSystemEntities())
		{
			auto transform = entity.GetComponent<TransformComponent>();

			if (transform.position.x + (camera.w / 2) < Engine::mapWidth)
			{
				camera.x = transform.position.x - (Engine::mWindowWidth / 2);
			}
			if (transform.position.y + (camera.h / 2) < Engine::mapHeight)
			{
				camera.y = transform.position.y - (Engine::mWindowWidth / 2);
			}

			camera.x = camera.x < 0 ? 0 : camera.x;
			camera.y = camera.y < 0 ? 0 : camera.y;
			camera.x = camera.x > camera.w ? camera.w : camera.x;
			camera.y = camera.y > camera.h ? camera.h : camera.y;
		}
	}
};

class CharacterAnimationSystem : public System
{
public:
	CharacterAnimationSystem()
	{
		RequireComponent<SpriteComponent>();
		RequireComponent<AnimationComponent>();
		RequireComponent<RigidbodyComponent>();
	}

	void Update(float deltaTime)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& animation = entity.GetComponent<AnimationComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();

			if (rigidbody.velocity.y < 0)
			{
				sprite.srcRect.y = sprite.height * 1;
			}
			else if (rigidbody.velocity.y > 0)
			{
				sprite.srcRect.y = sprite.height * 2;
			}
			else if (rigidbody.velocity.x < 0)
			{
				sprite.srcRect.y = sprite.height * 3;
			}
			else if (rigidbody.velocity.x > 0)
			{
				sprite.srcRect.y = sprite.height * 4;
			}
			else if (rigidbody.velocity == Vec2(0.0f))
			{
				sprite.srcRect.y = 0;
			}

			animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameRateSpeed / 1000) % animation.numFrames;
			sprite.srcRect.x = animation.currentFrame * sprite.width;
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
				case SDLK_ESCAPE:
				{

				}
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
				case SDLK_ESCAPE:
				{

				}
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
			}
		}
	}
};

class CharacterMovementSystem : public System
{
public:
	CharacterMovementSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<RigidbodyComponent>();
		RequireComponent<CharacterMovementComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<CharacterInputComponent>();
	}

	void Update(double dt)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
			auto& movement = entity.GetComponent<CharacterMovementComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& input = entity.GetComponent<CharacterInputComponent>();

			if (movement.movementState == CharacterMovementComponent::EMovementState::Moving)
			{
				if(movement.destination == Vec2(0.0f))
				{
					SetVelocity(rigidbody, movement, input, transform);
				}

				if (transform.position != movement.destination)
				{
					movement.rate += 2 * dt;
					transform.position = Vec2::Lerp(movement.start, movement.destination, movement.rate);
					if (transform.position == movement.destination)
					{
						movement.rate = 0.0f;
						movement.start = transform.position;
						movement.destination = Vec2(0.0f);
						rigidbody.velocity = Vec2(0.0f);
						sprite.srcRect.y = 0;

						if (MovementPressed(input))
						{
							SetVelocity(rigidbody, movement, input, transform);
						}
						else
						{
							movement.movementState = CharacterMovementComponent::EMovementState::Idle;
						}
					}
				}
			}
			else
			{
				if (MovementPressed(input))
				{
					movement.movementState = CharacterMovementComponent::EMovementState::Moving;
				}
			}
		}
	}

	bool MovementPressed(const CharacterInputComponent& i)
	{
		return i.upButtonPresed || i.downButtonPresed || i.leftButtonPresed || i.rightButtonPresed;
	}
	void SetVelocity(RigidbodyComponent& r, CharacterMovementComponent& m, CharacterInputComponent& i, TransformComponent& t)
	{
		if (i.upButtonPresed)
		{
			r.velocity = m.upVelocity * 32.0f;
			m.start = t.position;
		}
		else if (i.downButtonPresed)
		{
			r.velocity = m.downVelocity * 32.0f;
			m.destination = t.position + r.velocity;
			m.start = t.position;
			m.destination = t.position + r.velocity;
		}
		else if (i.leftButtonPresed)
		{
			r.velocity = m.leftVelocity * 32.0f;
			m.start = t.position;
			m.destination = t.position + r.velocity;
		}
		else if (i.rightButtonPresed)
		{
			r.velocity = m.rightVelocity * 32.0f;
			m.start = t.position;
			m.destination = t.position + r.velocity;
		}
		m.destination = t.position + r.velocity;
	}
};

class CollisionSystem : public System
{
public:
	CollisionSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<BoxColliderComponent>();
	}

	void Update(std::unique_ptr<EventBus>& eventBus)
	{
		auto entities = GetSystemEntities();

		for (auto i = entities.begin(); i != entities.end(); i++)
		{
			Entity a = *i;
			auto aTransform = a.GetComponent<TransformComponent>();
			auto aCollider = a.GetComponent<BoxColliderComponent>();

			for (auto j = i; j != entities.end(); j++)
			{
				Entity b = *j;
				if (a == b) continue;

				auto bTransform = b.GetComponent<TransformComponent>();
				auto bCollider = b.GetComponent<BoxColliderComponent>();

				if (CheckAABBCollision(
					aTransform.position.x + aCollider.offset.x, aTransform.position.y + aCollider.offset.y, aCollider.width, aCollider.height,
					bTransform.position.x + bCollider.offset.x, bTransform.position.y + bCollider.offset.y, bCollider.width, bCollider.height))
				{
					eventBus->EmitEvent<CollisionEvent>(a, b);
				}
			}
		}
	}

	bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH)
	{
		return
			aX < bX + bW &&
			aX + aW > bX &&
			aY < bY + bH &&
			aY + aH > bY;
	}
};

class DamageSystem : public System
{
public:
	DamageSystem()
	{
		RequireComponent<BoxColliderComponent>();
	}

	void SuscribeToEvents(std::unique_ptr<EventBus>& eventBus)
	{
		eventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
	}

	void OnCollision(CollisionEvent& event)
	{
		Entity a = event.a;
		Entity b = event.b;

		/*Logger::Log(
			"the damage system received an event collision between entities " +
			std::to_string(a.GetID()) + " and " + std::to_string(b.GetID()));*/

		if (a.BelongsToGroup("projectiles") && b.HasTag("player"))
		{
			OnProjectileHitPlayer(a, b);
		}

		if (b.BelongsToGroup("projectiles") && a.HasTag("player"))
		{
			OnProjectileHitPlayer(b, a);
		}

		if (a.BelongsToGroup("projectiles") && b.BelongsToGroup("enemies"))
		{
			OnProjectileHitEnemy(a, b);
		}

		if (b.BelongsToGroup("projectiles") && a.BelongsToGroup("enemies"))
		{
			OnProjectileHitEnemy(b, a);
		}
	}

	void Update()
	{

	}

	void OnProjectileHitPlayer(Entity projectile, Entity player)
	{
		auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

		if (!projectileComponent.isFriendly)
		{
			auto& health = player.GetComponent<HealthComponent>();

			health.healthPercentage -= projectileComponent.hitPercentDamage;

			if (health.healthPercentage <= 0)
			{
				player.Kill();
			}

			projectile.Kill();
		}
	}

	void OnProjectileHitEnemy(Entity projectile, Entity enemy)
	{
		auto projectileComponent = projectile.GetComponent<ProjectileComponent>();

		if (projectileComponent.isFriendly)
		{
			auto& health = enemy.GetComponent<HealthComponent>();

			health.healthPercentage -= projectileComponent.hitPercentDamage;

			if (health.healthPercentage <= 0)
			{
				enemy.Kill();
			}

			projectile.Kill();
		}
	}
};

class KeyboardControlSystem : public System
{
public:
	KeyboardControlSystem()
	{
		RequireComponent<CharacterMovementComponent>();
		RequireComponent<KeyboardControlComponent>();
		RequireComponent<RigidbodyComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<TransformComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
	{
		eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
	}

	void OnKeyPressed(KeyPressedEvent& event)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& keyboardControl = entity.GetComponent<KeyboardControlComponent>();
			auto& characterMovement = entity.GetComponent<CharacterMovementComponent>();
			auto& rigidBody = entity.GetComponent<RigidbodyComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& transform = entity.GetComponent<TransformComponent>();

			switch (event.symbol)
			{
				case SDLK_ESCAPE:
				{
					
				}
				case SDLK_UP:
				{
					rigidBody.velocity = keyboardControl.upVelocity;

					characterMovement.destination = transform.position + rigidBody.velocity;
					characterMovement.start = transform.position;
					characterMovement.movementState = CharacterMovementComponent::EMovementState::Moving;

					sprite.srcRect.y = sprite.height * 1;
					break;
				}
				case SDLK_DOWN:
				{
					rigidBody.velocity = keyboardControl.downVelocity;

					characterMovement.destination = transform.position + rigidBody.velocity;
					characterMovement.start = transform.position;
					characterMovement.movementState = CharacterMovementComponent::EMovementState::Moving;

					sprite.srcRect.y = sprite.height * 2;
					break;
				}
				case SDLK_LEFT:
				{
					rigidBody.velocity = keyboardControl.leftVelocity;

					characterMovement.destination = transform.position + rigidBody.velocity;
					characterMovement.start = transform.position;
					characterMovement.movementState = CharacterMovementComponent::EMovementState::Moving;

					sprite.srcRect.y = sprite.height * 3;
					break;
				}
				case SDLK_RIGHT:
				{
					rigidBody.velocity = keyboardControl.rightVelocity;

					characterMovement.destination = transform.position + rigidBody.velocity;
					characterMovement.start = transform.position;
					characterMovement.movementState = CharacterMovementComponent::EMovementState::Moving;

					sprite.srcRect.y = sprite.height * 4;
					break;
				}
			}
		}
	}
};

class MovementSystem : public System
{
public:
	MovementSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<RigidbodyComponent>();
		RequireComponent<SpriteComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus)
	{
		eventBus->SubscribeToEvent<CollisionEvent>(this, &MovementSystem::OnCollision);
	}

	void OnCollision(CollisionEvent& event)
	{
		Entity a = event.a;
		Entity b = event.b;

		if (a.BelongsToGroup("enemies") && b.BelongsToGroup("obstacles"))
		{
			OnEnemyHitsObstacles(a, b);
		}

		if (a.BelongsToGroup("obstacles") && b.BelongsToGroup("enemies"))
		{
			OnEnemyHitsObstacles(b, a);
		}
	}

	void OnEnemyHitsObstacles(Entity enemy, Entity obstacle)
	{
		if (enemy.HasComponent<RigidbodyComponent>() && enemy.HasComponent<SpriteComponent>())
		{
			auto& rigidbody = enemy.GetComponent<RigidbodyComponent>();
			auto& sprite = enemy.GetComponent<SpriteComponent>();

			if (rigidbody.velocity.x != 0)
			{
				rigidbody.velocity.x *= -1;

				if (sprite.flip == SDL_FLIP_NONE) sprite.flip = SDL_FLIP_HORIZONTAL;
				else sprite.flip = SDL_FLIP_NONE;
			}

			if (rigidbody.velocity.y != 0)
			{
				rigidbody.velocity.y *= -1;

				if (sprite.flip == SDL_FLIP_NONE) sprite.flip = SDL_FLIP_VERTICAL;
				else sprite.flip = SDL_FLIP_NONE;
			}
		}
	}

	void Update(double deltaTime)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto& rigidbody = entity.GetComponent<RigidbodyComponent>();

			transform.position.x += rigidbody.velocity.x * deltaTime;
			transform.position.y += rigidbody.velocity.y * deltaTime;

			if (
				(transform.position.x < 0 ||
					transform.position.x > Engine::mapWidth ||
					transform.position.y < 0 ||
					transform.position.y > Engine::mapHeight) &&
				!entity.HasTag("player"))
			{
				entity.Kill();
			}

			if (entity.HasTag("player"))
			{
				int paddingLeft = 10;
				int paddingTop = 10;
				int paddingRight = 50;
				int paddingBottom = 50;

				transform.position.x = transform.position.x < paddingLeft ? paddingLeft : transform.position.x;
				transform.position.x = transform.position.x > Engine::mapWidth - paddingRight ? Engine::mapWidth - paddingRight : transform.position.x;
				transform.position.y = transform.position.y < paddingLeft ? paddingTop : transform.position.y;
				transform.position.y = transform.position.y > Engine::mapHeight + paddingBottom ? Engine::mapHeight - paddingBottom : transform.position.y;
			}

			if (
				(transform.position.x < 0 ||
					transform.position.x > Engine::mapWidth ||
					transform.position.y < 0 ||
					transform.position.y > Engine::mapHeight) &&
				entity.HasTag("player"))
			{
				entity.Kill();
			}
		}
	}
};

class ProjectileEmitSystem : public System
{
public:
	ProjectileEmitSystem()
	{
		RequireComponent<ProjectileEmitterComponent>();
		RequireComponent<TransformComponent>();
	}

	void SubcribeToEvents(std::unique_ptr<EventBus>& eventBus)
	{
		eventBus->SubscribeToEvent<KeyPressedEvent>(this, &ProjectileEmitSystem::OnKeyPressed);
	}

	void Update(std::unique_ptr<Registry>& registry)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
			const auto transform = entity.GetComponent<TransformComponent>();

			if (projectileEmitter.repeatFrequency == 0) continue;

			if (SDL_GetTicks() - projectileEmitter.lastEmissionTime > projectileEmitter.repeatFrequency)
			{
				Vec2 projectilePosition = transform.position;
				if (entity.HasComponent<SpriteComponent>())
				{
					const auto sprite = entity.GetComponent<SpriteComponent>();
					projectilePosition.x += (transform.scale.x * sprite.width / 2);
					projectilePosition.y += (transform.scale.y * sprite.height / 2);
				}

				Entity projectile = registry->CreateEntity();
				projectile.Group("projectiles");
				projectile.AddComponent<TransformComponent>(projectilePosition, Vec2(1.0, 1.0), 0.0);
				projectile.AddComponent<RigidbodyComponent>(projectileEmitter.projectileVelocity);
				projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);
				projectile.AddComponent<BoxColliderComponent>(4, 4);
				projectile.AddComponent<ProjectileComponent>(projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage, projectileEmitter.projectileDuration);

				projectileEmitter.lastEmissionTime = SDL_GetTicks();
			}
		}
	}

	void OnKeyPressed(KeyPressedEvent& event)
	{
		if (event.symbol == SDLK_SPACE)
		{
			for (auto entity : GetSystemEntities())
			{
				if (entity.HasComponent<CameraFollowComponent>())
				{
					const auto projectileEmitter = entity.GetComponent<ProjectileEmitterComponent>();
					const auto transform = entity.GetComponent<TransformComponent>();
					const auto rigidbody = entity.GetComponent<RigidbodyComponent>();

					Vec2 projectilePosition = transform.position;
					if (entity.HasComponent<SpriteComponent>())
					{
						auto sprite = entity.GetComponent<SpriteComponent>();
						projectilePosition.x += transform.scale.x * sprite.width / 2;
						projectilePosition.y += transform.scale.y * sprite.height / 2;
					}

					Vec2 projectileVelocity = projectileEmitter.projectileVelocity;
					int directionX = 0;
					int directionY = 0;
					if (rigidbody.velocity.x > 0) directionX = 1;
					if (rigidbody.velocity.x < 0) directionX = -1;
					if (rigidbody.velocity.y > 0) directionY = 1;
					if (rigidbody.velocity.y < 0) directionY = -1;
					projectileVelocity.x = projectileEmitter.projectileVelocity.x * directionX;
					projectileVelocity.y = projectileEmitter.projectileVelocity.y * directionY;

					Entity projectile = entity.mRegistry->CreateEntity();
					projectile.Group("projectiles");
					projectile.AddComponent<TransformComponent>(projectilePosition, Vec2(1.0, 1.0), 0.0);
					projectile.AddComponent<RigidbodyComponent>(projectileVelocity);
					projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);
					projectile.AddComponent<BoxColliderComponent>(4, 4);
					projectile.AddComponent<ProjectileComponent>(projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage, projectileEmitter.projectileDuration);
				}
			}
		}
	}
};

class ProjectileSystem : public System
{
public:
	ProjectileSystem()
	{
		RequireComponent<ProjectileComponent>();
	}

	void Update()
	{
		for (auto entity : GetSystemEntities())
		{
			auto projectile = entity.GetComponent<ProjectileComponent>();

			if (SDL_GetTicks() - projectile.startTime > projectile.duration)
			{
				entity.Kill();
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
		RequireComponent<AnimationComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, const SDL_Rect& camera)
	{
		for (const auto& entity : GetSystemEntities())
		{
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			SDL_Rect srcRect = sprite.srcRect;
			SDL_Rect destRect = {
				transform.position.x - (sprite.isFixed ? 0 : camera.x),
				transform.position.y - (sprite.isFixed ? 0 : camera.y),
				sprite.width * transform.scale.x,
				sprite.height * transform.scale.y };
			SDL_Point center = { transform.position.x + sprite.width / 2.0, transform.position.y + sprite.height / 2.0 };

			SDL_RenderCopyEx(renderer, assetStore->GetTexture(sprite.assetId), &srcRect, &destRect, transform.rotation, nullptr, sprite.flip);
		}
	}
};

class RenderCollisionSystem : public System
{
public:
	RenderCollisionSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<BoxColliderComponent>();
	}

	void Update(SDL_Renderer* renderer, SDL_Rect& camera)
	{
		for (auto entity : GetSystemEntities())
		{
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto collider = entity.GetComponent<BoxColliderComponent>();

			SDL_Rect colliderRect =
			{
				static_cast<int>(transform.position.x + collider.offset.x - camera.x),
				static_cast<int>(transform.position.y + collider.offset.y - camera.y),
				static_cast<int>(collider.width * transform.scale.x),
				static_cast<int>(collider.height * transform.scale.y)
			};

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &colliderRect);
		}
	}
};

class RenderGUISytem : public System
{
public:
	RenderGUISytem() = default;

	void Update(const std::unique_ptr<Registry>& registry, SDL_Rect& camera)
	{
		ImGui::NewFrame();

		if (ImGui::Begin("Spawn Enemies"))
		{
			static int enemyPosX = 0;
			static int enemyPosY = 0;
			static int scaleX = 1;
			static int scaleY = 1;
			static int velX = 0;
			static int velY = 0;
			static int health = 100;
			static float rotation = 0.0;
			static float projAngle = 0.0;
			static float projSpeed = 0.0;
			static int projRepeat = 10;
			static int projDuration = 10;
			const char* sprites[] = { "tank-image", "truck-image" };
			static int selectedSpriteIndex = 0;

			if (ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Combo("texture id", &selectedSpriteIndex, sprites, IM_ARRAYSIZE(sprites));
			}
			ImGui::Spacing();

			if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::InputInt("position x", &enemyPosX);
				ImGui::InputInt("position y", &enemyPosY);
				ImGui::SliderInt("scale x", &scaleX, 1, 10);
				ImGui::SliderInt("scale y", &scaleY, 1, 10);
				ImGui::SliderAngle("rotation (deg)", &rotation, 0, 360);
			}

			if (ImGui::CollapsingHeader("Rigid Body", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::InputInt("velocity x", &velX);
				ImGui::InputInt("velocity y", &velY);
			}
			ImGui::Spacing();

			if (ImGui::CollapsingHeader("Projectile emitter", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::SliderAngle("angle (deg)", &projAngle, 0, 360);
				ImGui::SliderFloat("spedd (px/sec)", &projSpeed, 10, 500);
				ImGui::InputInt("repeat (sec)", &projRepeat);
				ImGui::InputInt("durection (sec)", &projDuration);
			}
			ImGui::Spacing();

			if (ImGui::CollapsingHeader("Health", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::InputInt("%", &health, 0, 100);
			}
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			if (ImGui::Button("Create new enemy"))
			{
				Entity enemy = registry->CreateEntity();
				enemy.Group("enemies");
				enemy.AddComponent<TransformComponent>(Vec2(enemyPosX, enemyPosY), Vec2(scaleX, scaleY), 0.0);
				enemy.AddComponent<RigidbodyComponent>(Vec2(velX, velY));
				enemy.AddComponent<SpriteComponent>(sprites[selectedSpriteIndex], 32, 32, 1);
				enemy.AddComponent<BoxColliderComponent>(25, 20, Vec2(5, 5));
				double projVelX = cos(projAngle) * projSpeed;
				double projVelY = sin(projAngle) * projSpeed;
				enemy.AddComponent<ProjectileEmitterComponent>(Vec2(projVelX, projVelY), projRepeat * 1000, projDuration * 1000, 10, false);
				enemy.AddComponent<HealthComponent>(health);

				enemyPosX = enemyPosY = rotation = projAngle = 0;
				scaleX = scaleY = 1;
				projRepeat = projDuration = 10;
				projSpeed = 100;
				health = 100;
			}
		}
		ImGui::End();

		ImGuiWindowFlags windowsFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav;
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always, ImVec2(0, 0));
		ImGui::SetNextWindowBgAlpha(0.9f);
		if (ImGui::Begin("Map Coordinates", NULL, windowsFlags))
		{
			ImGui::Text(
				"Map coordinates (x=%.1f, y=%.1f)",
				ImGui::GetIO().MousePos.x + camera.x,
				ImGui::GetIO().MousePos.y + camera.y
			);
		}
		ImGui::End();

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
	}
};

class RenderHealthBarSystem : public System
{
public:
	RenderHealthBarSystem()
	{
		RequireComponent<HealthComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, const SDL_Rect& camera)
	{
		for (auto entity : GetSystemEntities())
		{
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();
			const auto health = entity.GetComponent<HealthComponent>();

			SDL_Color healthBarColor = { 255, 255, 255 };

			if (health.healthPercentage >= 0 && health.healthPercentage < 40) healthBarColor = { 255, 0, 0 };
			if (health.healthPercentage >= 40 && health.healthPercentage < 80) healthBarColor = { 255, 255, 0 };
			if (health.healthPercentage >= 80 && health.healthPercentage <= 100) healthBarColor = { 0, 255, 0 };

			int healthBarWidth = 15;
			int healthBarHeight = 3;
			double healthBarPosX = (transform.position.x + (sprite.width * transform.scale.x)) - camera.x;
			double healthBarPosY = (transform.position.y) - camera.y;

			SDL_Rect healthBarRectangle =
			{
				healthBarPosX,
				healthBarPosY,
				healthBarWidth * (health.healthPercentage / 100.0),
				healthBarHeight
			};

			SDL_SetRenderDrawColor(renderer, healthBarColor.r, healthBarColor.g, healthBarColor.b, 255);
			SDL_RenderFillRect(renderer, &healthBarRectangle);

			std::string healthText = std::to_string(health.healthPercentage);
			SDL_Surface* surface = TTF_RenderText_Blended(assetStore->GetFont("charriot-font"), healthText.c_str(), healthBarColor);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			int labelWidth = 0;
			int labelHeight = 0;
			SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);
			SDL_Rect healthBarTextRectangle =
			{
				healthBarPosX,
				healthBarPosY + 5,
				labelWidth,
				labelHeight
			};

			SDL_RenderCopy(renderer, texture, NULL, &healthBarTextRectangle);
			SDL_DestroyTexture(texture);
		}
	}
};

class RenderSystem : public System
{
public:
	RenderSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, const SDL_Rect& camera)
	{
		struct RenderableEntity
		{
			TransformComponent transformComponent;
			SpriteComponent spriteComponent;
		};
		std::vector<RenderableEntity> renderableEntities;

		for (auto& entity : GetSystemEntities())
		{
			RenderableEntity renderableEntity;
			renderableEntity.transformComponent = entity.GetComponent<TransformComponent>();
			renderableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();

			if (!(renderableEntity.transformComponent.position.x + (renderableEntity.transformComponent.scale.x * renderableEntity.spriteComponent.width) < camera.x ||
				renderableEntity.transformComponent.position.x > camera.x + camera.w ||
				renderableEntity.transformComponent.position.y + (renderableEntity.transformComponent.scale.y * renderableEntity.spriteComponent.height) < camera.y ||
				renderableEntity.transformComponent.position.y > camera.y + camera.h
				) && !renderableEntity.spriteComponent.isFixed)
			{
				renderableEntities.emplace_back(renderableEntity);
			}
		}

		std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity& a, const RenderableEntity& b)
			{
				return a.spriteComponent.zIndex < b.spriteComponent.zIndex;
			});

		for (const auto& entity : renderableEntities)
		{
			const auto transform = entity.transformComponent;
			const auto sprite = entity.spriteComponent;

			SDL_Rect srcRect = sprite.srcRect;
			SDL_Rect destRect = {
				transform.position.x - (sprite.isFixed ? 0 : camera.x),
				transform.position.y - (sprite.isFixed ? 0 : camera.y),
				sprite.width * transform.scale.x,
				sprite.height * transform.scale.y };
			SDL_Point center = { transform.position.x + sprite.width / 2.0, transform.position.y + sprite.height / 2.0 };

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

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, const SDL_Rect& camera)
	{
		int x = camera.x - (camera.x % 16);
		int y = camera.y - (camera.y % 16);

		/*for (int i = y; i < camera.h / 16; i++)
		{
			for (int j = x; j < camera.w / 16; j++)
			{
				const auto transform = GetSystemEntities()[j + i * 256].GetComponent<TransformComponent>();
				const auto sprite = GetSystemEntities()[j + i * 256].GetComponent<SpriteComponent>();

				SDL_Rect srcRect = sprite.srcRect;
				SDL_Rect destRect = {
					transform.position.x - (sprite.isFixed ? 0 : camera.x),
					transform.position.y - (sprite.isFixed ? 0 : camera.y),
					sprite.width * transform.scale.x,
					sprite.height * transform.scale.y };
				SDL_Point center = { transform.position.x + sprite.width / 2.0, transform.position.y + sprite.height / 2.0 };

				SDL_RenderCopyEx(renderer, assetStore->GetTexture(sprite.assetId), &srcRect, &destRect, transform.rotation, nullptr, sprite.flip);
			}
		}*/

		for (const auto& entity : GetSystemEntities())
		{
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			SDL_Rect srcRect = sprite.srcRect;
			SDL_Rect destRect = {
				transform.position.x - (sprite.isFixed ? 0 : camera.x),
				transform.position.y - (sprite.isFixed ? 0 : camera.y),
				sprite.width * transform.scale.x,
				sprite.height * transform.scale.y };
			SDL_Point center = { transform.position.x + sprite.width / 2.0, transform.position.y + sprite.height / 2.0 };

			SDL_RenderCopyEx(renderer, assetStore->GetTexture(sprite.assetId), &srcRect, &destRect, transform.rotation, nullptr, sprite.flip);
		}
	}
};