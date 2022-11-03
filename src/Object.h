#pragma once

#include <string>
#include <bitset>

const int maxComponents = 32;

#include "Transform.h"

class Object {

	friend class Scene;
	friend class Registry;

public:
	Object() = default;

	template<typename T> T* AddComponent() { return scene->registry.AddComponent<T>(id); }
	template<typename T> T* GetComponent() { return scene->registry.GetComponent<T>(id); }
	template<typename T> void RemoveComponent() { scene->registry.RemoveComponent<T>(id); }
	template<typename T> bool HasComponent() { scene->registry.AddComponent<T>(id); }

	const char* name = nullptr;
	Transform* transform = nullptr;

	operator bool() const { return id != -1 && scene != nullptr; }
	operator int32_t() const { return id; }

	bool operator==(const Object* other) const { return id == other->id && scene == other->scene; }
	bool operator!=(const Object* other) const { return !(*this == other); }

private:
	int32_t id = -1;
	std::bitset<maxComponents>* componentMask = nullptr;

	Scene* scene = nullptr;

};