#pragma once

#include <vector>
#include <bitset>
#include <unordered_map>
#include <typeindex>
#include <set>
#include <memory>
#include <deque>

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent
{
protected:
	static int nextId;
};

template<typename T>
class Component: public IComponent
{
public:
	Component();

	static int GetId()
	{
		static auto id = nextId++;
		return id;
	}

private:

};

class Entity
{
public:
	Entity() = default;
	Entity(int id) : id(id) {};
	Entity(const Entity& entity) = default;

	inline int GetID() const { return id; }

	void Kill();
	void Tag(std::string tag);
	bool HasTag(const std::string& tag) const;
	void Group(std::string group);
	bool BelongsToGroup(const std::string& group) const;

	Entity& operator= (const Entity& other) = default;
	bool operator== (const Entity& other) const { return id == other.id; }
	bool operator!= (const Entity& other) const { return id != other.id; }
	bool operator< (const Entity& other) const { return id < other.id; }
	bool operator> (const Entity& other) const { return id > other.id; }

	template <typename TComponent, typename ...TArgs> void AddComponent(TArgs&& ...args);
	template <typename TComponent> void RemoveComponent();
	template <typename TComponent> bool HasComponent() const;
	template <typename TComponent> TComponent& GetComponent() const;

	class Registry* mRegistry;

private:
	int id;
};

class System
{
public:
	System() = default;
	~System() = default;

	inline std::vector<Entity>& GetSystemEntities() { return mEntities; }

	void AddEntityToSystem(Entity entity);
	void RemoveEntityFromSystem(Entity entity);
	const Signature& GetComponentSignature() const;

	template <typename TComponent> void RequireComponent();

private:
	Signature componentSignature;
	std::vector<Entity> mEntities;
};

template <typename TComponent>
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}

class IPool
{
public:
	virtual ~IPool() = default;
	virtual void RemoveEntityFromPool(int entityId) = 0;
};

template <typename T>
class Pool : public IPool
{
public:
	Pool(int capacity = 100)
	{ 
		size = 0;
		data.resize(capacity);
	}
	virtual ~Pool() = default;

	void RemoveEntityFromPool(int entityId) override
	{
		if (entityIdToIndex.find(entityId) != entityIdToIndex.end())
		{
			Remove(entityId);
		}
	}

	bool IsEmpty() const { return size == 0; }

	int GetSize() const { return size; }

	void Resize(int n) { data.resize(n); }

	void Clear()
	{ 
		size = 0;
		data.clear();
	}

	void Add(T object) { data.push_back(object); }

	void Set(int entityId, T object)
	{
		if (entityIdToIndex.find(entityId) != entityIdToIndex.end())
		{
			int index = entityIdToIndex[entityId];
			data[index] = object;
		}
		else
		{
			int index = size;
			entityIdToIndex.emplace(entityId, index);
			indexToEntityId.emplace(index, entityId);
			if (index >= data.capacity())
			{
				data.resize(size * 2);
			}
			data[index] = object;
			size++;
		}
	}

	void Remove(int entityId)
	{
		int indxOfRemoved = entityIdToIndex[entityId];
		int indexOfLast = size - 1;
		data[indxOfRemoved] = data[indexOfLast];

		int entityOfLastElement = indexToEntityId[indexOfLast];
		entityIdToIndex[entityOfLastElement] = indxOfRemoved;
		indexToEntityId[indxOfRemoved] = entityOfLastElement;

		entityIdToIndex.erase(entityId);
		indexToEntityId.erase(indexOfLast);

		size--;
	}

	T& Get(int entityId)
	{
		int index = entityIdToIndex[entityId];
		return static_cast<T&>(data[index]);
	}

	T& operator[](unsigned int index) { return data[index]; }

private:
	std::vector<T> data;
	int size;

	std::unordered_map<int, int> entityIdToIndex;
	std::unordered_map<int, int> indexToEntityId;
};

class Registry
{
public:
	Registry() = default;
	~Registry() { }

	void Update();

	Entity CreateEntity();
	void KillEntity(Entity entity);
	void KillAllEntities();

	void AddEntityToSystems(Entity entity);
	void RemoveEntityFromSystems(Entity entity);

	void TagEntity(Entity entity, const std::string& tag);
	bool EntityHasTag(Entity entity, const std::string& tag) const;
	Entity GetEntityByTag(const std::string& tag) const;
	void RemoveEntityTag(Entity entity);

	void GroupEntity(Entity entity, const std::string& group);
	bool EntityBelongsToGroup(Entity entity, const std::string& group) const;
	std::vector<Entity> GetEntitiesByGroup(const std::string& group) const;
	void RemoveEntityGroup(Entity entity);

	template <typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
	template <typename TComponent> void RemoveComponent(Entity entity);
	template <typename TComponent> bool HasComponent(Entity entity);
	template <typename TComponent> TComponent& GetComponent(Entity entity) const;

	template <typename TSystem, typename ...TArgs> void AddSystem(TArgs&& ...args);
	template <typename TSystem> void RemoveSystem(System system);
	template <typename TSystem> bool HasSystem(System system) const;
	template <typename TSystem> TSystem& GetSystem() const;

private:
	int numEntities = 0;
	std::vector<std::shared_ptr<IPool>> componentPools;
	std::vector<Signature> entityComponentSignatures;
	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
	std::set<Entity> mEntitiesToBeAdded;
	std::set<Entity> mEntitiesToBeKilled;
	std::deque<int> freeIds;
	std::unordered_map<std::string, Entity> entityPerTag;
	std::unordered_map<int, std::string> tagPerEntity;
	std::unordered_map<std::string, std::set<Entity>> entitiesPerGroup;
	std::unordered_map<int, std::string> groupPerEntity;
};

template<typename TComponent, typename ...TArgs>
inline void Registry::AddComponent(Entity entity, TArgs && ...args)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetID();

	if (componentId >= componentPools.size())
	{
		componentPools.resize(componentId + 1, nullptr);
	}

	if (componentPools[componentId] == nullptr)
	{
		std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
		componentPools[componentId] = newComponentPool;
	}

	std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

	TComponent newComponent(std::forward<TArgs>(args)...);

	componentPool->Set(entityId, newComponent);
	entityComponentSignatures[entityId].set(componentId);

	//Logger::Log("Component id = " + std::to_string(componentId) + " was added to entity id " + std::to_string(entityId));
	//Logger::Log("COMPONENT ID " + std::to_string(componentId) + " --> POOL SIZE: " + std::to_string(componentPool->GetSize()));
}

template<typename TComponent>
inline void Registry::RemoveComponent(Entity entity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetID();
	entityComponentSignatures[entityId].set(componentId, false);

	std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);
	componentPool->Rmove(entityId);

	entityComponentSignatures[entityId].set(componentId, false);

	//Logger::Log("Component id = " + std::to_string(componentId) + " was removed from entity id " + std::to_string(entityId));
}

template<typename TComponent>
inline bool Registry::HasComponent(Entity entity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetID();

	return entityComponentSignatures[entityId].test(componentId);
}

template<typename TComponent>
inline TComponent& Registry::GetComponent(Entity entity) const
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetID();
	auto componentPool = std::static_pointer_cast < Pool<TComponent >> (componentPools[componentId]);

	return componentPool->Get(entityId);
}

template<typename TSystem, typename ...TArgs>
inline void Registry::AddSystem(TArgs && ...args)
{
	std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
	systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template<typename TSystem>
inline void Registry::RemoveSystem(System systemToRemove)
{
	auto system = systems.find(std::type_index(typeid(TSystem)));
	systems.erase(systemToRemove);
}

template<typename TSystem>
inline bool Registry::HasSystem(System system) const
{
	return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template<typename TSystem>
inline TSystem& Registry::GetSystem() const
{
	auto system = systems.find(std::type_index(typeid(TSystem)));
	return *std::static_pointer_cast<TSystem>(system->second);
}

template<typename TComponent, typename ...TArgs>
inline void Entity::AddComponent(TArgs&& ...args)
{
	mRegistry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template<typename TComponent>
inline void Entity::RemoveComponent()
{
	mRegistry->RemoveComponent<TComponent>(*this);
}

template<typename TComponent>
inline bool Entity::HasComponent() const
{
	return mRegistry->HasComponent<TComponent>(*this);
}

template<typename TComponent>
inline TComponent& Entity::GetComponent() const
{
	return mRegistry->GetComponent<TComponent>(*this);
}