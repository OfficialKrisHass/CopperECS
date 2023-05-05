#pragma once

#include <stdint.h>
#include <string>
#include <bitset>

const int maxComponents = 32;
const uint32_t invalidID = 4'294'967'295;

class Scene;

class InternalEntity {

	friend class Registry;
	friend class Scene;
	friend class Entity;

public:
	InternalEntity() = default;

	std::string name = "";

	template<typename T> T* AddComponent();
	template<typename T> T* GetComponent();
	template<typename T> bool HasComponent();
	template<typename T> void RemoveComponent();

	uint32_t ID() const { return id; }

	bool operator==(const InternalEntity& other) const { return id == other.id && scene == other.scene; }

	operator bool() const { return id != invalidID && scene != nullptr; }
	operator uint32_t() const { return id; };
	operator int32_t() const { return (int32_t) id; };

private:
	uint32_t id = invalidID;
	Scene* scene = nullptr;

	std::bitset<maxComponents> cMask;

	void Invalidate() {

		id = invalidID;
		name = "";
		scene = nullptr;
		cMask.reset();

	}

};

#include "Scene.h"

class Entity {

public:
	Entity() = default;
	Entity(InternalEntity* entity) {

		if (!entity) return;

		id = entity->id;
		scene = entity->scene;

	}

	bool operator==(const Entity& other) const { return id == other.id && scene == other.scene; }
	bool operator!=(const Entity& other) const { return !(*this == other); }

	InternalEntity* operator->() {

		return scene->GetEntityFromID(id);

	}
	InternalEntity* operator*() {

		return scene->GetEntityFromID(id);

	}

	operator InternalEntity*() const {

		return scene->GetEntityFromID(id);

	}

	operator bool() const { return scene && *scene->GetEntityFromID(id); }
	operator uint32_t() const { return id; }
	operator int32_t() const { return (int32_t) id; }

private:
	uint32_t id = invalidID;
	Scene* scene = nullptr;

};

#include "Entity.inl"