#pragma once

#include <string>
#include <vector>

#include "Component.h"

const int maxComponents = 32;

template<typename T> class ComponentList;

class Object {

	friend class Scene;
	friend class Registry;

public:
	Object() = default;

	std::string name = "";

	template<typename T> T* AddComponent() {
		
		T* component = scene->registry.AddComponent<T>(*this);
		if (!component) return nullptr;

		component->object = this;

		return component;
	
	}
	template<typename T> T* GetComponent(uint32_t index = 0)		{ return scene->registry.GetComponent<T>(id, index); }
	template<typename T> bool HasComponent()						{ return scene->registry.HasComponent<T>(id); }
	template<typename T> void RemoveComponent(uint32_t index = 0)	{        scene->registry.RemoveComponent<T>(*this, index); }

	template<typename T> ComponentList<T> GetComponents() { return scene->registry.GetComponents<T>(scene, id); }

	int32_t GetID() const { return id; }
	const std::vector<uint32_t>& GetComponentMask() const { return componentMask; }

	operator bool() const { return id != -1 && scene != nullptr; }
	operator int32_t() const { return id; }

	bool operator==(const Object* other) const { return id == other->id && scene == other->scene; }
	bool operator!=(const Object* other) const { return !(*this == other); }

private:
	int32_t id = -1;
	std::vector<uint32_t> componentMask;

	Scene* scene = nullptr;

};