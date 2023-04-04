#pragma once

#include "Entity.h"
#include "Registry.h"

class Scene {

	friend InternalEntity;
	friend class Entity;

public:
	InternalEntity* CreateEntity(const std::string& name = "Entity") {

		return registry.CreateEntity(this, name);

	}
	InternalEntity* CreateEntityFromID(uint32_t id, const std::string& name = "Entity", bool returnIfExists = true) {

		return registry.CreateEntityFromID(id, this, name, returnIfExists);

	}
	InternalEntity* GetEntityFromID(uint32_t id) {

		return registry.GetEntityFromID(id);

	}
	void RemoveEntity(InternalEntity* entity) {

		registry.RemoveEntity(entity->id);

	}
	void RemoveEntityFromID(uint32_t id) {

		registry.RemoveEntity(id);

	}

	Registry::ComponentPool* GetComponentPool(int cID) {

		return registry.GetComponentPool(cID);

	}
	uint32_t GetNumOfEntities() {

		return registry.entities.size();

	}

private:
	Registry registry;

};