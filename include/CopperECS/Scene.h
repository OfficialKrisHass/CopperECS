#pragma once

#include "Registry.h"

class Scene {

	friend class Object;

public:
	Object CreateObject(const char* name = "Object") { return registry.CreateObject(this, name); }
	void DestroyObject(Object& obj) { registry.DestroyObject(obj); }

	Registry* GetRegistry() { return &registry; }

private:
	Registry registry;

};