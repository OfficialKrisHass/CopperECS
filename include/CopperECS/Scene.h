#pragma once

#include "Registry.h"

class Scene {

	friend class Object;

public:
	Object CreateObject(std::string name = "Object") {

		Object ret = registry.CreateObject(this, name);

		return registry.objects[ret.id];

	}
	void DestroyObject(Object& obj) { registry.DestroyObject(obj); }

	Registry* GetRegistry() { return &registry; }

private:
	Registry registry;

};