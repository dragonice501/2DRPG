#pragma once

#include "../ECS/ECS.h"
#include "../ECS/Components.h"
#include "../EventBus/EventBus.h"
#include "../EventBus/Event.h"
#include "../Utils/Utils.h"
#include "../Utils/Vec2.h"
#include "../Utils/Constants.h"
#include "../Managers/SceneManager.h"

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
		RequireComponent<CameraFollowComponent>();
	}

	void Update(double dt, std::unique_ptr<EventBus>& eventBus, const int mapWidth, const int mapHeight, const std::vector<Entity>& tiles)
	{
		for (auto entity : GetSystemEntities())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rigidbody = entity.GetComponent<RigidbodyComponent>();
			auto& movement = entity.GetComponent<CharacterMovementComponent>();//
			auto& sprite = entity.GetComponent<SpriteComponent>();
			auto& input = entity.GetComponent<CharacterInputComponent>();

			if (movement.movementState == CharacterMovementComponent::EMovementState::Moving)
			{
				if (transform.position != movement.destination)
				{
					movement.rate += 2 * dt;
					transform.position = Vec2::Lerp(movement.start, movement.destination, movement.rate);
					if (transform.position == movement.destination)
					{
						movement.rate = 0.0f;
						movement.start = transform.position;
						movement.destination = Vec2(0.0f);
						rigidbody.lastVelocity = rigidbody.velocity;
						rigidbody.velocity = Vec2(0.0f);
						sprite.srcRect.y = 0;

						int index = transform.position.x / TILE_SIZE + (transform.position.y / TILE_SIZE) * mapWidth;
						eventBus->EmitEvent<CharacterMovementEvent>(tiles[index].GetComponent<TileComponent>().terrainType, transform.position);

						if (MovementPressed(input))
						{
							Vec2 desiredPosition = GetDesiredPosition(movement, input, transform);
							if (
								MovementInsideMap(desiredPosition, mapWidth, mapHeight) &&
								CanMove(mapWidth, mapHeight, transform, desiredPosition, input, tiles, movement))
							{
								SetMovement(rigidbody, movement, input, transform);
							}
							else
							{
								movement.movementState = CharacterMovementComponent::EMovementState::Idle;
							}
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
					Vec2 desiredPosition = GetDesiredPosition(movement, input, transform);
					if (
						MovementInsideMap(desiredPosition, mapWidth, mapHeight) &&
						CanMove(mapWidth, mapHeight, transform, desiredPosition, input, tiles, movement))
					{
						movement.movementState = CharacterMovementComponent::EMovementState::Moving;
						SetMovement(rigidbody, movement, input, transform);
					}
					else
					{
						movement.movementState = CharacterMovementComponent::EMovementState::Idle;
					}
				}
			}
		}
	}

	bool MovementPressed(const CharacterInputComponent& i)
	{
		return i.upButtonPresed || i.downButtonPresed || i.leftButtonPresed || i.rightButtonPresed;
	}

	Vec2 GetDesiredPosition(const CharacterMovementComponent& m, const CharacterInputComponent& i, const TransformComponent& t)
	{
		Vec2 desiredPosition;

		if (i.upButtonPresed)
		{
			desiredPosition = Vec2(static_cast<int>(t.position.x + m.upVelocity.x * TILE_SIZE), static_cast<int>(t.position.y + m.upVelocity.y * TILE_SIZE));
		}
		else if (i.downButtonPresed)
		{
			desiredPosition = Vec2(static_cast<int>(t.position.x + m.downVelocity.x * TILE_SIZE), static_cast<int>(t.position.y + m.downVelocity.y * TILE_SIZE));
		}
		else if (i.leftButtonPresed)
		{
			desiredPosition = Vec2(static_cast<int>(t.position.x + m.leftVelocity.x * TILE_SIZE), static_cast<int>(t.position.y + m.leftVelocity.y * TILE_SIZE));
		}
		else if (i.rightButtonPresed)
		{
			desiredPosition = Vec2(static_cast<int>(t.position.x + m.rightVelocity.x * TILE_SIZE), static_cast<int>(t.position.y + m.rightVelocity.y * TILE_SIZE));
		}

		return desiredPosition;
	}

	bool MovementInsideMap(const Vec2& position, const int width, const int height)
	{
		return !(
			position.x < 0 ||
			position.x + TILE_SIZE > width * TILE_SIZE ||
			position.y < 0 ||
			position.y + TILE_SIZE > height * TILE_SIZE);
	}

	bool CanMove(
		int width, int height, const TransformComponent& t, const Vec2& position, const CharacterInputComponent& i,
		const std::vector<Entity>& tl, const CharacterMovementComponent& m)
	{
		int x = position.x / TILE_SIZE;
		int y = position.y / TILE_SIZE;

		ETownTileType townTile = tl[x + y * width].GetComponent<TileComponent>().townTileType;
		ETerrainType terrain = tl[x + y * width].GetComponent<TileComponent>().terrainType;


		if (SceneManager::Instance().GetIsOverworld())
		{
			if (terrain == CLIFF && !m.canWalkCliffs) return false;

			if (terrain == RIVER && !m.canWalkRivers) return false;
		}
		else
		{
			if (townTile == UNWALKABLE) return false;
		}

		return true;
	}

	void SetMovement(RigidbodyComponent& r, CharacterMovementComponent& m, CharacterInputComponent& i, TransformComponent& t)
	{
		if (i.upButtonPresed)
		{
			r.velocity = m.upVelocity;
			m.start = t.position;
			m.destination = t.position + m.upVelocity * TILE_SIZE;
		}
		else if (i.downButtonPresed)
		{
			r.velocity = m.downVelocity;
			m.start = t.position;
			m.destination = t.position + m.downVelocity * TILE_SIZE;
		}
		else if (i.leftButtonPresed)
		{
			r.velocity = m.leftVelocity;
			m.start = t.position;
			m.destination = t.position + m.leftVelocity * TILE_SIZE;
		}
		else if (i.rightButtonPresed)
		{
			r.velocity = m.rightVelocity;
			m.start = t.position;
			m.destination = t.position + m.rightVelocity * TILE_SIZE;
		}
	}
};