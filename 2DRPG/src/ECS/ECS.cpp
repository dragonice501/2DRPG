#include "ECS.h"
#include "../Logger/Logger.h"

int IComponent::nextId = 0;

void Entity::Kill()
{
    mRegistry->KillEntity(*this);
}

void Entity::Tag(std::string tag)
{
    mRegistry->TagEntity(*this, tag);
}

bool Entity::HasTag(const std::string& tag) const
{
    return mRegistry->EntityHasTag(*this, tag);
}

void Entity::Group(std::string group)
{
    mRegistry->GroupEntity(*this, group);
}

bool Entity::BelongsToGroup(const std::string& group) const
{
    return mRegistry->EntityBelongsToGroup(*this, group);
}

void System::AddEntityToSystem(Entity entity)
{
	mEntities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity)
{
    mEntities.erase(std::remove_if(mEntities.begin(), mEntities.end(), [&entity](Entity other) {
        return entity == other;
        }), mEntities.end());
}

const Signature& System::GetComponentSignature() const
{
	return componentSignature;
}

void Registry::Update()
{
    for (auto entity : mEntitiesToBeAdded)
    {
        AddEntityToSystems(entity);
    }
    mEntitiesToBeAdded.clear();

    for (auto entity : mEntitiesToBeKilled)
    {
        RemoveEntityFromSystems(entity);

        entityComponentSignatures[entity.GetID()].reset();

        for (auto pool : componentPools)
        {
            if (pool)
            {
                pool->RemoveEntityFromPool(entity.GetID());
            }
        }

        freeIds.push_back(entity.GetID());

        RemoveEntityTag(entity);
        RemoveEntityGroup(entity);
    }
    mEntitiesToBeKilled.clear();
}

Entity Registry::CreateEntity()
{
    int entityId;

    if (freeIds.empty())
    {
        entityId = numEntities++;
        if (entityId >= entityComponentSignatures.size())
        {
            entityComponentSignatures.resize(entityId + 1);
        }
    }
    else
    {
        entityId = freeIds.front();
        freeIds.pop_front();
    }

    Entity entity(entityId);
    entity.mRegistry = this;
    mEntitiesToBeAdded.insert(entity);
    
    return entity;
}

void Registry::KillEntity(Entity entity)
{
    mEntitiesToBeKilled.insert(entity);
}

void Registry::KillAllEntities()
{
    for (auto& system : systems)
    {
        for (auto& entity : system.second->GetSystemEntities())
        {
            entity.Kill();
        }
    }
}

void Registry::AddEntityToSystems(Entity entity)
{
    const auto entityId = entity.GetID();
    const auto& entityComponentSignature = entityComponentSignatures[entityId];

    for (auto& system : systems)
    {
        const auto& systemComponentSignature = system.second->GetComponentSignature();

        if ((entityComponentSignature & systemComponentSignature) == systemComponentSignature)
        {
            system.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::RemoveEntityFromSystems(Entity entity)
{
    for (auto system : systems)
    {
        system.second->RemoveEntityFromSystem(entity);
    }
}

void Registry::TagEntity(Entity entity, const std::string& tag)
{
    entityPerTag.emplace(tag, entity);
    tagPerEntity.emplace(entity.GetID(), tag);
}

bool Registry::EntityHasTag(Entity entity, const std::string& tag) const
{
    if (tagPerEntity.find(entity.GetID()) == tagPerEntity.end()) return false;

    return entityPerTag.find(tag)->second == entity;
}

Entity Registry::GetEntityByTag(const std::string& tag) const
{
    return entityPerTag.at(tag);
}

void Registry::RemoveEntityTag(Entity entity)
{
    auto taggedEntity = tagPerEntity.find(entity.GetID());
    if (taggedEntity != tagPerEntity.end())
    {
        auto tag = taggedEntity->second;
        entityPerTag.erase(tag);
        tagPerEntity.erase(taggedEntity);
    }
}

void Registry::GroupEntity(Entity entity, const std::string& group)
{
    entitiesPerGroup.emplace(group, std::set<Entity>());
    entitiesPerGroup[group].emplace(entity);
    groupPerEntity.emplace(entity.GetID(), group);
}

bool Registry::EntityBelongsToGroup(Entity entity, const std::string& group) const
{
    if (entitiesPerGroup.find(group) == entitiesPerGroup.end()) return false;

    auto groupEntities = entitiesPerGroup.at(group);
    return groupEntities.find(entity.GetID()) != groupEntities.end();
}

std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& group) const
{
    auto& setOfEntites = entitiesPerGroup.at(group);
    return std::vector<Entity>(setOfEntites.begin(), setOfEntites.end());
}

void Registry::RemoveEntityGroup(Entity entity)
{
    auto groupedEntity = groupPerEntity.find(entity.GetID());
    if (groupedEntity != groupPerEntity.end())
    {
        auto group = entitiesPerGroup.find(groupedEntity->second);
        if (group != entitiesPerGroup.end())
        {
            auto entityInGroup = group->second.find(entity);
            if (entityInGroup != group->second.find(entity))
            {
                group->second.erase(entityInGroup);
            }
        }

        groupPerEntity.erase(groupedEntity);
    }
}
